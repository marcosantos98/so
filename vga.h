#pragma once

#include <stdint.h>

// Location of the VGA Text Mode buffer.
#define VGA_TXT_MODE 0xB8000

typedef struct
{
    uint8_t background;
    uint8_t foreground;
} VGAColor;


#define BLACK \
    (VGAColor) { 0x0, 0xF }
#define WHITE \
    (VGAColor) { 0xF, 0xF }
#define RED \
    (VGAColor) { 0x4, 0x4 }

void vgaInit(VGAColor);
void vgaSetColor(int, VGAColor);
void vgaPutC(uint8_t, int, uint8_t);
void vgaPrint(const char*);