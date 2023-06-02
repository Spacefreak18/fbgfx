#include <stdbool.h>

#include "render16.h"
#include "ttfont.h"

unsigned short int fn(unsigned int a)
{
    return (-(a >> 16) >> 16) | a;
};

int init_ft (const char* ttf_file, FT_Face* face, FT_Library* ft,
             int req_size, char** error)
{
    //LOG_IN
    //bool ret = false;
    //log_debug ("Requested glyph size is %d px", req_size);
    if (FT_Init_FreeType (ft) == 0)
    {
        //log_info ("Initialized FreeType");
        if (FT_New_Face(*ft, ttf_file, 0, face) == 0)
        {
            //log_info ("Loaded TTF file");
            // Note -- req_size is a request, not an instruction
            if (FT_Set_Pixel_Sizes(*face, 0, req_size) == 0)
            {
                //log_info ("Set pixel size");
                //ret = true;
            }
            else
            {
                //log_error ("Can't set font size to %d", req_size);
                if (error)
                {
                    *error = strdup ("Can't set font size");
                }
            }
        }
        else
        {
            //log_error ("Can't load TTF file %s", ttf_file);
            if (error)
            {
                *error = strdup ("Can't load TTF file");
            }
        }
    }
    else
    {
        //log_error ("Can't initialize FreeType library");
        if (error)
        {
            *error = strdup ("Can't init freetype library");
        }
    }

    //LOG_OUT
    return true;
}

void done_ft (FT_Library ft)
{
    FT_Done_FreeType (ft);
}

int face_get_line_spacing (FT_Face face)
{
    return face->size->metrics.height / 64;
    // There are other possibilities the give subtly different results:
    // return (face->bbox.yMax - face->bbox.yMin)  / 64;
    // return face->height / 64;
}


void face_draw_char_on_fb (FT_Face face, unsigned char* fb, int c, int* x, int y, gfx_color_t color)
{
    // Note that TT fonts have no built-in padding.
    // That is, first,
    //  the top row of the bitmap is the top row of pixels to
    //  draw. These rows usually won't be at the face bounding box. We need to
    //  work out the overall height of the character cell, and
    //  offset the drawing vertically by that amount.
    //
    // Similar, there is no left padding. The first pixel in each row will not
    //  be drawn at the left margin of the bounding box, but in the centre of
    //  the screen width that will be occupied by the glyph.
    //
    //  We need to calculate the x and y offsets of the glyph, but we can't do
    //  this until we've loaded the glyph, because metrics
    //  won't be available.

    // Note that, by default, TT metrics are in 64'ths of a pixel, hence
    //  all the divide-by-64 operations below.

    // Get a FreeType glyph index for the character. If there is no
    //  glyph in the face for the character, this function returns
    //  zero. We should really check for this, and substitute a default
    //  glyph. Naturally, the TTF font chosen must contain glyphs for
    //  all the characters to be displayed.
    FT_UInt gi = FT_Get_Char_Index (face, c);

    // Loading the glyph makes metrics data available
    FT_Load_Glyph (face, gi, FT_LOAD_DEFAULT);

    // Now we have the metrics, let's work out the x and y offset
    //  of the glyph from the specified x and y. Because there is
    //  no padding, we can't just draw the bitmap so that it's
    //  TL corner is at (x,y) -- we must insert the "missing"
    //  padding by aligning the bitmap in the space available.

    // bbox.yMax is the height of a bounding box that will enclose
    //  any glyph in the face, starting from the glyph baseline.
    int bbox_ymax = face->bbox.yMax / 64;
    // horiBearingX is the height of the top of the glyph from
    //   the baseline. So we work out the y offset -- the distance
    //   we must push down the glyph from the top of the bounding
    //   box -- from the height and the Y bearing.
    int y_off = bbox_ymax - face->glyph->metrics.horiBearingY / 64;

    // glyph_width is the pixel width of this specific glyph
    int glyph_width = face->glyph->metrics.width / 64;
    // Advance is the amount of x spacing, in pixels, allocated
    //   to this glyph
    int advance = face->glyph->metrics.horiAdvance / 64;
    // Work out where to draw the left-most row of pixels --
    //   the x offset -- by halving the space between the
    //   glyph width and the advance
    int x_off = (advance - glyph_width) / 2;

    // So now we have (x_off,y_off), the location at which to
    //   start drawing the glyph bitmap.

    // Rendering a loaded glyph creates the bitmap
    FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

    // Write out the glyph row-by-row using framebuffer_set_pixel
    // Note that the glyph can contain horizontal padding. We need
    //  to take this into account when working out where the pixels
    //  are in memory, but we don't actually need to "draw" these
    //  empty pixels. bitmap.width is the number of pixels that actually
    //  contain values; bitmap.pitch is the spacing between bitmap
    //  rows in memory.
    for (int i = 0; i < (int)face->glyph->bitmap.rows; i++)
    {
        // Row offset is the distance from the top of the framebuffer
        //  of this particular row of pixels in the glyph.
        int row_offset = y + i + y_off;
        for (int j = 0; j < (int)face->glyph->bitmap.width; j++)
        {
            unsigned char p =
                face->glyph->bitmap.buffer [i * face->glyph->bitmap.pitch + j];

            // Working out the Y position is a little fiddly. horiBearingY
            //  is how far the glyph extends about the baseline. We push
            //  the bitmap down by the height of the bounding box, and then
            //  back up by this "bearing" value.
            if (p)
            {
                //framebuffer_set_pixel (fb, *x + j + x_off, row_offset, p, p, p);

                putpixel16(fn(*x + j + x_off), fn(row_offset), color);
            }
        }
    }
    // horiAdvance is the nominal X spacing between displayed glyphs.
    *x += advance;
}

