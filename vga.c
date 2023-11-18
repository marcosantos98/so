#include <string.h>

#include "io.h"
#include "vga.h"

uint16_t *vgaBuff;
uint8_t vgaBackgroundColor;

size_t cursorX = 0;
size_t cursorY = 0;

// Move the cursor to the specified position in the framebuffer.
// This uses the CRT Control IO Ports to move the cursor.
void __moveCursor(size_t x, size_t y)
{
    // Compute [x, y] to index in vgaBuff;
    size_t idx = y * VGA_COLS + x;

    ioWrite(VGA_CRT, VGA_CURSOR_HIGH);
    ioWrite(VGA_CRT_DATA, idx >> 8);
    ioWrite(VGA_CRT, VGA_CURSOR_LOW);
    ioWrite(VGA_CRT_DATA, idx);
}

void __setColor(int pos, VGAColor color)
{
    vgaBuff[pos] = ' ' | (color.foreground | color.background << 4) << 8;
}

void __putC(uint8_t c, int pos, uint8_t textColor)
{
    vgaBuff[pos] = c | (textColor | vgaBackgroundColor << 4) << 8;
}

void vgaClearScreen(VGAColor color)
{
    for (size_t y = 0; y < VGA_ROWS; y++)
    {
        for (size_t x = 0; x < VGA_COLS; x++)
        {
            const size_t index = y * VGA_COLS + x;
            __setColor(index, color);
        }
    }
    vgaBackgroundColor = color.background;
}

// Draws the given buffer and move the cursor at the end
void vgaPrint(const char *buffer)
{
    while (*buffer)
    {
        // \n will behave the same way as \r\n
        if (buffer[0] == '\n')
        {
            cursorX = 0;
            cursorY++;
        }
        else
        {
            size_t idx = cursorY * VGA_COLS + cursorX;
            __putC(buffer[0], idx, 0xF);
            cursorX++;
        }
        (void)*buffer++;
    }
    __moveCursor(cursorX, cursorY);
}

void vgaInit(VGAColor color)
{
    vgaBuff = (uint16_t *)VGA_TXT_MODE; // Point our buffer to the logical of VGA in pyshical memory
    vgaBackgroundColor = color.background; // Save the given color so we can draw text with the same background
                                            
    __moveCursor(0, 0); // Setup the cursor                    
    vgaClearScreen(color); // Clear the screen using the provided color
}