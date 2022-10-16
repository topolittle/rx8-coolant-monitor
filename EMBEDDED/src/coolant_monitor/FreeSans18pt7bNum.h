/* 
 * This is the standard Adafruit FreeSans18pt7b font but without letters and symbols.
 * Only numbers, sing and ponctuation have been keept to save space.
 * The original source code is available here:
 * https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Fonts/FreeSans18pt7b.h
 * The code is distributed under the BSD licence. To comply with the license, a copy of
 * the original license file was retreived and put beside this file under the name
 * 'Copying-Adafruit-GFX-Library.txt'. The file was retreived from the above GitHub
 * repository on the 'master' branch, commit 91d916deeb75263582a2456cb211ebdaf06b840b.
*/

#include <gfxfont.h>

const uint8_t FreeSans18pt7bBitmapsNum[] PROGMEM = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE9, 0x20, 0x3F, 0xFC, 0xE3, 0xF1,
    0xF8, 0xFC, 0x7E, 0x3F, 0x1F, 0x8E, 0x82, 0x41, 0x00, 0x01, 0xC3, 0x80,
    0x38, 0x70, 0x06, 0x0E, 0x00, 0xC1, 0x80, 0x38, 0x70, 0x07, 0x0E, 0x0F,
    0xFF, 0xF9, 0xFF, 0xFF, 0x3F, 0xFF, 0xE0, 0xE1, 0xC0, 0x1C, 0x38, 0x03,
    0x87, 0x00, 0x70, 0xE0, 0x0C, 0x18, 0x3F, 0xFF, 0xF7, 0xFF, 0xFE, 0xFF,
    0xFF, 0xC1, 0xC3, 0x80, 0x30, 0x60, 0x06, 0x0C, 0x01, 0xC3, 0x80, 0x38,
    0x70, 0x07, 0x0E, 0x00, 0xC1, 0x80, 0x03, 0x00, 0x0F, 0xC0, 0x3F, 0xF0,
    0x3F, 0xF8, 0x7B, 0x3C, 0xF3, 0x1C, 0xE3, 0x0E, 0xE3, 0x0E, 0xE3, 0x0E,
    0xE3, 0x00, 0xE3, 0x00, 0xF3, 0x00, 0x7B, 0x00, 0x7F, 0x80, 0x1F, 0xF0,
    0x07, 0xFC, 0x03, 0x7E, 0x03, 0x0F, 0x03, 0x07, 0xE3, 0x07, 0xE3, 0x07,
    0xE3, 0x07, 0xE3, 0x0F, 0x73, 0x3E, 0x7F, 0xFC, 0x3F, 0xF8, 0x0F, 0xE0,
    0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x78, 0x00,
    0xE0, 0x0F, 0xF0, 0x06, 0x00, 0xFF, 0xC0, 0x70, 0x07, 0x0E, 0x07, 0x00,
    0x70, 0x38, 0x38, 0x03, 0x00, 0xC3, 0x80, 0x18, 0x06, 0x1C, 0x00, 0xE0,
    0x71, 0xC0, 0x03, 0x87, 0x8C, 0x00, 0x1F, 0xF8, 0xE0, 0x00, 0x7F, 0x86,
    0x00, 0x01, 0xF8, 0x70, 0x00, 0x00, 0x03, 0x03, 0xC0, 0x00, 0x38, 0x7F,
    0x80, 0x01, 0x87, 0xFE, 0x00, 0x1C, 0x38, 0x70, 0x00, 0xC3, 0x81, 0xC0,
    0x0E, 0x18, 0x06, 0x00, 0xE0, 0xC0, 0x30, 0x07, 0x07, 0x03, 0x80, 0x70,
    0x1C, 0x38, 0x03, 0x80, 0xFF, 0xC0, 0x38, 0x03, 0xFC, 0x01, 0x80, 0x07,
    0x80, 0x01, 0xF0, 0x00, 0x7F, 0x80, 0x0F, 0xFC, 0x01, 0xE1, 0xE0, 0x1C,
    0x0E, 0x01, 0xC0, 0xE0, 0x1C, 0x0E, 0x01, 0xE1, 0xE0, 0x0E, 0x3C, 0x00,
    0x77, 0x80, 0x07, 0xF0, 0x00, 0x7C, 0x00, 0x0F, 0xE0, 0x03, 0xCF, 0x1C,
    0x78, 0x79, 0xC7, 0x03, 0xDC, 0xE0, 0x1F, 0x8E, 0x00, 0xF8, 0xE0, 0x0F,
    0x0E, 0x00, 0x70, 0xF0, 0x0F, 0x87, 0xC3, 0xFC, 0x7F, 0xFD, 0xC3, 0xFF,
    0x0E, 0x0F, 0xC0, 0xF0, 0xFF, 0xFF, 0xFA, 0x40, 0x06, 0x06, 0x0C, 0x0C,
    0x18, 0x18, 0x38, 0x30, 0x70, 0x70, 0x70, 0x60, 0xE0, 0xE0, 0xE0, 0xE0,
    0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x60, 0x70, 0x70, 0x70, 0x30, 0x38, 0x18,
    0x18, 0x0C, 0x0C, 0x06, 0x03, 0xC0, 0x60, 0x30, 0x30, 0x38, 0x18, 0x1C,
    0x0C, 0x0E, 0x0E, 0x0E, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x06, 0x0E, 0x0E, 0x0E, 0x0C, 0x1C, 0x18, 0x38, 0x30, 0x30,
    0x60, 0xC0, 0x0C, 0x03, 0x00, 0xC3, 0xB7, 0xFF, 0xC7, 0x81, 0xE0, 0xEC,
    0x73, 0x88, 0x40, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
    0x80, 0x01, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x80, 0x01,
    0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0xFF,
    0xF6, 0xDA, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0xC0, 0x30, 0x18,
    0x06, 0x01, 0x80, 0xC0, 0x30, 0x0C, 0x06, 0x01, 0x80, 0x60, 0x30, 0x0C,
    0x03, 0x00, 0xC0, 0x60, 0x18, 0x06, 0x03, 0x00, 0xC0, 0x30, 0x18, 0x06,
    0x01, 0x80, 0xC0, 0x30, 0x00, 0x07, 0xE0, 0x0F, 0xF8, 0x1F, 0xFC, 0x3C,
    0x3C, 0x78, 0x1E, 0x70, 0x0E, 0x70, 0x0E, 0xE0, 0x07, 0xE0, 0x07, 0xE0,
    0x07, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x07, 0xE0,
    0x07, 0xE0, 0x07, 0xE0, 0x0F, 0x70, 0x0E, 0x70, 0x0E, 0x78, 0x1E, 0x3C,
    0x3C, 0x1F, 0xF8, 0x1F, 0xF0, 0x07, 0xE0, 0x03, 0x03, 0x07, 0x0F, 0x3F,
    0xFF, 0xFF, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xE0, 0x1F, 0xF8,
    0x3F, 0xFC, 0x7C, 0x3E, 0x70, 0x0F, 0xF0, 0x0F, 0xE0, 0x07, 0xE0, 0x07,
    0x00, 0x07, 0x00, 0x07, 0x00, 0x0F, 0x00, 0x1E, 0x00, 0x3C, 0x00, 0xF8,
    0x03, 0xF0, 0x07, 0xC0, 0x1F, 0x00, 0x3C, 0x00, 0x38, 0x00, 0x70, 0x00,
    0x60, 0x00, 0xE0, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xF0,
    0x07, 0xFE, 0x07, 0xFF, 0x87, 0x83, 0xC3, 0x80, 0xF3, 0x80, 0x39, 0xC0,
    0x1C, 0xE0, 0x0E, 0x00, 0x07, 0x00, 0x0F, 0x00, 0x7F, 0x00, 0x3F, 0x00,
    0x1F, 0xE0, 0x00, 0x78, 0x00, 0x1E, 0x00, 0x07, 0x00, 0x03, 0xF0, 0x01,
    0xF8, 0x00, 0xFE, 0x00, 0x77, 0x00, 0x73, 0xE0, 0xF8, 0xFF, 0xF8, 0x3F,
    0xF8, 0x07, 0xF0, 0x00, 0x00, 0x38, 0x00, 0x38, 0x00, 0x78, 0x00, 0xF8,
    0x00, 0xF8, 0x01, 0xF8, 0x03, 0xB8, 0x03, 0x38, 0x07, 0x38, 0x0E, 0x38,
    0x1C, 0x38, 0x18, 0x38, 0x38, 0x38, 0x70, 0x38, 0x60, 0x38, 0xE0, 0x38,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38,
    0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x1F, 0xFF, 0x0F, 0xFF, 0x8F, 0xFF,
    0xC7, 0x00, 0x03, 0x80, 0x01, 0xC0, 0x00, 0xE0, 0x00, 0x70, 0x00, 0x39,
    0xF0, 0x3F, 0xFE, 0x1F, 0xFF, 0x8F, 0x83, 0xE7, 0x00, 0xF0, 0x00, 0x3C,
    0x00, 0x0E, 0x00, 0x07, 0x00, 0x03, 0x80, 0x01, 0xC0, 0x00, 0xFC, 0x00,
    0xEF, 0x00, 0x73, 0xC0, 0xF0, 0xFF, 0xF8, 0x3F, 0xF8, 0x07, 0xE0, 0x00,
    0x03, 0xE0, 0x0F, 0xF8, 0x1F, 0xFC, 0x3C, 0x1E, 0x38, 0x0E, 0x70, 0x0E,
    0x70, 0x00, 0x60, 0x00, 0xE0, 0x00, 0xE3, 0xE0, 0xEF, 0xF8, 0xFF, 0xFC,
    0xFC, 0x3E, 0xF0, 0x0E, 0xF0, 0x0F, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x07,
    0x60, 0x07, 0x70, 0x0F, 0x70, 0x0E, 0x3C, 0x3E, 0x3F, 0xFC, 0x1F, 0xF8,
    0x07, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x06, 0x00, 0x0E,
    0x00, 0x1C, 0x00, 0x18, 0x00, 0x38, 0x00, 0x70, 0x00, 0x60, 0x00, 0xE0,
    0x00, 0xC0, 0x01, 0xC0, 0x01, 0x80, 0x03, 0x80, 0x03, 0x80, 0x07, 0x00,
    0x07, 0x00, 0x07, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0C, 0x00,
    0x1C, 0x00, 0x1C, 0x00, 0x07, 0xF0, 0x0F, 0xFE, 0x0F, 0xFF, 0x87, 0x83,
    0xC7, 0x80, 0xF3, 0x80, 0x39, 0xC0, 0x1C, 0xE0, 0x0E, 0x78, 0x0F, 0x1E,
    0x0F, 0x07, 0xFF, 0x01, 0xFF, 0x03, 0xFF, 0xE3, 0xE0, 0xF9, 0xC0, 0x1D,
    0xC0, 0x0F, 0xE0, 0x03, 0xF0, 0x01, 0xF8, 0x00, 0xFC, 0x00, 0xF7, 0x00,
    0x73, 0xE0, 0xF8, 0xFF, 0xF8, 0x3F, 0xF8, 0x07, 0xF0, 0x00, 0x07, 0xE0,
    0x1F, 0xF8, 0x3F, 0xFC, 0x7C, 0x3C, 0x70, 0x0E, 0xF0, 0x0E, 0xE0, 0x06,
    0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x0F, 0x70, 0x0F, 0x78, 0x3F,
    0x3F, 0xFF, 0x1F, 0xF7, 0x07, 0xC7, 0x00, 0x07, 0x00, 0x06, 0x00, 0x0E,
    0x70, 0x0E, 0x70, 0x1C, 0x78, 0x3C, 0x3F, 0xF8, 0x1F, 0xF0, 0x07, 0xC0,
};

