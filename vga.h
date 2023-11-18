#pragma once

#include "nice.h"

// Location of the VGA Text Mode buffer.
// https://littleosbook.github.io/#the-framebuffer
#define VGA_TXT_MODE 0xB8000
#define VGA_COLS 80
#define VGA_ROWS 25

// http://www.osdever.net/FreeVGA/vga/crtcreg.htm
#define VGA_CRT 0x3D4
#define VGA_CRT_DATA 0x3D5
// Cursor Location Registers
// http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0E
#define VGA_CURSOR_HIGH 0x0E
// http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0F
#define VGA_CURSOR_LOW 0x0F

typedef struct
{
    u8 background;
    u8 foreground;
} VGAColor;


#define BLACK \
    (VGAColor) { 0x0, 0xF }
#define WHITE \
    (VGAColor) { 0xF, 0xF }
#define RED \
    (VGAColor) { 0x4, 0x4 }

void vgaInit(VGAColor);
void vgaPrint(const char*);
void vgaClearScreen(VGAColor);