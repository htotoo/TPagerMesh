/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: --bpp 1 --size 10 --no-compress --stride 1 --align 1 --font Montserrat-Regular.ttf --symbols őűŐŰ😀😁😂🤣😃😄😎😋😊😉😆😅🙂🤗🫡 --range 160-255,8352-8399 --format lvgl -o font_montserrat_10_hun.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef FONT_MONTSERRAT_10_HUN
#define FONT_MONTSERRAT_10_HUN 1
#endif

#if FONT_MONTSERRAT_10_HUN

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+00A0 " " */
    0x0,

    /* U+00A1 "¡" */
    0xbc,

    /* U+00A2 "¢" */
    0x23, 0xa9, 0x4a, 0x38, 0x80,

    /* U+00A3 "£" */
    0x3d, 0x4, 0x3e, 0x41, 0xf, 0xc0,

    /* U+00A4 "¤" */
    0xb7, 0x38, 0x61, 0xfc,

    /* U+00A5 "¥" */
    0x82, 0x89, 0xa1, 0x47, 0xcf, 0x84, 0x0,

    /* U+00A6 "¦" */
    0xe3, 0x80,

    /* U+00A7 "§" */
    0xf8, 0xcb, 0xd3, 0x1e,

    /* U+00A8 "¨" */
    0xc0,

    /* U+00A9 "©" */
    0x18, 0xeb, 0xe, 0x1c, 0x2e, 0x8e, 0x0,

    /* U+00AA "ª" */
    0xce, 0xb0,

    /* U+00AB "«" */
    0x25, 0xa5,

    /* U+00AC "¬" */
    0xf8, 0x40,

    /* U+00AE "®" */
    0x18, 0xfa, 0x9d, 0xda, 0xa8, 0x8e, 0x0,

    /* U+00AF "¯" */
    0xf0,

    /* U+00B0 "°" */
    0x56, 0xa0,

    /* U+00B1 "±" */
    0x21, 0x3e, 0x40, 0x7c,

    /* U+00B2 "²" */
    0xe4, 0xac,

    /* U+00B3 "³" */
    0x22, 0x21, 0xe0,

    /* U+00B4 "´" */
    0x40,

    /* U+00B5 "µ" */
    0x8c, 0x63, 0x1f, 0xc2, 0x0,

    /* U+00B6 "¶" */
    0x7f, 0x7a, 0x52, 0x94, 0xa5,

    /* U+00B7 "·" */
    0x80,

    /* U+00B8 "¸" */
    0x18,

    /* U+00B9 "¹" */
    0x49, 0x24,

    /* U+00BA "º" */
    0x69, 0x96,

    /* U+00BB "»" */
    0xa5, 0x5a,

    /* U+00BC "¼" */
    0xc0, 0x22, 0x12, 0x1e, 0x41, 0x51, 0x3c, 0x84,

    /* U+00BD "½" */
    0xc2, 0x22, 0x12, 0xdd, 0x11, 0x11, 0x10, 0x9e,

    /* U+00BE "¾" */
    0xf0, 0x18, 0x81, 0x49, 0xa4, 0x12, 0x84, 0xf2,
    0x8,

    /* U+00BF "¿" */
    0x40, 0x8, 0x88, 0x45, 0xc0,

    /* U+00C0 "À" */
    0x20, 0x20, 0x41, 0x42, 0x88, 0x9f, 0x42, 0x82,

    /* U+00C1 "Á" */
    0x8, 0x20, 0x41, 0x42, 0x88, 0x9f, 0x42, 0x82,

    /* U+00C2 "Â" */
    0x10, 0x50, 0x41, 0x42, 0x88, 0x9f, 0x42, 0x82,

    /* U+00C3 "Ã" */
    0x20, 0x30, 0x41, 0x42, 0x88, 0x9f, 0x42, 0x82,

    /* U+00C4 "Ä" */
    0x28, 0x20, 0xa1, 0x44, 0x4f, 0xa1, 0x41,

    /* U+00C5 "Å" */
    0x10, 0x20, 0x41, 0x42, 0x88, 0x9f, 0x42, 0x82,

    /* U+00C6 "Æ" */
    0xf, 0xc5, 0x1, 0x40, 0x9f, 0x3c, 0x11, 0x8,
    0x7c,

    /* U+00C7 "Ç" */
    0x3d, 0x8, 0x20, 0x81, 0x3, 0xc4, 0x10,

    /* U+00C8 "È" */
    0x41, 0x3f, 0x8, 0x7e, 0x10, 0xf8,

    /* U+00C9 "É" */
    0x11, 0x3f, 0x8, 0x7e, 0x10, 0xf8,

    /* U+00CA "Ê" */
    0x22, 0xbf, 0x8, 0x7e, 0x10, 0xf8,

    /* U+00CB "Ë" */
    0x57, 0xe1, 0xf, 0xc2, 0x1f,

    /* U+00CC "Ì" */
    0x95, 0x55, 0x40,

    /* U+00CD "Í" */
    0x6a, 0xaa, 0x80,

    /* U+00CE "Î" */
    0x55, 0x24, 0x92, 0x40,

    /* U+00CF "Ï" */
    0xa9, 0x24, 0x92,

    /* U+00D0 "Ð" */
    0x7c, 0x42, 0x41, 0xf1, 0x41, 0x42, 0x7c,

    /* U+00D1 "Ñ" */
    0x29, 0x48, 0x71, 0xa6, 0xd9, 0x63, 0x84,

    /* U+00D2 "Ò" */
    0x20, 0x20, 0xe2, 0x28, 0x30, 0x60, 0xa2, 0x38,

    /* U+00D3 "Ó" */
    0x8, 0x20, 0xe2, 0x28, 0x30, 0x60, 0xa2, 0x38,

    /* U+00D4 "Ô" */
    0x10, 0x50, 0xe2, 0x28, 0x30, 0x60, 0xa2, 0x38,

    /* U+00D5 "Õ" */
    0x0, 0x70, 0xe2, 0x28, 0x30, 0x60, 0xa2, 0x38,

    /* U+00D6 "Ö" */
    0x14, 0x71, 0x14, 0x18, 0x30, 0x51, 0x1c,

    /* U+00D7 "×" */
    0x96, 0xa0,

    /* U+00D8 "Ø" */
    0x4, 0x71, 0x34, 0x99, 0x34, 0x59, 0x1c, 0x40,

    /* U+00D9 "Ù" */
    0x40, 0x88, 0x61, 0x86, 0x18, 0x61, 0x78,

    /* U+00DA "Ú" */
    0x8, 0x48, 0x61, 0x86, 0x18, 0x61, 0x78,

    /* U+00DB "Û" */
    0x0, 0xc8, 0x61, 0x86, 0x18, 0x61, 0x78,

    /* U+00DC "Ü" */
    0x32, 0x18, 0x61, 0x86, 0x18, 0x5e,

    /* U+00DD "Ý" */
    0x8, 0x22, 0x12, 0x22, 0x85, 0x4, 0x8, 0x10,

    /* U+00DE "Þ" */
    0x83, 0xe8, 0x61, 0x87, 0xe8, 0x0,

    /* U+00DF "ß" */
    0x74, 0x63, 0x68, 0xc6, 0xc0,

    /* U+00E0 "à" */
    0x41, 0x3c, 0x17, 0xc5, 0xe0,

    /* U+00E1 "á" */
    0x11, 0x3c, 0x17, 0xc5, 0xe0,

    /* U+00E2 "â" */
    0x70, 0x3c, 0x17, 0xc5, 0xe0,

    /* U+00E3 "ã" */
    0x70, 0x3c, 0x17, 0xc5, 0xe0,

    /* U+00E4 "ä" */
    0x10, 0x3c, 0x17, 0xc5, 0xe0,

    /* U+00E5 "å" */
    0x22, 0x89, 0xe0, 0xbe, 0x2f,

    /* U+00E6 "æ" */
    0xf7, 0x4, 0x5f, 0xf1, 0xf, 0x70,

    /* U+00E7 "ç" */
    0x74, 0x21, 0x7, 0x10, 0x80,

    /* U+00E8 "è" */
    0x20, 0x1d, 0x1f, 0xc1, 0xc0,

    /* U+00E9 "é" */
    0x10, 0x1d, 0x1f, 0xc1, 0xc0,

    /* U+00EA "ê" */
    0x70, 0x1d, 0x1f, 0xc1, 0xc0,

    /* U+00EB "ë" */
    0x20, 0x1d, 0x1f, 0xc1, 0xc0,

    /* U+00EC "ì" */
    0x95, 0x54,

    /* U+00ED "í" */
    0x6a, 0xa8,

    /* U+00EE "î" */
    0xc5, 0x24, 0x90,

    /* U+00EF "ï" */
    0x85, 0x54,

    /* U+00F0 "ð" */
    0x41, 0x94, 0xd9, 0xc5, 0xc0,

    /* U+00F1 "ñ" */
    0x70, 0x3d, 0x18, 0xc6, 0x20,

    /* U+00F2 "ò" */
    0x20, 0x7, 0xa1, 0x86, 0x17, 0x80,

    /* U+00F3 "ó" */
    0x10, 0x7, 0xa1, 0x86, 0x17, 0x80,

    /* U+00F4 "ô" */
    0x30, 0x7, 0xa1, 0x86, 0x17, 0x80,

    /* U+00F5 "õ" */
    0x70, 0x7, 0xa1, 0x86, 0x17, 0x80,

    /* U+00F6 "ö" */
    0x20, 0x7, 0xa1, 0x86, 0x17, 0x80,

    /* U+00F7 "÷" */
    0x40, 0xf0, 0x40,

    /* U+00F8 "ø" */
    0x9, 0xe9, 0x69, 0xa5, 0xe0, 0x0,

    /* U+00F9 "ù" */
    0x41, 0x23, 0x18, 0xc5, 0xe0,

    /* U+00FA "ú" */
    0x20, 0x23, 0x18, 0xc5, 0xe0,

    /* U+00FB "û" */
    0x60, 0x23, 0x18, 0xc5, 0xe0,

    /* U+00FC "ü" */
    0x50, 0x23, 0x18, 0xc5, 0xe0,

    /* U+00FD "ý" */
    0x11, 0x23, 0x15, 0x28, 0x84, 0xc0,

    /* U+00FE "þ" */
    0x84, 0x3d, 0x18, 0xc7, 0xd0, 0x80,

    /* U+00FF "ÿ" */
    0x50, 0x23, 0x15, 0x28, 0x84, 0xc0,

    /* U+0150 "Ő" */
    0x18, 0x71, 0x14, 0x18, 0x30, 0x51, 0x1c,

    /* U+0151 "ő" */
    0x28, 0x7, 0xa1, 0x86, 0x17, 0x80,

    /* U+0170 "Ű" */
    0x2a, 0x18, 0x61, 0x86, 0x18, 0x5e,

    /* U+0171 "ű" */
    0x30, 0x23, 0x18, 0xc5, 0xe0,

    /* U+20A1 "₡" */
    0x4, 0x79, 0x64, 0xca, 0x96, 0x1c, 0x1e, 0x10,

    /* U+20A3 "₣" */
    0x7d, 0x4, 0x1f, 0x43, 0xc4, 0x0,

    /* U+20A4 "₤" */
    0x3d, 0x4, 0x3e, 0xf9, 0xf, 0xc0,

    /* U+20A6 "₦" */
    0x42, 0x62, 0x52, 0xff, 0xff, 0x46, 0x42,

    /* U+20A7 "₧" */
    0xf8, 0x1, 0xa, 0x2, 0x1e, 0xfc, 0x29, 0xf,
    0x91, 0xd0, 0x20, 0x60, 0x6f, 0x80,

    /* U+20A9 "₩" */
    0x84, 0x28, 0xc5, 0x29, 0x7f, 0xff, 0xfe, 0x63,
    0x4, 0x20,

    /* U+20AB "₫" */
    0x3c, 0x27, 0xa2, 0x8a, 0x27, 0xbe,

    /* U+20AC "€" */
    0x1e, 0x20, 0xfc, 0x40, 0xfc, 0x20, 0x1e,

    /* U+20AD "₭" */
    0x45, 0x25, 0x3e, 0x51, 0x24, 0x40,

    /* U+20AE "₮" */
    0xf9, 0xc, 0xd3, 0x70, 0x80,

    /* U+20B1 "₱" */
    0x7c, 0xff, 0x42, 0xff, 0x7c, 0x40, 0x40,

    /* U+20B2 "₲" */
    0x10, 0xe5, 0x64, 0x92, 0x55, 0x4f, 0x10,

    /* U+20B4 "₴" */
    0x78, 0xb, 0xf8, 0xf, 0xe8, 0xf, 0x0,

    /* U+20B5 "₵" */
    0x10, 0x79, 0x44, 0x89, 0x12, 0x14, 0x1e, 0x10,

    /* U+20B8 "₸" */
    0x77, 0xc8, 0x42, 0x10, 0x80,

    /* U+20B9 "₹" */
    0x7d, 0xfc, 0x10, 0x47, 0x1, 0x2, 0x0,

    /* U+20BA "₺" */
    0x41, 0x85, 0x19, 0xc5, 0x37, 0x0,

    /* U+20BC "₼" */
    0x10, 0x71, 0x54, 0x99, 0x32, 0x64, 0xc1,

    /* U+20BD "₽" */
    0x7c, 0x85, 0xa, 0x17, 0xde, 0x10, 0x0,

    /* U+20BF "₿" */
    0x53, 0xe8, 0x61, 0xfa, 0x18, 0x7e, 0x50
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 42, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 42, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 7, .adv_w = 102, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 13, .adv_w = 112, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 111, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 47, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 26, .adv_w = 78, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 30, .adv_w = 96, .box_w = 2, .box_h = 1, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 31, .adv_w = 129, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 64, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 40, .adv_w = 76, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 42, .adv_w = 92, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 44, .adv_w = 129, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 96, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 52, .adv_w = 67, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 54, .adv_w = 92, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 69, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 60, .adv_w = 69, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 63, .adv_w = 96, .box_w = 3, .box_h = 1, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 64, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 69, .adv_w = 101, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 74, .adv_w = 40, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 75, .adv_w = 96, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 76, .adv_w = 69, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 78, .adv_w = 66, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 80, .adv_w = 76, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 82, .adv_w = 165, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 165, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 165, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 91, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 112, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 165, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 175, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 107, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 48, .box_w = 2, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 48, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 48, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 48, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 133, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 130, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 92, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 266, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 274, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 127, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 102, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 107, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 158, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 361, .adv_w = 97, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 97, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 97, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 97, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 43, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 43, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 43, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 43, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 390, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 424, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 92, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 433, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 439, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 87, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 465, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 471, .adv_w = 87, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 477, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 127, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 509, .adv_w = 105, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 102, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 139, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 259, .box_w = 15, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 187, .box_w = 11, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 108, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 558, .adv_w = 127, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 133, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 583, .adv_w = 124, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 590, .adv_w = 132, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 605, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 610, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 617, .adv_w = 111, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 147, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 630, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 637, .adv_w = 131, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_2[] = {
    0x0, 0x1, 0x20, 0x21, 0x1f51, 0x1f53, 0x1f54, 0x1f56,
    0x1f57, 0x1f59, 0x1f5b, 0x1f5c, 0x1f5d, 0x1f5e, 0x1f61, 0x1f62,
    0x1f64, 0x1f65, 0x1f68, 0x1f69, 0x1f6a, 0x1f6c, 0x1f6d, 0x1f6f
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 160, .range_length = 13, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 174, .range_length = 82, .glyph_id_start = 14,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 336, .range_length = 8048, .glyph_id_start = 96,
        .unicode_list = unicode_list_2, .glyph_id_ofs_list = NULL, .list_length = 24, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 3,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};

extern const lv_font_t lv_font_montserrat_10;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t font_montserrat_10_hun = {
#else
lv_font_t font_montserrat_10_hun = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 11,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .static_bitmap = 0,
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &lv_font_montserrat_10,
#endif
    .user_data = NULL,
};



#endif /*#if FONT_MONTSERRAT_10_HUN*/
