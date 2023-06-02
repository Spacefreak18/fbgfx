#include "render.h"
#include "render16.h"
#include "fbgfx.h"


gfx_color_t (*gfx_rgb) (unsigned char r, unsigned char g, unsigned char b);
void (*gfx_draw_glyph)(unsigned short x, unsigned short y, gfx_color_t fg, gfx_color_t bg, uint8_t ch);
void (*gfx_draw_hline)(unsigned short x0, unsigned short x1, unsigned short y, gfx_color_t c);
void (*gfx_draw_circle)(unsigned short x, unsigned short y, unsigned short r, gfx_color_t c);
void (*gfx_fill_circle)(unsigned short x, unsigned short y, unsigned short r, gfx_color_t c);

gfx_color_t rgb565(unsigned char r, unsigned char g, unsigned char b)
{
    return RGB565(r, g, b);
}


int draw_init(int bpp)
{
    switch (bpp)
    {
        case 16:
            //gfx_draw_glyph = glyph16;
            gfx_rgb = rgb565;
            gfx_draw_hline = hline16;
            gfx_draw_circle = circle16;
            gfx_fill_circle = filledcircle16;
            return 0;
    }

    return -1;
}

void pal_init(void)
{
    pal16[0] = gfx_rgb(0,0,0);
    pal16[1] = gfx_rgb(0,0,170);
    pal16[2] = gfx_rgb(0,170,0);
    pal16[3] = gfx_rgb(0,170,170);
    pal16[4] = gfx_rgb(170,0,0);
    pal16[5] = gfx_rgb(170,0,170);
    pal16[6] = gfx_rgb(170,85,0);
    pal16[7] = gfx_rgb(170,170,170);
    pal16[8] = gfx_rgb(85,85,85);
    pal16[9] = gfx_rgb(85,85,255);
    pal16[10] = gfx_rgb(85,255,85);
    pal16[11] = gfx_rgb(85,255,255);
    pal16[12] = gfx_rgb(255,85,85);
    pal16[13] = gfx_rgb(255,85,255);
    pal16[14] = gfx_rgb(255,255,85);
    pal16[15] = gfx_rgb(255,255,255);
    pal16[16] = gfx_rgb(255,255,0);
    pal16[17] = gfx_rgb(0,0,255);
}
