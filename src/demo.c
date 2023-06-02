#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>

#include "fbgfx.h"
#include "fbbuf.h"
#include "render16.h"
#include "font16.h"
#include "render.h"
#include "ttfont.h"

size_t pixels_len, rowbytes;
unsigned char* pixels;
unsigned xres, yres;

gfx_color_t pal16[17];

/******************************************************************************/

#define MIN(a, b) ({ \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })
#define MAX(a, b) ({ \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

/******************************************************************************/






static void draw_string(unsigned short x, unsigned short y, gfx_color_t fg, gfx_color_t bg, const char* s)
{
    unsigned short i;


    for (i = x; *s; i += font_w)
    {
        if (i > xres)
        {
            y += font_h;
            i = x;
        }
        //gfx_draw_glyph(i, y, fg, bg, *s++);
    }
}

static void random_text(void)
{
    gfx_color_t fg, bg;
    unsigned short x, y;

    /* fill the screen with random letters of random color */
    for (y = 0; y <= yres - font_h; y += 8)
    {
        for (x = 0; x <= xres - font_w; x += 8)
        {
            unsigned char ch = (rand() % font_glyphs) + font_base;
            fg = pal16[rand() % 16];
            bg = pal16[rand() % 16];

            //gfx_draw_glyph(x, y, fg, bg, ch);
        }
    }
}

void iso_maze(void)
{
    gfx_color_t fg, bg;
    unsigned short x, y;

    fg = pal16[0];
    bg = pal16[7];
    for (y = 0; y <= yres - font_h; y += 8)
    {
        for (x = 0; x <= xres - font_w; x += 8)
        {

            //gfx_draw_glyph(x, y, fg, bg, rand() % 2 ? '\\' : '/');
        }
    }
}

/* demo of several draw commands */
void demo16(void)
{
    gfx_color_t fg, bg;
    unsigned i;
    unsigned short r;
    unsigned short x, y;

    iso_maze();

    /* draw some lines on top of a black circle */
    filledcircle16(xres / 2, yres / 2, MAX(xres, yres) / 5, pal16[0]);
    for (i = 1; i < 15; i++)
    {
        line16(xres / 3, yres / 3,
               xres - xres / 3 - i * 3, yres - yres / 3, pal16[i]);
        line16(xres / 3, yres / 3,
               xres - xres / 3, yres - yres / 3 - i * 2, pal16[i]);
    }

    /* draw a fan in the corner */
    r = MIN(yres, xres) / 3;
    for (i = 1; i < r; i += 10)
    {
        line16(xres - r, yres - r, xres - i, yres - 1, pal16[15]);
        line16(xres - r, yres - r, xres - 1, yres - i, pal16[15]);
    }

    /* draw a red triangle thing */
    r = xres / 4;
    for (i = 0; i < r; i++)
    {
        gfx_draw_hline(r + i, xres - 1 - r - i, 40 + i, pal16[12]);
    }

    /* draw a 2x2 block of black on white letters */
    bg = pal16[15];
    fg = pal16[0];
    x = 233; // rand() % (xres - font_w * 2);
    y = 57; // rand() % (yres - font_h * 2);
    //glyph16(x, y, fg, bg, 'A');
    //glyph16(x + font_w, y, fg, bg, 'B');
    //glyph16(x, y + font_h, fg, bg, 'C');
    //glyph16(x + font_w, y + font_h, fg, bg, 'D');

    /* draw a blue circle in the upper left corner */
    r = MIN(xres, yres) / 5;
    filledcircle16(r, r, r, pal16[9]);
    circle16(xres / 2, yres / 2, r, pal16[14]);

    gfx_swapbuffers();
}

/* an animated clock */