const GFXglyph FreeSans18pt7bGlyphsNum[] PROGMEM = {
    {0, 0, 0, 9, 0, 1},         // 0x20 ' '
    {0, 3, 26, 12, 4, -25},     // 0x21 '!'
    {10, 9, 9, 12, 1, -24},     // 0x22 '"'
    {21, 19, 24, 19, 0, -23},   // 0x23 '#'
    {78, 16, 30, 19, 2, -26},   // 0x24 '$'
    {138, 29, 25, 31, 1, -24},  // 0x25 '%'
    {229, 20, 25, 23, 2, -24},  // 0x26 '&'
    {292, 3, 9, 7, 2, -24},     // 0x27 '''
    {296, 8, 33, 12, 3, -25},   // 0x28 '('
    {329, 8, 33, 12, 1, -25},   // 0x29 ')'
    {362, 10, 10, 14, 2, -25},  // 0x2A '*'
    {375, 16, 16, 20, 2, -15},  // 0x2B '+'
    {407, 3, 9, 10, 3, -3},     // 0x2C ','
    {411, 8, 3, 12, 2, -10},    // 0x2D '-'
    {414, 3, 4, 9, 3, -3},      // 0x2E '.'
    {416, 10, 26, 10, 0, -25},  // 0x2F '/'
    {449, 16, 25, 19, 2, -24},  // 0x30 '0'
    {499, 8, 25, 19, 4, -24},   // 0x31 '1'
    {524, 16, 25, 19, 2, -24},  // 0x32 '2'
    {574, 17, 25, 19, 1, -24},  // 0x33 '3'
    {628, 16, 25, 19, 1, -24},  // 0x34 '4'
    {678, 17, 25, 19, 1, -24},  // 0x35 '5'
    {732, 16, 25, 19, 2, -24},  // 0x36 '6'
    {782, 16, 25, 19, 2, -24},  // 0x37 '7'
    {832, 17, 25, 19, 1, -24},  // 0x38 '8'
    {886, 16, 25, 19, 1, -24},  // 0x39 '9'
};

const GFXfont FreeSans18pt7bNum PROGMEM = {(uint8_t *)FreeSans18pt7bBitmapsNum,
                                        (GFXglyph *)FreeSans18pt7bGlyphsNum, 0x20,
                                        0x7E, 42};
