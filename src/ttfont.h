#ifndef TTFONT_H
#define TTFONT_H

#include <freetype2/ft2build.h>
#include <freetype/freetype.h>

#include "fbgfx.h"

#ifndef UTF8
typedef unsigned char UTF8;
#endif

#ifndef UTF32
typedef int32_t UTF32;
#endif


unsigned short int fn(unsigned int a);

int init_ft (const char* ttf_file, FT_Face* face, FT_Library* ft, int req_size, char** error);

/*===========================================================================

  done_ft

  Clean up after we've finished wih the FreeType library

  =========================================================================*/
void done_ft (FT_Library ft);

/*===========================================================================

  face_get_line_spacing

  Get the nominal line spacing, that is, the distance between glyph
  baselines for vertically-adjacent rows of text. This is "nominal" because,
  in "real" typesetting, we'd need to add extra room for accents, etc.

  =========================================================================*/
int face_get_line_spacing (FT_Face face);

/*===========================================================================

  face_draw_char_on_fb

  Draw a specific character, at a specific location, direct to the
  framebuffer. The Y coordinate is the left-hand edge of the character.
  The Y coordinate is the top of the bounding box that contains all
  glyphs in the specific face. That is, (X,Y) are the top-left corner
  of where the largest glyph in the face would need to be drawn.
  In practice, most glyphs will be drawn a little below ths point, to
  make the baselines align.

  The X coordinate is expressed as a pointer so it can be incremented,
  ready for the next draw on the same line.

  =========================================================================*/
void face_draw_char_on_fb (FT_Face face, unsigned char* fb, int c, int* x, int y, gfx_color_t color);

/*===========================================================================

  face_draw_string_on_fb

  draw a string of UTF32 characters (null-terminated), advancing each
  character by enough to create reasonable horizontal spacing. The
  X coordinate is expressed as a pointer so it can be incremented,
  ready for the next draw on the same line.

  =========================================================================*/
void face_draw_string_on_fb (FT_Face face, unsigned char* fb, const UTF32* s, int* x, int y, gfx_color_t color);

/*===========================================================================

  face_get_char_extent

  =========================================================================*/
void face_get_char_extent (const FT_Face face, int c, int* x, int* y);

/*===========================================================================

  face_get_string_extent

  UTF32 characters (null-terminated),

  =========================================================================*/
void face_get_string_extent (const FT_Face face, const UTF32* s, int* x, int* y);

/*===========================================================================

  utf8_to_utf32

  Convert an 8-bit character string to a 32-bit character string; both
  are null-terminated.

  If this weren't just a demo, we'd have a real character set
    conversion here. It's not that difficult, but it's not really what
    this demonstration is for. For now, just pad the 8-bit characters
    to 32-bit.

  =========================================================================*/
UTF32* utf8_to_utf32 (const UTF8* word);


void draw_string_on_fb(FT_Face face, FT_Library fontlib, char* pixels, int xpos, int ypos, gfx_color_t color, char* string);

#endif
