#ifndef RENDER16_H
#define RENDER16_H

#include "fbgfx.h"




void* pixel_address(unsigned short x, unsigned short y);
void putpixel16(unsigned short x, unsigned short y, gfx_color_t c);

void line16(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, gfx_color_t c);

void glyph16(unsigned short x, unsigned short y, gfx_color_t fg, gfx_color_t bg, uint8_t ch);
void hline16(unsigned short x0, unsigned short x1, unsigned short y, gfx_color_t c);
void circle16(unsigned short x, unsigned short y, unsigned short r, gfx_color_t c);
void filledcircle16(unsigned short x, unsigned short y, unsigned short r, gfx_color_t c);

#endif
