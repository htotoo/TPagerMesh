/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: --bpp 1 --size 10 --no-compress --stride 1 --align 1 --font Montserrat-Regular.ttf --symbols éáűúőóüöíÍÉÁŰÚŐÓÜÖ@&!%+"'-.,;>*< --range 160-255,8352-8399 --font NotoEmoji-VariableFont_wght.ttf --symbols 😀😁😂🤣😃😄😎😋😊😉😆😅🙂🤗🫡🖖👋👍🤖📡🙋🥳😬🙂🖐️🚕😁 😜🚬👀😋☕️😜👌☁️🥱🙋⏰🆙🌅☕🥐🎙️📻🎧 🦉🏓🌛💤🛏️❤️🚨🌞🙋🌌😁🎄🥳😅🚓 🚑 🚒 🧑‍🚀🏰🔋📊🥕🏡🐕‍🦺🌡️🚘 🚐🗼🔌🗼🌐🌋🏠⛰️🚂🚶‍♂🏢🌲🛸🐘🐓📟😶‍🌫️🤹🏫🛰👽🧳🚚 🇭🇺🚙🔭📨📲 🇵🇱❄️🔆🇨🇿🚧💰🌐🇷🇸🏛️🧊🦊🔱📶🐺🎯 --format lvgl -o font_montserrat_10_hun.c
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
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfa,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0025 "%" */
    0xe4, 0xa8, 0xa8, 0x56, 0x29, 0x29, 0x6,

    /* U+0026 "&" */
    0x70, 0xa0, 0xc2, 0x88, 0x91, 0x9c, 0x0,

    /* U+0027 "'" */
    0xe0,

    /* U+002A "*" */
    0x5d, 0x0,

    /* U+002B "+" */
    0x21, 0x3e, 0x40,

    /* U+002C "," */
    0xc0,

    /* U+002D "-" */
    0xc0,

    /* U+002E "." */
    0x80,

    /* U+003B ";" */
    0x8c,

    /* U+003C "<" */
    0x36, 0x18, 0x30,

    /* U+003E ">" */
    0xc1, 0xc9, 0x80,

    /* U+0040 "@" */
    0x1e, 0x18, 0x69, 0xe6, 0x89, 0xa2, 0x68, 0x99,
    0xf9, 0x0, 0x3c, 0x0,

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

    /* U+200D "‍" */
    0x0,

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
    0x53, 0xe8, 0x61, 0xfa, 0x18, 0x7e, 0x50,

    /* U+23F0 "⏰" */
    0x0, 0x9a, 0xe7, 0x79, 0xb4, 0xc1, 0xb0, 0x2c,
    0x9e, 0x86, 0xe1, 0x9f, 0xc1, 0xf0,

    /* U+2601 "☁" */
    0x3, 0x80, 0xc4, 0x18, 0x22, 0x42, 0x60, 0x38,
    0x1, 0x80, 0x17, 0xe6, 0x1, 0x80,

    /* U+2615 "☕" */
    0x0, 0x1, 0x81, 0xc0, 0xf8, 0x41, 0x1f, 0xd2,
    0x9, 0x4, 0xa3, 0xb7, 0x67, 0xe0,

    /* U+2642 "♂" */
    0x3, 0xc0, 0x30, 0x14, 0xf9, 0x46, 0x20, 0x88,
    0x22, 0x8, 0x44, 0xe, 0x0,

    /* U+26F0 "⛰" */
    0x4, 0x0, 0xa0, 0xb, 0x1, 0xa8, 0x2b, 0x82,
    0xc4, 0xfb, 0xea, 0x7a, 0x7f, 0xc0,

    /* U+2744 "❄" */
    0x0, 0x4, 0x1d, 0x5b, 0x7b, 0x4b, 0x7b, 0x4f,
    0xfd, 0x57, 0xa, 0x2, 0x0,

    /* U+2764 "❤" */
    0x79, 0xed, 0xab, 0xde, 0xdd, 0xed, 0xde, 0xd5,
    0xea, 0x5e, 0xc3, 0xe8, 0xd, 0x0, 0x60,

    /* U+FE0F "️" */
    0x0,

    /* U+1F199 "🆙" */
    0xff, 0xff, 0xff, 0xfe, 0xa3, 0xaa, 0xea, 0x3a,
    0xbe, 0x2f, 0xff, 0xff, 0xff, 0xfc,

    /* U+1F1E8 "🇨" */
    0x7e, 0x21, 0x8, 0x61, 0xe0,

    /* U+1F1ED "🇭" */
    0x86, 0x18, 0x7f, 0x86, 0x18, 0x40,

    /* U+1F1F1 "🇱" */
    0x88, 0x88, 0x88, 0xf0,

    /* U+1F1F5 "🇵" */
    0xf4, 0x63, 0xe8, 0x42, 0x0,

    /* U+1F1F7 "🇷" */
    0xf2, 0x28, 0xbc, 0x92, 0x48, 0x80,

    /* U+1F1F8 "🇸" */
    0x7c, 0x20, 0xc1, 0x87, 0xc0,

    /* U+1F1FA "🇺" */
    0x86, 0x18, 0x61, 0x86, 0x37, 0x80,

    /* U+1F1FF "🇿" */
    0xf8, 0x84, 0x44, 0x43, 0xe0,

    /* U+1F305 "🌅" */
    0xff, 0xf6, 0xe7, 0xbc, 0xdf, 0x3d, 0xef, 0xe3,
    0xff, 0xfc, 0xf9, 0xae, 0x30, 0x7, 0xff, 0x80,

    /* U+1F30B "🌋" */
    0x0, 0xa, 0xd, 0xd6, 0xf0, 0x2, 0xe0, 0xe8,
    0xa6, 0xa0, 0xc0, 0x5f, 0xc0,

    /* U+1F30C "🌌" */
    0xff, 0xfc, 0xe7, 0xf7, 0xff, 0xbd, 0xdf, 0xe6,
    0xef, 0x7e, 0x3f, 0xfd, 0xff, 0xff, 0xff, 0x80,

    /* U+1F310 "🌐" */
    0x3f, 0x8c, 0xa9, 0xff, 0x52, 0x5f, 0xff, 0x89,
    0x69, 0x4b, 0xfe, 0x65, 0x47, 0xf0,

    /* U+1F31B "🌛" */
    0x6, 0x1, 0x40, 0x28, 0x9, 0x2, 0x43, 0xd0,
    0x84, 0x21, 0xf8, 0x90, 0x63, 0xe0,

    /* U+1F31E "🌞" */
    0x16, 0x17, 0xa2, 0x13, 0x2b, 0x58, 0xa0, 0x2c,
    0xcd, 0x4, 0x73, 0x87, 0x80,

    /* U+1F321 "🌡" */
    0x72, 0xa5, 0x25, 0x5a, 0xdd, 0xff, 0x5c,

    /* U+1F32B "🌫" */
    0xff, 0xf1, 0xde, 0x7c, 0xd0, 0x1d, 0xc3, 0x44,
    0x60, 0x7c, 0x7, 0x81, 0x33, 0xc7, 0xff, 0x80,

    /* U+1F332 "🌲" */
    0x8, 0x7, 0x3, 0x20, 0x88, 0x3f, 0x10, 0x23,
    0xf3, 0x2, 0xe1, 0x8f, 0xc0, 0xc0,

    /* U+1F384 "🎄" */
    0x0, 0x3, 0x0, 0x60, 0xc4, 0x1a, 0x1b, 0x63,
    0x51, 0xbe, 0xc0, 0x8f, 0xc0, 0xc0,

    /* U+1F399 "🎙" */
    0x10, 0x6c, 0x9c, 0xda, 0x8a, 0x4e, 0x59, 0x4e,
    0x3e, 0x1e, 0xc,

    /* U+1F3A7 "🎧" */
    0x1e, 0x18, 0x45, 0xea, 0x86, 0xc1, 0x70, 0x27,
    0x39, 0xfe, 0x6d, 0x9b, 0x63, 0xf0,

    /* U+1F3AF "🎯" */
    0x1f, 0x3, 0x18, 0x44, 0x49, 0xb7, 0xbe, 0xed,
    0x7a, 0xd1, 0xaa, 0xea, 0x51, 0x43, 0xf8, 0x1f,
    0x0,

    /* U+1F3D3 "🏓" */
    0x1f, 0x89, 0xf2, 0x7c, 0xff, 0x3f, 0xcf, 0xf2,
    0xf8, 0xbc, 0x50, 0x28, 0x6, 0x0,

    /* U+1F3DB "🏛" */
    0x4, 0x3, 0xe1, 0xbb, 0x3f, 0xf7, 0xfc, 0xff,
    0x95, 0x52, 0xaa, 0x7f, 0xcf, 0xfb, 0xff, 0x80,

    /* U+1F3E0 "🏠" */
    0x4, 0x5, 0x40, 0xfc, 0x28, 0xca, 0xd, 0x80,
    0xdf, 0x93, 0xfa, 0x4e, 0x4e, 0x38, 0x38, 0x0,

    /* U+1F3E1 "🏡" */
    0x60, 0x1c, 0x2, 0x58, 0x46, 0x89, 0xa9, 0xe3,
    0x9c, 0x39, 0x33, 0x66, 0x67, 0x38, 0x38, 0x0,

    /* U+1F3E2 "🏢" */
    0x7, 0x3, 0xff, 0x9e, 0xbc, 0xa0, 0xa5, 0x5,
    0x3d, 0x79, 0x41, 0x4a, 0xea, 0x7b, 0xf2, 0xda,
    0x9f, 0xfc,

    /* U+1F3EB "🏫" */
    0x4, 0x1, 0xc0, 0x6c, 0x7f, 0xff, 0x6f, 0x59,
    0x7b, 0xbf, 0x77, 0xf6, 0xff, 0xdf, 0xff, 0x80,

    /* U+1F3F0 "🏰" */
    0x24, 0x29, 0xc9, 0x13, 0x77, 0xfa, 0x9f, 0x6a,
    0x6b, 0xcd, 0xe9, 0xb7, 0x2f, 0xfc,

    /* U+1F413 "🐓" */
    0x0, 0xc, 0xe, 0xbb, 0x51, 0xe4, 0x57, 0x35,
    0xf8, 0x88, 0x1c, 0xa, 0x1, 0x80,

    /* U+1F415 "🐕" */
    0x3a, 0x39, 0xcc, 0x53, 0x58, 0x4d, 0x9, 0x75,
    0xa8, 0xaa, 0x3a, 0x8f, 0x40, 0x40,

    /* U+1F418 "🐘" */
    0x22, 0x7, 0xc8, 0x40, 0x84, 0x4c, 0xc5, 0x2d,
    0xa2, 0x68, 0x37, 0xbc, 0x5b, 0xa3, 0x56, 0xc,
    0x0,

    /* U+1F43A "🐺" */
    0x60, 0xa7, 0xda, 0x1d, 0x82, 0x50, 0xa0, 0x1b,
    0x3d, 0xb3, 0x1f, 0x7, 0x80, 0xc0,

    /* U+1F440 "👀" */
    0x38, 0xc4, 0x52, 0xc6, 0x1a, 0x29, 0xb2, 0xda,
    0x29, 0x87, 0x14, 0x52, 0x38, 0xc0,

    /* U+1F44B "👋" */
    0x2, 0x0, 0x43, 0xc8, 0xae, 0x55, 0x9a, 0x65,
    0x15, 0x81, 0x90, 0x42, 0x30, 0x78,

    /* U+1F44C "👌" */
    0x30, 0x48, 0x64, 0x52, 0x3d, 0xf1, 0xc9, 0xc9,
    0xb9, 0x42, 0x3c,

    /* U+1F44D "👍" */
    0x6, 0x1, 0x80, 0x60, 0x28, 0x33, 0xb8, 0xa8,
    0x36, 0x1f, 0x82, 0x5c, 0xe0, 0xf8,

    /* U+1F47D "👽" */
    0x1e, 0x18, 0x64, 0xa, 0x1, 0xa1, 0x6c, 0xdb,
    0x35, 0x2, 0x6d, 0x8c, 0xc0, 0xc0,

    /* U+1F4A4 "💤" */
    0x4, 0x1, 0x0, 0x8d, 0xa2, 0x24, 0xd0, 0x4,
    0x1, 0x80,

    /* U+1F4B0 "💰" */
    0x7, 0x82, 0x20, 0x8, 0x1a, 0x3a, 0x13, 0x48,
    0x92, 0x52, 0x9c, 0x70, 0x33, 0xf0,

    /* U+1F4CA "📊" */
    0xff, 0xf0, 0x7, 0xff, 0xc0, 0x5f, 0xff, 0xff,
    0xed, 0x2f, 0xff, 0xb4, 0xbf, 0xff, 0xff, 0x80,

    /* U+1F4DF "📟" */
    0xff, 0xf7, 0xf6, 0xd6, 0xdf, 0xd8, 0x3, 0x56,
    0x7f, 0xf8,

    /* U+1F4E1 "📡" */
    0xe1, 0x26, 0x48, 0x61, 0xf8, 0x63, 0x14, 0xa3,
    0xa4, 0x59, 0x3f, 0xcb, 0x3, 0xe0,

    /* U+1F4E8 "📨" */
    0xbf, 0xec, 0xd, 0x43, 0x6d, 0xaa, 0x4c, 0x80,
    0x9f, 0xe0,

    /* U+1F4F2 "📲" */
    0xf, 0xc3, 0x10, 0xbc, 0x2f, 0x48, 0x7a, 0xb4,
    0x84, 0x21, 0xb, 0xc2, 0x10, 0xfc,

    /* U+1F4F6 "📶" */
    0xff, 0xff, 0xff, 0xef, 0xfb, 0xfe, 0xfd, 0xbd,
    0x6f, 0x5b, 0xd6, 0xff, 0xff, 0xfc,

    /* U+1F4FB "📻" */
    0x0, 0x40, 0x1c, 0x1f, 0xfd, 0x80, 0x3b, 0xff,
    0xc3, 0xfe, 0xdb, 0xf6, 0x21, 0xb3, 0x6c, 0xb,
    0x7f, 0xfe,

    /* U+1F506 "🔆" */
    0x0, 0x2, 0x2, 0x18, 0x30, 0x12, 0x34, 0xb1,
    0x20, 0x30, 0x21, 0x82, 0x0, 0x80,

    /* U+1F50B "🔋" */
    0x3, 0xf8, 0x7f, 0x86, 0x18, 0x61, 0xb6, 0x17,
    0x80,

    /* U+1F50C "🔌" */
    0x20, 0x6, 0x2, 0x78, 0x65, 0x87, 0x48, 0x51,
    0x14, 0x21, 0x86, 0xf, 0xc0, 0x64, 0x3, 0x0,

    /* U+1F52D "🔭" */
    0x40, 0x1a, 0x3, 0x58, 0x68, 0xc2, 0xee, 0xf,
    0xc3, 0x80, 0x68, 0x15, 0x2, 0x90, 0x0, 0x0,

    /* U+1F531 "🔱" */
    0x24, 0x8d, 0xaa, 0xbd, 0x76, 0xaa, 0xcd, 0x59,
    0xa7, 0x53, 0x16, 0x13, 0x1, 0xc0,

    /* U+1F590 "🖐" */
    0xc, 0xe, 0x8b, 0xb3, 0xe8, 0xba, 0x20, 0xb4,
    0x15, 0x1e, 0x45, 0x10, 0x83, 0xc0,

    /* U+1F596 "🖖" */
    0x2, 0x9, 0x45, 0x72, 0xdc, 0x6b, 0x12, 0x74,
    0x15, 0xe, 0x45, 0x18, 0x83, 0xc0,

    /* U+1F5FC "🗼" */
    0x8, 0x10, 0x60, 0xc1, 0x8c, 0x8e, 0x16, 0x5d,
    0x4f, 0x8,

    /* U+1F600 "😀" */
    0x1f, 0x4, 0x11, 0x1, 0x40, 0x98, 0x93, 0x0,
    0x6f, 0xec, 0xf9, 0x4e, 0x44, 0x10, 0x7c, 0x0,

    /* U+1F601 "😁" */
    0x1f, 0x6, 0x11, 0x1, 0x40, 0x19, 0x13, 0x54,
    0x60, 0xf, 0xfd, 0x7f, 0x45, 0xd0, 0x7c, 0x0,

    /* U+1F602 "😂" */
    0x7, 0x80, 0xc6, 0x8, 0x8, 0xa0, 0xe4, 0x89,
    0x10, 0x13, 0x7f, 0xa3, 0xfe, 0x27, 0x40, 0x86,
    0x3, 0xc0,

    /* U+1F603 "😃" */
    0x1f, 0x4, 0x11, 0x1, 0x44, 0x98, 0x93, 0x0,
    0x6f, 0xec, 0xf9, 0x4e, 0x44, 0x10, 0x7c, 0x0,

    /* U+1F604 "😄" */
    0x1f, 0x6, 0x11, 0x1, 0x40, 0x19, 0xb3, 0x0,
    0x6f, 0xed, 0xfd, 0x4e, 0x44, 0x10, 0x7c, 0x0,

    /* U+1F605 "😅" */
    0x1e, 0x6, 0x39, 0x2, 0xc0, 0x58, 0x9f, 0x0,
    0xaf, 0xf4, 0xfc, 0x4e, 0x84, 0x20, 0x78, 0x0,

    /* U+1F606 "😆" */
    0x1f, 0x6, 0x11, 0x1, 0x40, 0x18, 0xa3, 0x2,
    0x6f, 0xec, 0xf9, 0x4e, 0x44, 0x10, 0x7c, 0x0,

    /* U+1F609 "😉" */
    0x1f, 0x6, 0x11, 0x41, 0x50, 0x19, 0x23, 0x2,
    0x64, 0xc, 0x71, 0x40, 0x44, 0x10, 0x7c, 0x0,

    /* U+1F60A "😊" */
    0x1f, 0x6, 0x11, 0x1, 0x40, 0x19, 0xb3, 0x14,
    0x64, 0xc, 0x1, 0x4e, 0x44, 0x10, 0x7c, 0x0,

    /* U+1F60B "😋" */
    0x1e, 0x8, 0x64, 0x6, 0x1, 0x93, 0x60, 0x18,
    0xe, 0x86, 0x5e, 0x48, 0x91, 0xd8,

    /* U+1F60E "😎" */
    0x1e, 0x8, 0x64, 0x7, 0xff, 0xfb, 0xfc, 0xfe,
    0xe, 0x45, 0x4e, 0x48, 0x61, 0xe0,

    /* U+1F61C "😜" */
    0xf, 0x6, 0x11, 0x1, 0x20, 0x99, 0x7b, 0x45,
    0x60, 0x4d, 0xfe, 0x55, 0x86, 0x20, 0x78, 0x0,

    /* U+1F62C "😬" */
    0x1f, 0x6, 0x11, 0x1, 0x40, 0x19, 0x13, 0x0,
    0x6f, 0xee, 0xfd, 0x7f, 0x44, 0x10, 0x7c, 0x0,

    /* U+1F636 "😶" */
    0x1f, 0x6, 0x11, 0x1, 0x40, 0x19, 0x13, 0x0,
    0x60, 0xc, 0x1, 0x40, 0x44, 0x10, 0x7c, 0x0,

    /* U+1F642 "🙂" */
    0x1f, 0x6, 0x11, 0x1, 0x40, 0x19, 0x13, 0x0,
    0x60, 0xc, 0x71, 0x40, 0x44, 0x10, 0x7c, 0x0,

    /* U+1F64B "🙋" */
    0x60, 0xa0, 0xa0, 0xde, 0xa1, 0x85, 0x8d, 0x81,
    0x41, 0x61, 0x3f,

    /* U+1F680 "🚀" */
    0x1, 0xc1, 0x90, 0x84, 0x46, 0x67, 0x28, 0x46,
    0xe0, 0xf0, 0x94, 0x3e, 0x0, 0x0,

    /* U+1F682 "🚂" */
    0x3f, 0x0, 0x20, 0xf8, 0x10, 0xf2, 0x1e, 0x7e,
    0xce, 0xe9, 0xdf, 0x67, 0xfb, 0xdf, 0xfd, 0x80,

    /* U+1F690 "🚐" */
    0x1f, 0xc1, 0x2, 0x1f, 0xe3, 0x66, 0xdf, 0xec,
    0x1, 0xff, 0xff, 0xfe, 0x30, 0xe0,

    /* U+1F691 "🚑" */
    0x6, 0x0, 0xff, 0xf, 0xf1, 0xe5, 0x32, 0xd4,
    0xed, 0x7f, 0xff, 0x3, 0xf8, 0x72, 0xfe, 0x18,
    0x20,

    /* U+1F692 "🚒" */
    0xf, 0xc0, 0xac, 0x3f, 0xc3, 0xfc, 0x34, 0x27,
    0x42, 0x74, 0x24, 0x5e, 0x9f, 0xde, 0xf3, 0x11,
    0xc0,

    /* U+1F693 "🚓" */
    0x7, 0x80, 0x8, 0x1f, 0x43, 0xaa, 0xdf, 0x9c,
    0x3, 0xff, 0xfc, 0xfb, 0x38, 0x60,

    /* U+1F695 "🚕" */
    0x3, 0x0, 0x78, 0x1f, 0xc1, 0xaa, 0xef, 0x98,
    0x71, 0xb0, 0xfc, 0x8b, 0x37, 0x60,

    /* U+1F698 "🚘" */
    0x1f, 0xc0, 0x82, 0xa, 0x29, 0xff, 0xf2, 0x2,
    0x3c, 0x69, 0x5c, 0x4e, 0xe, 0x4f, 0x91, 0xff,
    0x0,

    /* U+1F699 "🚙" */
    0x3, 0xf0, 0x20, 0x83, 0xfc, 0xef, 0xe4, 0x1,
    0xa0, 0x5, 0xe3, 0x85, 0xf6, 0x18, 0x60,

    /* U+1F69A "🚚" */
    0x7, 0xf8, 0x35, 0x41, 0xaa, 0x7d, 0x55, 0x6a,
    0xfb, 0x57, 0x9a, 0xb7, 0xab, 0xff, 0xf1, 0x84,
    0x8c, 0x38,

    /* U+1F6A7 "🚧" */
    0x60, 0xca, 0x19, 0x83, 0x7f, 0xf9, 0x27, 0xdb,
    0x7f, 0xfd, 0x2, 0xa0, 0x54, 0x9, 0x81, 0x0,

    /* U+1F6A8 "🚨" */
    0x1e, 0x17, 0xc2, 0xd1, 0xce, 0x61, 0x94, 0xa7,
    0xf9, 0xb6, 0xff, 0xe0, 0x17, 0xf8,

    /* U+1F6AC "🚬" */
    0x0, 0x18, 0x2, 0xfc, 0x43, 0x47, 0x98, 0x1e,
    0xc, 0x81, 0x60, 0x7f, 0xfc, 0xd, 0xff, 0x80,

    /* U+1F6B6 "🚶" */
    0x18, 0xe3, 0x86, 0x3d, 0xf5, 0xce, 0x25, 0x10,

    /* U+1F6CF "🛏" */
    0xe0, 0xd, 0x0, 0xd8, 0xe, 0x7e, 0xf4, 0x1b,
    0xff, 0x80, 0x1f, 0xff, 0xc0, 0x30,

    /* U+1F6F0 "🛰" */
    0xf7, 0x15, 0x1, 0x9e, 0x13, 0x31, 0x66, 0x33,
    0xc0, 0x8,

    /* U+1F6F8 "🛸" */
    0xe, 0x5, 0x4e, 0xf3, 0x82, 0x7c, 0x8c, 0xd0,
    0xf8,

    /* U+1F916 "🤖" */
    0xe, 0x1, 0x40, 0x38, 0x3f, 0xed, 0x17, 0xd6,
    0xfe, 0xde, 0x3, 0xdf, 0x69, 0xc9, 0xff, 0x0,

    /* U+1F917 "🤗" */
    0xf, 0x80, 0x82, 0x8, 0x8, 0xb6, 0x25, 0x5,
    0x29, 0xc9, 0xf3, 0xd2, 0x25, 0x89, 0x3e, 0x48,
    0x5d, 0xbc,

    /* U+1F923 "🤣" */
    0xe, 0x6, 0x31, 0x3, 0xa3, 0x98, 0x1f, 0x27,
    0x61, 0x6c, 0xd9, 0x6e, 0x45, 0x18, 0x7c, 0x0,

    /* U+1F939 "🤹" */
    0x2, 0x1, 0x0, 0x1f, 0xc2, 0x28, 0xf3, 0x79,
    0xb9, 0x7e, 0x8f, 0xc7, 0x80,

    /* U+1F950 "🥐" */
    0x1f, 0x4, 0xb0, 0x8b, 0x39, 0x68, 0x8b, 0x3,
    0x7f, 0x9c, 0x20, 0x54, 0x4, 0x40, 0x70, 0x0,

    /* U+1F955 "🥕" */
    0x3, 0xc0, 0x48, 0x9, 0x83, 0x21, 0x9c, 0x6c,
    0x11, 0x4, 0xc0, 0xe0, 0x0,

    /* U+1F971 "🥱" */
    0x1f, 0x6, 0x11, 0x1, 0x69, 0x9a, 0xb, 0x3c,
    0x6a, 0xce, 0x2a, 0x47, 0x48, 0x70, 0xf0, 0x0,

    /* U+1F973 "🥳" */
    0x0, 0x60, 0xf8, 0xef, 0x20, 0x45, 0xa6, 0x81,
    0x90, 0x6, 0x8e, 0x30, 0xc3, 0xe0,

    /* U+1F989 "🦉" */
    0x0, 0x7f, 0x7d, 0x5f, 0x77, 0x73, 0xcd, 0x41,
    0x5e, 0x34, 0x3e,

    /* U+1F98A "🦊" */
    0x31, 0x87, 0x51, 0x5e, 0x10, 0x44, 0x4, 0x94,
    0x2d, 0x7a, 0x26, 0x31, 0x81, 0xc0,

    /* U+1F9BA "🦺" */
    0x1c, 0x3f, 0x9f, 0x4d, 0xaa, 0xf5, 0x76, 0xb3,
    0xff, 0x8c, 0xff, 0xdd, 0xc0,

    /* U+1F9CA "🧊" */
    0xf, 0x6, 0x39, 0x1, 0xdc, 0xd8, 0x6a, 0xaa,
    0x59, 0x2b, 0xa1, 0xa4, 0x4f, 0xf0, 0x80, 0x0,

    /* U+1F9D1 "🧑" */
    0x3c, 0x3f, 0xbc, 0xfc, 0x3d, 0x5e, 0xd, 0x24,
    0x82, 0x61, 0x1f, 0x0,

    /* U+1F9F3 "🧳" */
    0x3, 0x7, 0x1d, 0x1a, 0x65, 0x43, 0x85, 0x86,
    0x6c, 0x14, 0x8,

    /* U+1FAE1 "🫡" */
    0x3e, 0xd, 0x62, 0x72, 0x5c, 0x27, 0x13, 0x0,
    0x60, 0xa, 0xf9, 0x40, 0x46, 0x18, 0x3c, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 203, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 42, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 60, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 4, .adv_w = 133, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 107, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 32, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 19, .adv_w = 62, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 21, .adv_w = 92, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 24, .adv_w = 34, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 25, .adv_w = 61, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 26, .adv_w = 34, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 34, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 28, .adv_w = 92, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 31, .adv_w = 92, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 34, .adv_w = 165, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 46, .adv_w = 42, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 42, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 48, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 53, .adv_w = 102, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 112, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 111, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 47, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 72, .adv_w = 78, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 76, .adv_w = 96, .box_w = 2, .box_h = 1, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 77, .adv_w = 129, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 64, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 86, .adv_w = 76, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 88, .adv_w = 92, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 90, .adv_w = 129, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 96, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 98, .adv_w = 67, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 100, .adv_w = 92, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 69, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 106, .adv_w = 69, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 109, .adv_w = 96, .box_w = 3, .box_h = 1, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 110, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 115, .adv_w = 101, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 120, .adv_w = 40, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 121, .adv_w = 96, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 122, .adv_w = 69, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 124, .adv_w = 66, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 126, .adv_w = 76, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 128, .adv_w = 165, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 165, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 165, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 91, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 158, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 165, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 221, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 107, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 48, .box_w = 2, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 48, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 48, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 48, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 133, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 130, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 92, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 312, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 320, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 127, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 102, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 107, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 158, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 407, .adv_w = 97, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 97, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 97, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 97, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 427, .adv_w = 43, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 429, .adv_w = 43, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 43, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 43, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 441, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 92, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 479, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 485, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 87, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 511, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 517, .adv_w = 87, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 523, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 127, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 556, .adv_w = 105, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 102, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 139, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 259, .box_w = 15, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 589, .adv_w = 187, .box_w = 11, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 108, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 605, .adv_w = 127, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 133, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 630, .adv_w = 124, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 637, .adv_w = 132, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 652, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 657, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 111, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 147, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 131, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 691, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 705, .adv_w = 203, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 719, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 733, .adv_w = 203, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 746, .adv_w = 203, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 760, .adv_w = 203, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 773, .adv_w = 203, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 788, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 789, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 803, .adv_w = 203, .box_w = 5, .box_h = 7, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 808, .adv_w = 203, .box_w = 6, .box_h = 7, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 203, .box_w = 4, .box_h = 7, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 818, .adv_w = 203, .box_w = 5, .box_h = 7, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 823, .adv_w = 203, .box_w = 6, .box_h = 7, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 829, .adv_w = 203, .box_w = 5, .box_h = 7, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 834, .adv_w = 203, .box_w = 6, .box_h = 7, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 203, .box_w = 5, .box_h = 7, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 845, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 861, .adv_w = 203, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 874, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 890, .adv_w = 203, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 904, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 918, .adv_w = 203, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 931, .adv_w = 203, .box_w = 5, .box_h = 11, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 938, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 954, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 968, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 982, .adv_w = 203, .box_w = 8, .box_h = 11, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 993, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1007, .adv_w = 203, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1024, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1038, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1054, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1070, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1086, .adv_w = 203, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1104, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1120, .adv_w = 203, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1134, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1148, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1162, .adv_w = 203, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1179, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1193, .adv_w = 203, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1207, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1221, .adv_w = 203, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1232, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1246, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1260, .adv_w = 203, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1270, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1284, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1300, .adv_w = 203, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1310, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1324, .adv_w = 203, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1334, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1348, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1362, .adv_w = 203, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1380, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1394, .adv_w = 203, .box_w = 6, .box_h = 11, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 1403, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1419, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1435, .adv_w = 203, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1449, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1463, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1477, .adv_w = 203, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1487, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1503, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1519, .adv_w = 203, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1537, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1553, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1569, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1585, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1601, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1617, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1633, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1647, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1661, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1677, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1693, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1709, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1725, .adv_w = 203, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1736, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1750, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1766, .adv_w = 203, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1780, .adv_w = 203, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1797, .adv_w = 203, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1814, .adv_w = 203, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1828, .adv_w = 203, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1842, .adv_w = 203, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1859, .adv_w = 203, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1874, .adv_w = 203, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1892, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1908, .adv_w = 203, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1922, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1938, .adv_w = 203, .box_w = 6, .box_h = 10, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 1946, .adv_w = 203, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1960, .adv_w = 203, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1970, .adv_w = 203, .box_w = 10, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1979, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1995, .adv_w = 203, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2013, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2029, .adv_w = 203, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 2042, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2058, .adv_w = 203, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2071, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2087, .adv_w = 203, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2101, .adv_w = 203, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 2112, .adv_w = 203, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2126, .adv_w = 203, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 2139, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2155, .adv_w = 203, .box_w = 9, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 2167, .adv_w = 203, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 2178, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x1, 0x2, 0x5, 0x6, 0x7, 0xa, 0xb,
    0xc, 0xd, 0xe, 0x1b, 0x1c, 0x1e, 0x20
};

