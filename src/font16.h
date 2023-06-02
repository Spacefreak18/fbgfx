#ifndef FONT16_H
#define FONT16_H

extern const unsigned font_w = 8, font_h = 8;
extern const unsigned char font_base = 0x20, font_glyphs = 95;
extern const unsigned char font[95 * 8] =
{
    /* ' '  */ 0, 0, 0, 0, 0, 0, 0, 0,
    /* '!'  */ 24, 24, 24, 24, 0, 24, 24, 0,
    /* '"'  */ 108, 108, 72, 0, 0, 0, 0, 0,
    /* '#'  */ 108, 108, 254, 108, 254, 108, 108, 0,
    /* '$'  */ 16, 124, 208, 124, 22, 124, 16, 0,
    /* '%'  */ 98, 102, 12, 24, 48, 102, 70, 0,
    /* '&'  */ 56, 108, 104, 118, 220, 204, 118, 0,
    /* '''  */ 24, 24, 48, 0, 0, 0, 0, 0,
    /* '('  */ 12, 24, 48, 48, 48, 24, 12, 0,
    /* ')'  */ 48, 24, 12, 12, 12, 24, 48, 0,
    /* '*'  */ 0, 108, 56, 254, 56, 108, 0, 0,
    /* '+'  */ 0, 24, 24, 126, 24, 24, 0, 0,
    /* ','  */ 0, 0, 0, 0, 0, 24, 24, 16,
    /* '-'  */ 0, 0, 0, 126, 0, 0, 0, 0,
    /* '.'  */ 0, 0, 0, 0, 0, 24, 24, 0,
    /* '/'  */ 2, 6, 12, 24, 48, 96, 64, 0,
    /* '0'  */ 60, 102, 110, 118, 102, 102, 60, 0,
    /* '1'  */ 24, 24, 56, 24, 24, 24, 60, 0,
    /* '2'  */ 124, 6, 6, 60, 96, 96, 126, 0,
    /* '3'  */ 124, 6, 6, 28, 6, 6, 124, 0,
    /* '4'  */ 102, 102, 102, 126, 6, 6, 6, 0,
    /* '5'  */ 126, 96, 96, 124, 6, 6, 124, 0,
    /* '6'  */ 62, 96, 96, 124, 102, 102, 60, 0,
    /* '7'  */ 126, 6, 12, 24, 24, 24, 24, 0,
    /* '8'  */ 60, 102, 102, 60, 102, 102, 60, 0,
    /* '9'  */ 60, 102, 102, 62, 6, 6, 124, 0,
    /* ':'  */ 0, 24, 24, 0, 24, 24, 0, 0,
    /* ';'  */ 0, 0, 24, 24, 0, 24, 24, 16,
    /* '<'  */ 12, 24, 48, 96, 48, 24, 12, 0,
    /* '='  */ 0, 0, 126, 0, 126, 0, 0, 0,
    /* '>'  */ 48, 24, 12, 6, 12, 24, 48, 0,
    /* '?'  */ 60, 102, 6, 28, 24, 0, 24, 0,
    /* '@'  */ 60, 102, 110, 110, 110, 96, 62, 0,
    /* 'A'  */ 60, 102, 102, 126, 102, 102, 102, 0,
    /* 'B'  */ 124, 102, 102, 124, 102, 102, 124, 0,
    /* 'C'  */ 60, 102, 96, 96, 96, 102, 60, 0,
    /* 'D'  */ 124, 102, 102, 102, 102, 102, 124, 0,
    /* 'E'  */ 126, 96, 96, 120, 96, 96, 126, 0,
    /* 'F'  */ 126, 96, 96, 120, 96, 96, 96, 0,
    /* 'G'  */ 60, 102, 96, 110, 102, 102, 60, 0,
    /* 'H'  */ 102, 102, 102, 126, 102, 102, 102, 0,
    /* 'I'  */ 126, 24, 24, 24, 24, 24, 126, 0,
    /* 'J'  */ 14, 6, 6, 6, 6, 102, 60, 0,
    /* 'K'  */ 102, 108, 120, 112, 120, 108, 102, 0,
    /* 'L'  */ 96, 96, 96, 96, 96, 96, 126, 0,
    /* 'M'  */ 198, 238, 254, 214, 198, 198, 198, 0,
    /* 'N'  */ 102, 118, 126, 110, 102, 102, 102, 0,
    /* 'O'  */ 60, 102, 102, 102, 102, 102, 60, 0,
    /* 'P'  */ 124, 102, 102, 124, 96, 96, 96, 0,
    /* 'Q'  */ 60, 102, 102, 102, 110, 110, 62, 0,
    /* 'R'  */ 124, 102, 102, 124, 102, 102, 102, 0,
    /* 'S'  */ 62, 96, 96, 60, 6, 6, 124, 0,
    /* 'T'  */ 126, 24, 24, 24, 24, 24, 24, 0,
    /* 'U'  */ 102, 102, 102, 102, 102, 102, 60, 0,
    /* 'V'  */ 102, 102, 102, 102, 60, 60, 24, 0,
    /* 'W'  */ 198, 198, 198, 214, 254, 238, 198, 0,
    /* 'X'  */ 102, 102, 60, 24, 60, 102, 102, 0,
    /* 'Y'  */ 102, 102, 102, 60, 24, 24, 24, 0,
    /* 'Z'  */ 126, 6, 12, 24, 48, 96, 126, 0,
    /* '['  */ 60, 48, 48, 48, 48, 48, 60, 0,
    /* '\\' */ 64, 96, 48, 24, 12, 6, 2, 0,
    /* ']'  */ 60, 12, 12, 12, 12, 12, 60, 0,
    /* '^'  */ 16, 56, 108, 0, 0, 0, 0, 0,
    /* '_'  */ 0, 0, 0, 0, 0, 0, 0, 255,
    /* '`'  */ 24, 24, 8, 0, 0, 0, 0, 0,
    /* 'a'  */ 0, 0, 60, 6, 62, 102, 62, 0,
    /* 'b'  */ 96, 96, 124, 102, 102, 102, 124, 0,
    /* 'c'  */ 0, 0, 60, 102, 96, 102, 60, 0,
    /* 'd'  */ 6, 6, 62, 102, 102, 102, 62, 0,
    /* 'e'  */ 0, 0, 60, 102, 124, 96, 62, 0,
    /* 'f'  */ 14, 24, 24, 60, 24, 24, 60, 0,
    /* 'g'  */ 0, 0, 62, 102, 102, 62, 6, 124,
    /* 'h'  */ 96, 96, 124, 102, 102, 102, 102, 0,
    /* 'i'  */ 24, 0, 24, 24, 24, 24, 24, 0,
    /* 'j'  */ 24, 0, 24, 24, 24, 24, 24, 112,
    /* 'k'  */ 96, 96, 102, 108, 120, 108, 102, 0,
    /* 'l'  */ 48, 48, 48, 48, 48, 48, 28, 0,
    /* 'm'  */ 0, 0, 204, 254, 214, 198, 198, 0,
    /* 'n'  */ 0, 0, 124, 102, 102, 102, 102, 0,
    /* 'o'  */ 0, 0, 60, 102, 102, 102, 60, 0,
    /* 'p'  */ 0, 0, 124, 102, 102, 124, 96, 96,
    /* 'q'  */ 0, 0, 62, 102, 102, 62, 6, 6,
    /* 'r'  */ 0, 0, 54, 56, 48, 48, 48, 0,
    /* 's'  */ 0, 0, 62, 96, 60, 6, 124, 0,
    /* 't'  */ 24, 24, 24, 60, 24, 24, 12, 0,
    /* 'u'  */ 0, 0, 102, 102, 102, 102, 60, 0,
    /* 'v'  */ 0, 0, 102, 102, 60, 60, 24, 0,
    /* 'w'  */ 0, 0, 198, 198, 214, 254, 236, 0,
    /* 'x'  */ 0, 0, 102, 60, 24, 60, 102, 0,
    /* 'y'  */ 0, 0, 102, 102, 102, 62, 6, 124,
    /* 'z'  */ 0, 0, 126, 12, 24, 48, 126, 0,
    /* '{'  */ 28, 48, 48, 96, 48, 48, 28, 0,
    /* '|'  */ 24, 24, 24, 24, 24, 24, 24, 0,
    /* '}'  */ 56, 12, 12, 6, 12, 12, 56, 0,
    /* '~'  */ 50, 76, 0, 0, 0, 0, 0, 0,
};

#endif
