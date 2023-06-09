#ifndef GFX_H
#define GFX_H
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/******************************************************************************/

#define gfx_read8(p) (*(volatile uint8_t *) (p))
#define gfx_read16(p) (*(volatile uint16_t *) (p))
#define gfx_read32(p) (*(volatile uint32_t *) (p))
#define gfx_write8(v, p) (*(volatile uint8_t *) (p) = (v))
#define gfx_write16(v, p) (*(volatile uint16_t *) (p) = (v))
#define gfx_write32(v, p) (*(volatile uint32_t *) (p) = (v))

#define RGB565(r, g, b) (gfx_color_t)((((r) & 248u) << 8) | (((g) & 252) << 3) | (b >> 3))

/******************************************************************************/

typedef uint32_t gfx_color_t;

/******************************************************************************/

void gfx_close(void);
int gfx_open(unsigned* xres, unsigned* yres, size_t* rowbytes);
int gfx_setbpp(unsigned bpp, size_t* rowbytes);
void* gfx_buffer(size_t* len);
int gfx_setpal(unsigned i, unsigned n, unsigned short* r, unsigned short* g, unsigned short* b);
int gfx_swapbuffers(void);
void gfx_frame(void* pixels, size_t pixels_len);

/******************************************************************************/

static inline void
gfx_clear(void* pixels, size_t pixels_len)
{
    memset(pixels, 0, pixels_len);
}

#endif