void clock16(void)
{
    float theta;
    time_t now;
    struct tm tm;
    int ox, oy, cx, cy;
    int r;
    int i;
    char date[40];

    ox = xres / 2;
    oy = yres / 2;

    r = MIN(xres, yres) * 2 / 3 / 2;

    while (1)
    {
        time(&now);
        tm = *localtime(&now);


        gfx_clear(pixels, pixels_len);

        strftime(date, sizeof(date), "%Y.%m.%d", &tm);
        //draw_string(0, 0, pal16[8], pal16[15], date);

        /* draw jewels */
        for (i = 0; i < 12; i++)
        {
            theta = 2 * M_PI * (i / 12.) - M_PI / 2;
            cx = round(r * cos(theta));
            cy = round(r * sin(theta));
            filledcircle16(ox + cx, oy + cy, r / 18,
                           i == 0 ? pal16[14] : pal16[3]);
        }

        /* second hand */
        theta = 2 * M_PI * (tm.tm_sec / 60.) - M_PI / 2;
        cx = round(r * cos(theta));
        cy = round(r * sin(theta));
        line16(ox, oy, ox + cx, oy + cy, pal16[15]);

        /* minute hand */
        // TODO: draw a triangle
        theta = 2 * M_PI * (tm.tm_min / 60.) - M_PI / 2;
        cx = round(r * cos(theta));
        cy = round(r * sin(theta));
        line16(ox, oy, ox + cx, oy + cy, pal16[10]);

        /* hour hand */
        // TODO: draw a triangle
        // HOUR only: theta = 2 * M_PI * ((tm.tm_hour % 12) / 12.) - M_PI / 2;
        /* add in minute's contribution to a fraction of an hour */
        theta = 2 * M_PI * ((tm.tm_hour % 12) / 12. + (tm.tm_min / 720.)) - M_PI / 2;
        cx = round(r / 2 * cos(theta));
        cy = round(r / 2 * sin(theta));
        line16(ox, oy, ox + cx, oy + cy, pal16[13]);


        FT_Face face_font32;
        FT_Library ft_font32;
        char* error = NULL;
        if (init_ft ("./font.ttf", &face_font32, &ft_font32, 32, &error))
        {
            draw_string_on_fb(face_font32, ft_font32, pixels, xres/2 - (xres*.05), yres - (yres*.1), pal16[16], date);
        }

        gfx_swapbuffers();
        sleep(1);
    }
}


/* draws a simple star pattern to test the line drawing function */
void test16(void)
{
    unsigned short ox, oy;
    unsigned short r;

    ox = xres / 2;
    oy = yres / 2;
    r = MIN(xres, yres) / 4;

    line16(ox, oy, ox - r, oy - r, pal16[15]); // top-left
    line16(ox, oy, ox + r, oy - r, pal16[12]); // top-right
    line16(ox, oy, ox - r, oy + r, pal16[10]); // bottom-left
    line16(ox, oy, ox + r, oy + r, pal16[9]); // bottom-right

    line16(ox, oy, ox - r / 2, oy - r, pal16[14]);
    line16(ox, oy, ox + r / 2, oy - r, pal16[14]);
    line16(ox, oy, ox, oy - r, pal16[13]);

    line16(ox, oy, ox - r / 2, oy + r, pal16[14]);
    line16(ox, oy, ox + r / 2, oy + r, pal16[14]);
    line16(ox, oy, ox, oy + r, pal16[13]);

    line16(ox, oy, ox - r, oy - r / 2, pal16[2]);
    line16(ox, oy, ox - r, oy + r / 2, pal16[4]);
    line16(ox, oy, ox - r, oy, pal16[1]);

    line16(ox, oy, ox + r, oy + r / 2, pal16[2]);
    line16(ox, oy, ox + r, oy - r / 2, pal16[4]);
    line16(ox, oy, ox + r, oy, pal16[1]);
}

/******************************************************************************/

void sighandler(int signum, siginfo_t* info, void* ptr)
{
    gfx_clear(pixels, pixels_len);
    gfx_swapbuffers();
    gfx_close();
}

struct sigaction act;

int main(int argc, char** argv)
{
    srand(time(0));
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = sighandler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTSTP, &act, NULL);

    if (gfx_open(&xres, &yres, &rowbytes))
    {
        return 1;
    }

    if (gfx_setbpp(16, &rowbytes))
    {
        return 1;
    }


    draw_init(16);

    pixels = gfx_buffer(&pixels_len);
    if (!pixels)
    {
        return 1;
    }

    gfx_clear(pixels, pixels_len);

    pal_init();

    if (argc == 1)
    {
        printf("usage: %s [d|c|t]\n", argv[0]);
    }
    else
        if (argv[1][0] == 'd')
        {
            demo16();
        }
        else
            if (argv[1][0] == 'c')
            {
                clock16();
            }
            else
                if (argv[1][0] == 't')
                {
                    test16();
                }
                else
                {
                    goto failure;
                }

    gfx_close();

    return 0;
failure:
    gfx_close();
    return 1;
}
