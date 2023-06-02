#include "fbgfx.h"

extern gfx_color_t pal16[18];
extern size_t pixels_len, rowbytes;
extern unsigned char* pixels;
extern unsigned xres, yres;

int draw_init(int bpp);
void pal_init(void);

extern gfx_color_t (*gfx_rgb) (unsigned char r, unsigned char g, unsigned char b);
extern void (*gfx_draw_glyph)(unsigned short x, unsigned short y, gfx_color_t fg, gfx_color_t bg, uint8_t ch);
extern void (*gfx_draw_hline)(unsigned short x0, unsigned short x1, unsigned short y, gfx_color_t c);
extern void (*gfx_draw_circle)(unsigned short x, unsigned short y, unsigned short r, gfx_color_t c);
extern void (*gfx_fill_circle)(unsigned short x, unsigned short y, unsigned short r, gfx_color_t c);
