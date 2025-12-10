/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --no-compress --stride 1 --align 1 --font Montserrat-Regular.ttf --symbols őűŐŰ --range 160-255,8352-8399 --font NotoEmoji-VariableFont_wght.ttf --symbols 😀😁😂🤣😃😄😎😋😊😉😆😅🙂🤗🫡😀😃😄😂😅🤣 --format lvgl -o font_montserrat_12_hun.c
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



#ifndef FONT_MONTSERRAT_12_HUN
#define FONT_MONTSERRAT_12_HUN 1
#endif

#if FONT_MONTSERRAT_12_HUN

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+00A0 " " */
    0x0,

    /* U+00A1 "¡" */
    0xbe,

    /* U+00A2 "¢" */
    0x10, 0x43, 0xb5, 0x92, 0x4d, 0x5e, 0x10, 0x40,

    /* U+00A3 "£" */
    0x3c, 0xc5, 0x2, 0xf, 0x88, 0x10, 0x7f,

    /* U+00A4 "¤" */
    0x0, 0x5d, 0x63, 0x41, 0x41, 0x63, 0x5d, 0x0,

    /* U+00A5 "¥" */
    0x41, 0x20, 0x88, 0x82, 0x87, 0xf0, 0x41, 0xfc,
    0x10,

    /* U+00A6 "¦" */
    0xf3, 0xc0,

    /* U+00A7 "§" */
    0x7c, 0x20, 0xe8, 0xc5, 0xc1, 0xf, 0x80,

    /* U+00A8 "¨" */
    0xa0,

    /* U+00A9 "©" */
    0x3e, 0x3f, 0xac, 0x34, 0x1a, 0xd, 0x85, 0xfc,
    0x7c,

    /* U+00AA "ª" */
    0xf7, 0x97,

    /* U+00AB "«" */
    0x5a, 0xa5,

    /* U+00AC "¬" */
    0xf8, 0x42,

    /* U+00AE "®" */
    0x3e, 0x3f, 0xa8, 0xb4, 0x5b, 0xcd, 0x15, 0x8c,
    0x7c,

    /* U+00AF "¯" */
    0xe0,

    /* U+00B0 "°" */
    0x69, 0x96,

    /* U+00B1 "±" */
    0x21, 0x3e, 0x42, 0x3, 0xe0,

    /* U+00B2 "²" */
    0xf1, 0x24, 0xf0,

    /* U+00B3 "³" */
    0x78, 0x8c, 0x17, 0x80,

    /* U+00B4 "´" */
    0x70,

    /* U+00B5 "µ" */
    0x86, 0x18, 0x61, 0x8f, 0xd8, 0x20,

    /* U+00B6 "¶" */
    0x7e, 0xe5, 0xcb, 0x91, 0x22, 0x44, 0x89, 0x12,
    0x24,

    /* U+00B7 "·" */
    0x80,

    /* U+00B8 "¸" */
    0x9c,

    /* U+00B9 "¹" */
    0xc9, 0x2e,

    /* U+00BA "º" */
    0x69, 0x96,

    /* U+00BB "»" */
    0x51, 0x4a, 0xa0,

    /* U+00BC "¼" */
    0xc1, 0x8, 0x41, 0x10, 0x22, 0x4e, 0x88, 0x22,
    0x84, 0xf9, 0x2,

    /* U+00BD "½" */
    0xc2, 0x10, 0x84, 0x41, 0x27, 0xe8, 0x44, 0x22,
    0x10, 0x8f,

    /* U+00BE "¾" */
    0x78, 0x81, 0x10, 0x39, 0x0, 0xa2, 0x74, 0x40,
    0x4a, 0x8, 0xf1, 0x2,

    /* U+00BF "¿" */
    0x20, 0x2, 0x8, 0x42, 0x8, 0x5e,

    /* U+00C0 "À" */
    0x10, 0x4, 0x2, 0x3, 0x1, 0x41, 0x20, 0x88,
    0xfc, 0x41, 0x40, 0x80,

    /* U+00C1 "Á" */
    0x4, 0x4, 0x2, 0x3, 0x1, 0x41, 0x20, 0x88,
    0xfc, 0x41, 0x40, 0x80,

    /* U+00C2 "Â" */
    0x18, 0x12, 0x2, 0x3, 0x1, 0x41, 0x20, 0x88,
    0xfc, 0x41, 0x40, 0x80,

    /* U+00C3 "Ã" */
    0x14, 0x16, 0x2, 0x3, 0x1, 0x41, 0x20, 0x88,
    0xfc, 0x41, 0x40, 0x80,

    /* U+00C4 "Ä" */
    0x14, 0x0, 0x2, 0x3, 0x1, 0x41, 0x20, 0x88,
    0xfc, 0x41, 0x40, 0x80,

    /* U+00C5 "Å" */
    0x1c, 0xa, 0x7, 0x1, 0x1, 0x40, 0xa0, 0x88,
    0x44, 0x7f, 0x20, 0xa0, 0x20,

    /* U+00C6 "Æ" */
    0x7, 0xf0, 0xa0, 0xa, 0x1, 0x3e, 0x22, 0x3,
    0xe0, 0x42, 0x4, 0x3f,

    /* U+00C7 "Ç" */
    0x3e, 0x62, 0x80, 0x80, 0x80, 0x80, 0x62, 0x3e,
    0x10, 0x18,

    /* U+00C8 "È" */
    0x20, 0x4f, 0xe0, 0x83, 0xe8, 0x20, 0x83, 0xf0,

    /* U+00C9 "É" */
    0x10, 0x8f, 0xe0, 0x83, 0xe8, 0x20, 0x83, 0xf0,

    /* U+00CA "Ê" */
    0x31, 0x2f, 0xe0, 0x83, 0xe8, 0x20, 0x83, 0xf0,

    /* U+00CB "Ë" */
    0x28, 0xf, 0xe0, 0x83, 0xe8, 0x20, 0x83, 0xf0,

    /* U+00CC "Ì" */
    0x44, 0x92, 0x49, 0x24,

    /* U+00CD "Í" */
    0x52, 0x49, 0x24, 0x90,

    /* U+00CE "Î" */
    0x74, 0x48, 0x42, 0x10, 0x84, 0x21, 0x0,

    /* U+00CF "Ï" */
    0xa1, 0x24, 0x92, 0x48,

    /* U+00D0 "Ð" */
    0x7e, 0x21, 0x90, 0x3e, 0x14, 0xa, 0x5, 0xc,
    0xfc,

    /* U+00D1 "Ñ" */
    0x38, 0xb2, 0xe, 0x1a, 0x32, 0x64, 0xc5, 0x87,
    0x4,

    /* U+00D2 "Ò" */
    0x10, 0x4, 0xf, 0x8c, 0x68, 0xc, 0x6, 0x3,
    0x1, 0x63, 0x1f, 0x0,

    /* U+00D3 "Ó" */
    0x4, 0x4, 0xf, 0x8c, 0x68, 0xc, 0x6, 0x3,
    0x1, 0x63, 0x1f, 0x0,

    /* U+00D4 "Ô" */
    0x18, 0x2, 0xf, 0x8c, 0x68, 0xc, 0x6, 0x3,
    0x1, 0x63, 0x1f, 0x0,

    /* U+00D5 "Õ" */
    0x1a, 0x16, 0xf, 0x8c, 0x68, 0xc, 0x6, 0x3,
    0x1, 0x63, 0x1f, 0x0,

    /* U+00D6 "Ö" */
    0x24, 0x0, 0xf, 0x8c, 0x68, 0xc, 0x6, 0x3,
    0x1, 0x63, 0x1f, 0x0,

    /* U+00D7 "×" */
    0x8a, 0x99, 0x20,

    /* U+00D8 "Ø" */
    0x2, 0x1f, 0x19, 0xd0, 0x98, 0x8c, 0x86, 0x42,
    0xc6, 0x3e, 0x20, 0x0,

    /* U+00D9 "Ù" */
    0x20, 0x22, 0xc, 0x18, 0x30, 0x60, 0xc1, 0xc6,
    0xf8,

    /* U+00DA "Ú" */
    0x8, 0x22, 0xc, 0x18, 0x30, 0x60, 0xc1, 0xc6,
    0xf8,

    /* U+00DB "Û" */
    0x30, 0x12, 0xc, 0x18, 0x30, 0x60, 0xc1, 0xc6,
    0xf8,

    /* U+00DC "Ü" */
    0x28, 0x2, 0xc, 0x18, 0x30, 0x60, 0xc1, 0xc6,
    0xf8,

    /* U+00DD "Ý" */
    0x8, 0x22, 0xa, 0x24, 0x45, 0x4, 0x8, 0x10,
    0x20,

    /* U+00DE "Þ" */
    0x81, 0xfa, 0x1c, 0x18, 0x30, 0xff, 0x40,

    /* U+00DF "ß" */
    0x7b, 0x18, 0x66, 0x86, 0x18, 0x6e,

    /* U+00E0 "à" */
    0x41, 0x1c, 0x17, 0xc6, 0x2f,

    /* U+00E1 "á" */
    0x11, 0x1c, 0x17, 0xc6, 0x2f,

    /* U+00E2 "â" */
    0x70, 0x1c, 0x17, 0xc6, 0x2f,

    /* U+00E3 "ã" */
    0x70, 0x1c, 0x17, 0xc6, 0x2f,

    /* U+00E4 "ä" */
    0x50, 0x1c, 0x17, 0xc6, 0x2f,

    /* U+00E5 "å" */
    0x72, 0x9c, 0xe0, 0xbe, 0x31, 0x78,

    /* U+00E6 "æ" */
    0x77, 0xc1, 0x8d, 0xff, 0xc4, 0x8, 0xc0, 0xe7,
    0x80,

    /* U+00E7 "ç" */
    0x7b, 0x8, 0x20, 0xc1, 0xe0, 0xc,

    /* U+00E8 "è" */
    0x20, 0x7, 0xb1, 0xfe, 0xc, 0x1e,

    /* U+00E9 "é" */
    0x10, 0x7, 0xb1, 0xfe, 0xc, 0x1e,

    /* U+00EA "ê" */
    0x30, 0x7, 0xb1, 0xfe, 0xc, 0x1e,

    /* U+00EB "ë" */
    0x28, 0x7, 0xb1, 0xfe, 0xc, 0x1e,

    /* U+00EC "ì" */
    0x44, 0x92, 0x49,

    /* U+00ED "í" */
    0x52, 0x49, 0x24,

    /* U+00EE "î" */
    0xe1, 0x24, 0x92,

    /* U+00EF "ï" */
    0xa1, 0x24, 0x92,

    /* U+00F0 "ð" */
    0x28, 0xc0, 0x9d, 0x8e, 0x18, 0x5e,

    /* U+00F1 "ñ" */
    0x78, 0xb, 0xb1, 0x86, 0x18, 0x61,

    /* U+00F2 "ò" */
    0x20, 0x7, 0xb3, 0x86, 0x1c, 0xde,

    /* U+00F3 "ó" */
    0x10, 0x7, 0xb3, 0x86, 0x1c, 0xde,

    /* U+00F4 "ô" */
    0x30, 0x7, 0xb3, 0x86, 0x1c, 0xde,

    /* U+00F5 "õ" */
    0x70, 0x7, 0xb3, 0x86, 0x1c, 0xde,

    /* U+00F6 "ö" */
    0x28, 0x7, 0xb3, 0x86, 0x1c, 0xde,

    /* U+00F7 "÷" */
    0x20, 0x3e, 0x2, 0x0,

    /* U+00F8 "ø" */
    0x9, 0xed, 0xe9, 0xa7, 0xb7, 0x90,

    /* U+00F9 "ù" */
    0x20, 0x8, 0x61, 0x86, 0x18, 0xdd,

    /* U+00FA "ú" */
    0x10, 0x8, 0x61, 0x86, 0x18, 0xdd,

    /* U+00FB "û" */
    0x30, 0x8, 0x61, 0x86, 0x18, 0xdd,

    /* U+00FC "ü" */
    0x48, 0x8, 0x61, 0x86, 0x18, 0xdd,

    /* U+00FD "ý" */
    0x10, 0x8, 0x51, 0x48, 0xa3, 0x4, 0x23, 0x80,

    /* U+00FE "þ" */
    0x82, 0xf, 0xb3, 0x86, 0x1c, 0xfe, 0x82, 0x0,

    /* U+00FF "ÿ" */
    0x68, 0x8, 0x51, 0x48, 0xa3, 0x4, 0x23, 0x80,

    /* U+0150 "Ő" */
    0xa, 0x0, 0xf, 0x8c, 0x68, 0xc, 0x6, 0x3,
    0x1, 0x63, 0x1f, 0x0,

    /* U+0151 "ő" */
    0x28, 0x7, 0xb3, 0x86, 0x1c, 0xde,

    /* U+0170 "Ű" */
    0x18, 0x2, 0xc, 0x18, 0x30, 0x60, 0xc1, 0xc6,
    0xf8,

    /* U+0171 "ű" */
    0x28, 0x8, 0x61, 0x86, 0x18, 0xdd,

    /* U+20A1 "₡" */
    0x2, 0xa, 0x3c, 0x74, 0x94, 0x94, 0x98, 0xa8,
    0x68, 0x3e, 0x30, 0x10,

    /* U+20A3 "₣" */
    0x7e, 0x81, 0x2, 0x7, 0xc8, 0x3e, 0x20,

    /* U+20A4 "₤" */
    0x3c, 0xc1, 0x7, 0xcf, 0x88, 0x10, 0x7f,

    /* U+20A6 "₦" */
    0x41, 0x30, 0x94, 0x5f, 0xff, 0xfa, 0x29, 0xc,
    0x82,

    /* U+20A7 "₧" */
    0xfc, 0x0, 0x21, 0x90, 0x8, 0x2f, 0x3a, 0x9,
    0x10, 0x86, 0x44, 0x3f, 0x10, 0xf8, 0x4, 0x6,
    0x1, 0xde,

    /* U+20A9 "₩" */
    0x43, 0x9, 0xc, 0x24, 0x30, 0xbf, 0xff, 0xff,
    0xfc, 0x61, 0x81, 0x86, 0x6, 0x18,

    /* U+20AB "₫" */
    0x1e, 0x9, 0xf6, 0x68, 0x50, 0xb3, 0x3e, 0x1,
    0xf8,

    /* U+20AC "€" */
    0x1e, 0x18, 0x10, 0x1f, 0x8f, 0xc2, 0x0, 0xc0,
    0x3c,

    /* U+20AD "₭" */
    0x46, 0x89, 0x22, 0x8f, 0xca, 0x12, 0x22,

    /* U+20AE "₮" */
    0xfe, 0x20, 0x50, 0xc7, 0x47, 0x14, 0x8,

    /* U+20B1 "₱" */
    0x7e, 0x21, 0xbf, 0xff, 0xf4, 0x33, 0xf1, 0x0,
    0x80,

    /* U+20B2 "₲" */
    0x8, 0x8, 0x3e, 0x69, 0xc8, 0x88, 0x89, 0x89,
    0x69, 0x3e, 0x8, 0x8,

    /* U+20B4 "₴" */
    0x3c, 0x2, 0x2, 0xff, 0xff, 0x40, 0x42, 0x3c,

    /* U+20B5 "₵" */
    0x8, 0x8, 0x3e, 0x69, 0xc8, 0x88, 0x88, 0x88,
    0x69, 0x3e, 0x8, 0x8,

    /* U+20B8 "₸" */
    0xff, 0xfc, 0x40, 0x81, 0x2, 0x4, 0x8,

    /* U+20B9 "₹" */
    0x7f, 0xff, 0x2, 0x4, 0x78, 0x8, 0x4, 0x2,

    /* U+20BA "₺" */
    0x20, 0x2c, 0x34, 0xf8, 0x61, 0x21, 0x22, 0x3c,

    /* U+20BC "₼" */
    0x8, 0x8, 0x3c, 0x4a, 0x89, 0x89, 0x89, 0x89,
    0x89, 0x81,

    /* U+20BD "₽" */
    0x7e, 0x43, 0x41, 0x43, 0x7e, 0x40, 0xf8, 0x40,

    /* U+20BF "₿" */
    0x28, 0x53, 0xf4, 0x18, 0x3f, 0xa0, 0xc1, 0x83,
    0xf8, 0xa1, 0x40,

    /* U+1F600 "😀" */
    0xf, 0x81, 0x83, 0x18, 0xc, 0x80, 0x28, 0x88,
    0xc4, 0x46, 0x0, 0x37, 0xfd, 0x5f, 0xd3, 0x7d,
    0x8c, 0x18, 0x1f, 0x0,

    /* U+1F601 "😁" */
    0xf, 0x81, 0x83, 0x18, 0xc, 0x80, 0x29, 0x98,
    0xc0, 0x26, 0x0, 0x3f, 0xfd, 0x71, 0x53, 0x7d,
    0x8d, 0x98, 0x1f, 0x0,

    /* U+1F602 "😂" */
    0x7, 0xc0, 0x10, 0x60, 0x40, 0x61, 0x80, 0xc4,
    0xc6, 0x40, 0x0, 0xb8, 0x2, 0xef, 0xfd, 0xf,
    0xec, 0x4f, 0xa0, 0x60, 0x80, 0x3e, 0x0,

    /* U+1F603 "😃" */
    0xf, 0x81, 0x83, 0x18, 0xc, 0x91, 0x28, 0x88,
    0xc4, 0x46, 0x0, 0x37, 0xfd, 0x5f, 0xd3, 0x7d,
    0x8c, 0x18, 0x1f, 0x0,

    /* U+1F604 "😄" */
    0xf, 0x81, 0x83, 0x18, 0xc, 0x80, 0x28, 0x88,
    0xca, 0x86, 0x0, 0x37, 0xfd, 0x5f, 0xd3, 0x7d,
    0x8c, 0x18, 0x1f, 0x0,

    /* U+1F605 "😅" */
    0xf, 0x80, 0xc1, 0xe6, 0x2, 0x50, 0x9, 0x8d,
    0xfe, 0x0, 0x28, 0x0, 0xaf, 0xfc, 0x5f, 0xd1,
    0xbe, 0x83, 0x4, 0x3, 0xe0,

    /* U+1F606 "😆" */
    0xf, 0x81, 0x83, 0x18, 0xc, 0x80, 0x28, 0x88,
    0xcc, 0x66, 0x0, 0x37, 0xfd, 0x5f, 0xd3, 0x7d,
    0x8c, 0x18, 0x1f, 0x0,

    /* U+1F609 "😉" */
    0xf, 0x81, 0x83, 0x1a, 0xc, 0x80, 0x28, 0x88,
    0xc4, 0xc6, 0x0, 0x31, 0x11, 0x47, 0x13, 0x1,
    0x8c, 0x18, 0x1f, 0x0,

    /* U+1F60A "😊" */
    0xf, 0x81, 0x83, 0x18, 0xc, 0x80, 0x28, 0x88,
    0xca, 0xa6, 0x20, 0xb0, 0x1, 0x47, 0x13, 0x1,
    0x8c, 0x18, 0x1f, 0x0,

    /* U+1F60B "😋" */
    0xf, 0x83, 0x4, 0x60, 0x24, 0x1, 0x99, 0x98,
    0x1, 0x80, 0x1a, 0x5, 0x50, 0xe4, 0xf1, 0x31,
    0x10, 0xfe,

    /* U+1F60E "😎" */
    0xf, 0x80, 0x83, 0x8, 0x5, 0xff, 0xf7, 0xd7,
    0xbe, 0x7d, 0xe3, 0xf0, 0x1, 0x4f, 0x91, 0x0,
    0x84, 0x18, 0x1f, 0x0,

    /* U+1F642 "🙂" */
    0xf, 0x81, 0x83, 0x18, 0xc, 0x80, 0x28, 0x88,
    0xc4, 0x46, 0x0, 0x30, 0x1, 0x47, 0x13, 0x1,
    0x8c, 0x18, 0x1f, 0x0,

    /* U+1F917 "🤗" */
    0x7, 0xc0, 0x10, 0x60, 0x40, 0x61, 0x67, 0x44,
    0x80, 0x48, 0x4, 0x81, 0xf1, 0x34, 0x1e, 0xb4,
    0x5b, 0x8, 0x8e, 0x11, 0x1e, 0x32, 0x33, 0x9b,
    0x80,

    /* U+1F923 "🤣" */
    0xf, 0x81, 0x82, 0x10, 0x5c, 0x85, 0x18, 0x14,
    0xc0, 0x5e, 0x3, 0xb7, 0x39, 0x93, 0xcb, 0x7c,
    0x49, 0xc4, 0x48, 0xc1, 0xf8, 0x0,

    /* U+1FAE1 "🫡" */
    0x1f, 0x3, 0x2c, 0x23, 0x99, 0x34, 0x24, 0xcc,
    0xbc, 0x65, 0x0, 0x28, 0x1, 0x4f, 0x99, 0x0,
    0x84, 0x18, 0x1f, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 50, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 50, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 10, .adv_w = 122, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 25, .adv_w = 133, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 56, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 36, .adv_w = 94, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 43, .adv_w = 115, .box_w = 3, .box_h = 1, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 44, .adv_w = 155, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 77, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 55, .adv_w = 92, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 57, .adv_w = 110, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 59, .adv_w = 155, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 115, .box_w = 3, .box_h = 1, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 69, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 71, .adv_w = 110, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 83, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 79, .adv_w = 83, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 83, .adv_w = 115, .box_w = 3, .box_h = 2, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 84, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 90, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 99, .adv_w = 48, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 100, .adv_w = 115, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 101, .adv_w = 83, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 103, .adv_w = 79, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 105, .adv_w = 92, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 108, .adv_w = 198, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 198, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 198, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 109, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 147, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 138, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 198, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 136, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 242, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 58, .box_w = 3, .box_h = 10, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 58, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 58, .box_w = 5, .box_h = 10, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 58, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 293, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 156, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 110, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 374, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 386, .adv_w = 152, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 152, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 152, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 152, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 122, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 138, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 113, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 113, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 113, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 113, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 113, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 113, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 189, .box_w = 11, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 108, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 490, .adv_w = 116, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 116, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 116, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 116, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 52, .box_w = 3, .box_h = 8, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 52, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 52, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 52, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 526, .adv_w = 113, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 550, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 110, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 572, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 578, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 610, .adv_w = 130, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 618, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 626, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 152, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 653, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 671, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 678, .adv_w = 122, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 167, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 694, .adv_w = 310, .box_w = 18, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 225, .box_w = 14, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 726, .adv_w = 130, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 735, .adv_w = 152, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 744, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 129, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 767, .adv_w = 148, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 779, .adv_w = 158, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 787, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 799, .adv_w = 138, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 138, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 133, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 822, .adv_w = 176, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 142, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 157, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 851, .adv_w = 244, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 871, .adv_w = 244, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 891, .adv_w = 244, .box_w = 15, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 914, .adv_w = 244, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 934, .adv_w = 244, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 954, .adv_w = 244, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 975, .adv_w = 244, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 995, .adv_w = 244, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1015, .adv_w = 244, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1035, .adv_w = 244, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1053, .adv_w = 244, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1073, .adv_w = 244, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1093, .adv_w = 244, .box_w = 15, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1118, .adv_w = 244, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1140, .adv_w = 244, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_2[] = {
    0x0, 0x1, 0x20, 0x21, 0x1f51, 0x1f53, 0x1f54, 0x1f56,
    0x1f57, 0x1f59, 0x1f5b, 0x1f5c, 0x1f5d, 0x1f5e, 0x1f61, 0x1f62,
    0x1f64, 0x1f65, 0x1f68, 0x1f69, 0x1f6a, 0x1f6c, 0x1f6d, 0x1f6f
};

static const uint16_t unicode_list_3[] = {
    0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x9,
    0xa, 0xb, 0xe, 0x42, 0x317, 0x323, 0x4e1
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
    },
    {
        .range_start = 128512, .range_length = 1250, .glyph_id_start = 120,
        .unicode_list = unicode_list_3, .glyph_id_ofs_list = NULL, .list_length = 15, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
    .cmap_num = 4,
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
const lv_font_t font_montserrat_12_hun = {
#else
lv_font_t font_montserrat_12_hun = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if FONT_MONTSERRAT_12_HUN*/
