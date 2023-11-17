#include <string.h>

#include "vga.h"

uint16_t *vgaBuff;
uint8_t vgaBackgroundColor;

void vgaInit(VGAColor color)
{
    vgaBuff = (uint16_t *)VGA_TXT_MODE;
    vgaBackgroundColor = color.background;
    
    for (size_t y = 0; y < 25; y++)
    {
        for (size_t x = 0; x < 80; x++)
        {
            const size_t index = y * 80 + x;
            vgaSetColor(index, color);
        }
    }
}

void vgaSetColor(int pos, VGAColor color)
{
    vgaBuff[pos] = ' ' | (color.foreground | color.background << 4) << 8;
}

void vgaPutC(uint8_t c, int pos, uint8_t textColor)
{
    vgaBuff[pos] = c | (textColor | vgaBackgroundColor << 4) << 8;
}


void vgaPrint(const char* buffer) {
    size_t size = strlen(buffer);
    size_t i = 0;
    while(i < size) {
        vgaPutC(buffer[i], i, 0xF);
        i++;
    }
}