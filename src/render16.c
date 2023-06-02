#include <stdlib.h>

#include "fbbuf.h"
//#include "font16.h"
#include "render16.h"

void* pixel_address(unsigned short x, unsigned short y)
{
    return (uint8_t*)pixels + y * rowbytes + x * 2;
}

void putpixel16(unsigned short x, unsigned short y, gfx_color_t c)
{
    gfx_write16(c, pixel_address(x, y));
}

void line16(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, gfx_color_t c)
{
    int maj, minor;
    int ymajor;
    int32_t delta;
    unsigned j;
    unsigned short x, y;

    // HACK to swap (x0, y0) and (x1, y1)
    if (0)
    {
        unsigned short t;
        t = x0;
        x0 = x1;
        x1 = t;
        t = y0;
        y0 = y1;
        y1 = t;
    }

    maj = (int)x1 - (int)x0;
    minor = (int)y1 - (int)y0;
    x = x0;
    y = y0;

    ymajor = abs(maj) < abs(minor);
    if (ymajor)
    {
        int tmp = maj;
        maj = minor;
        minor = tmp;
    }

    if (maj)
    {
        delta = (minor << 16) / maj;
    }
    else
    {
        delta = 0;
    }

    if (ymajor)
    {
        if (maj > 0)
        {
            maj += y;
            for (j = 0x8000 + ((unsigned)x << 16); y <= maj; y++)
            {
                putpixel16(j >> 16, y, c);
                j += delta;
            }
        }
        else
        {
            maj += y;
            for (j = 0x8000 + ((unsigned)x << 16); y >= maj; y--)
            {
                putpixel16(j >> 16, y, c /* gfx_rgb(0,0,255) */);
                j -= delta;
            }
        }
    }
    else
    {
        if (maj > 0)
        {
            maj += x;
            for (j = 0x8000 + ((unsigned)y << 16); x <= maj; x++)
            {
                putpixel16(x, j >> 16, c /* gfx_rgb(0,255,0) */);
                j += delta;
            }
        }
        else
        {
            maj += x;
            for (j = 0x8000 + ((unsigned)y << 16); x >= maj; x--)
            {
                putpixel16(x, j >> 16, c /* gfx_rgb(255,0, 0) */);
                j -= delta;
            }
        }
    }
}

//void glyph16(unsigned short x, unsigned short y, gfx_color_t fg, gfx_color_t bg, uint8_t ch)
//{
//  /* expand 2 bits into 2 16-bit pixels */
//  static const uint32_t tab[4] = {
//      0x00000000, 0xffff0000, 0x0000ffff, 0xffffffff,
//  };
//  const uint8_t *c = font + font_h * ((font_w + 7) / 8) * (ch - font_base);
//  unsigned w = font_w, h = font_h;
//  uint32_t fgx, bgx, eorx;
//  uint32_t *out;
//  unsigned row, col;
//  size_t adj;
//
//  fgx = fg;
//  bgx = bg;
//  fgx |= (fgx << 16);
//  bgx |= (bgx << 16);
//  eorx = fgx ^ bgx;
//
//  out = pixel_address(x, y);
//  adj = rowbytes / 4 - (w / 2); // TODO: calculate this properly
//  for (row = 0; row < h; row++) {
//      for (col = 0; col < w; col += 8) {
//          gfx_write32((tab[*c >> 6] & eorx) ^ bgx, out++);
//          gfx_write32((tab[*c >> 4 & 3] & eorx) ^ bgx, out++);
//          gfx_write32((tab[*c >> 2 & 3] & eorx) ^ bgx, out++);
//          gfx_write32((tab[*c & 3] & eorx) ^ bgx, out++);
//          c++;
//      }
//      out += adj;
//  }
//}

//
// TODO: make operations that honor a scissor test
//   clip_hline16()
//   clip_putpixel16()
//

void hline16(unsigned short x0, unsigned short x1, unsigned short y, gfx_color_t c)
{
    uint32_t* out;
    uint32_t px;
    unsigned short x = x0;

    if (x & 1)
    {
        putpixel16(x, y, c);
        x++;
    }

    px = c;
    px |= px << 16;
    out = pixel_address(x, y);
    if ((intptr_t)out & 1)
    {
        return;
    }
    while (x < x1)
    {
        gfx_write32(px, out++);
        x += 2;
    }

    if (!(x1 & 1))
    {
        putpixel16(x1, y, c);
    }
}

void circle16(unsigned short x, unsigned short y, unsigned short r, gfx_color_t c)
{
    int i = r, j = 0;
    int err = 1 - i;

    while (i >= j)
    {
        putpixel16(x + i, y + j, c);
        putpixel16(x - i, y + j, c);
        putpixel16(x + i, y - j, c);
        putpixel16(x - i, y - j, c);
        putpixel16(x + j, y + i, c);
        putpixel16(x - j, y + i, c);
        putpixel16(x + j, y - i, c);
        putpixel16(x - j, y - i, c);
        j++;
        err += (err < 0) ?  2 * j + 1 : 2 * (j - --i + 1);
    }
}

void filledcircle16(unsigned short x, unsigned short y, unsigned short r, gfx_color_t c)
{
    int i = r, j = 0;
    int err = 1 - i;
    unsigned short a, b;

    while (i >= j)
    {
        a = x - i;
        b = x + i;
        hline16(a, b, y - j, c);
        if (j)
        {
            hline16(a, b, y + j, c);
        }
        j++;
        if (err < 0)
        {
            err += 2 * j + 1;
        }
        else
        {
            if (i >= j)
            {
                a = x - j;
                b = x + j;
                hline16(a, b, y - i, c);
                if (i)
                {
                    hline16(a, b, y + i, c);
                }
            }
            err += 2 * (j - --i + 1);
        }
    }
}