void face_draw_string_on_fb (FT_Face face, unsigned char* fb, const UTF32* s,
                             int* x, int y, gfx_color_t color)
{
    while (*s)
    {
        face_draw_char_on_fb (face, fb, *s, x, y, color);
        s++;
    }
}

void face_get_char_extent (const FT_Face face, int c, int* x, int* y)
{
    // Note that, by default, TT metrics are in 64'ths of a pixel, hence
    //  all the divide-by-64 operations below.

    // Get a FreeType glyph index for the character. If there is no
    //  glyph in the face for the character, this function returns
    //  zero. We should really check for this, and substitute a default
    //  glyph. Naturally, the TTF font chosen must contain glyphs for
    //  all the characters to be displayed.
    FT_UInt gi = FT_Get_Char_Index(face, c);

    // Loading the glyph makes metrics data available
    FT_Load_Glyph (face, gi, FT_LOAD_NO_BITMAP);

    *y = face_get_line_spacing (face);
    *x = face->glyph->metrics.horiAdvance / 64;
}

void face_get_string_extent (const FT_Face face, const UTF32* s,
                             int* x, int* y)
{
    *x = 0;
    int y_extent = 0;
    while (*s)
    {
        int x_extent;
        face_get_char_extent (face, *s, &x_extent, &y_extent);
        *x += x_extent;
        s++;
    }
    *y = y_extent;
}

UTF32* utf8_to_utf32 (const UTF8* word)
{
    //assert (word != NULL);
    int l = strlen ((char*)word);
    UTF32* ret = malloc ((l + 1) * sizeof (UTF32));
    for (int i = 0; i < l; i++)
    {
        ret[i] = (UTF32) word[i];
    }
    ret[l] = 0;
    return ret;
}



void draw_string_on_fb(FT_Face face, FT_Library fontlib, char* pixels, int xpos, int ypos, gfx_color_t color, char* string)
{
    int space_y;
    int space_x; // Pixel width of a space

    UTF32 utf32_space[2] = {' ', 0};
    //log_debug ("Obtained a face whose space has height %d px", space_y);
    //log_debug ("Line spacing is %d px", face_get_line_spacing (face));

    // x and y are the current coordinates of the top-left corner of
    //  the bounding box of the text being written, relative to the
    //  TL corner of the screen.
    int x = xpos;
    int y = ypos;

    face_get_string_extent (face, utf32_space, &space_x, &space_y);


    //log_debug ("Starting drawing at %d,%d", x, y);
    int line_spacing = face_get_line_spacing (face);
    UTF32* word32 = utf8_to_utf32 ((UTF8*)string);

    // Get the extent of the bounding box of this word, to see
    //  if it will fit in the specified width.
    int x_extent, y_extent;
    face_get_string_extent (face, word32, &x_extent, &y_extent);
    int x_advance = x_extent + space_x;
    //log_debug ("Word width is %d px; would advance X position by %d", x_extent, x_advance);

    // If the text won't fit, move down to the next line
    //if (x + x_advance > width)
    //{
    //log_debug ("Text too large for bonuds -- move to next line");
    //x = init_x;
    //y += line_spacing;
    //}
    // If we're already below the specified height, don't write anything
    //if (y + line_spacing < init_y + height)
    //{
    face_draw_string_on_fb (face, pixels, word32, &x, y, color);
    face_draw_string_on_fb (face, pixels, utf32_space, &x, y, color);
    //}
    free (word32);
}
