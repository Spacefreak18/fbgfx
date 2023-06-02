set(fbgfx_source_files
    src/render.c
    src/render.h
    src/render16.c
    src/render16.h
    src/fbgfx.c
    src/fbgfx.h
    src/fbbuf.h
    src/ttfont.h
    src/ttfont.c
    src/font16.h
)


set(FREETYPE_INCLUDE_DIR /usr/include/freetype2)
include_directories("." ${FREETYPE_INCLUDE_DIR})

add_library(fbgfx STATIC ${fbgfx_source_files})