static const uint16_t unicode_list_3[] = {
    0x0, 0x1, 0x20, 0x21, 0x1ebd, 0x1f51, 0x1f53, 0x1f54,
    0x1f56, 0x1f57, 0x1f59, 0x1f5b, 0x1f5c, 0x1f5d, 0x1f5e, 0x1f61,
    0x1f62, 0x1f64, 0x1f65, 0x1f68, 0x1f69, 0x1f6a, 0x1f6c, 0x1f6d,
    0x1f6f, 0x22a0, 0x24b1, 0x24c5, 0x24f2, 0x25a0, 0x25f4, 0x2614
};

static const uint16_t unicode_list_4[] = {
    0x0, 0xf38a, 0xf3d9, 0xf3de, 0xf3e2, 0xf3e6, 0xf3e8, 0xf3e9,
    0xf3eb, 0xf3f0, 0xf4f6, 0xf4fc, 0xf4fd, 0xf501, 0xf50c, 0xf50f,
    0xf512, 0xf51c, 0xf523, 0xf575, 0xf58a, 0xf598, 0xf5a0, 0xf5c4,
    0xf5cc, 0xf5d1, 0xf5d2, 0xf5d3, 0xf5dc, 0xf5e1, 0xf604, 0xf606,
    0xf609, 0xf62b, 0xf631, 0xf63c, 0xf63d, 0xf63e, 0xf66e, 0xf695,
    0xf6a1, 0xf6bb, 0xf6d0, 0xf6d2, 0xf6d9, 0xf6e3, 0xf6e7, 0xf6ec,
    0xf6f7, 0xf6fc, 0xf6fd, 0xf71e, 0xf722, 0xf781, 0xf787, 0xf7ed,
    0xf7f1, 0xf7f2, 0xf7f3, 0xf7f4, 0xf7f5, 0xf7f6, 0xf7f7, 0xf7fa,
    0xf7fb, 0xf7fc, 0xf7ff, 0xf80d, 0xf81d, 0xf827, 0xf833, 0xf83c,
    0xf871, 0xf873, 0xf881, 0xf882, 0xf883, 0xf884, 0xf886, 0xf889,
    0xf88a, 0xf88b, 0xf898, 0xf899, 0xf89d, 0xf8a7, 0xf8c0, 0xf8e1,
    0xf8e9, 0xfb07, 0xfb08, 0xfb14, 0xfb2a, 0xfb41, 0xfb46, 0xfb62,
    0xfb64, 0xfb7a, 0xfb7b, 0xfbab, 0xfbbb, 0xfbc2, 0xfbe4, 0xfcd2
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 33, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 15, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 160, .range_length = 13, .glyph_id_start = 16,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 174, .range_length = 82, .glyph_id_start = 29,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 336, .range_length = 9749, .glyph_id_start = 111,
        .unicode_list = unicode_list_3, .glyph_id_ofs_list = NULL, .list_length = 32, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 65039, .range_length = 64723, .glyph_id_start = 143,
        .unicode_list = unicode_list_4, .glyph_id_ofs_list = NULL, .list_length = 104, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
    .cmap_num = 5,
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
