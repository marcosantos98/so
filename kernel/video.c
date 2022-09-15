#include "video.h"
#include "io.h"
#include "../libc/string.h"

uint16_t *video_buffer;
uint8_t video_color;

size_t video_row = 0;
size_t video_col = 0;

void video_main()
{
	video_buffer = (uint16_t *)VIDEO_MEM_BEGIN;
	video_color = video_entry_color(VC_WHITE, VC_BLACK);
}

void video_set_color(uint8_t color)
{
	video_color = color;
}

void video_clear_mem()
{
	for (size_t y = 0; y < VIDEO_HEIGHT; y++)
	{
		for (size_t x = 0; x < VIDEO_WIDTH; x++)
		{
			const size_t index = y * VIDEO_WIDTH + x;
			video_buffer[index] = video_entry(' ', video_color);
		}
	}
}

void video_set_entry_at(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VIDEO_WIDTH + x;
	video_buffer[index] = video_entry(c, color);
}

void video_put_char(char c)
{
	if (c == '\n')
	{
		video_row++;
		video_col = 0;
		video_cursor_move(video_col, video_row);
		return;
	}
	video_set_entry_at(c, video_color, video_col, video_row);
	const size_t temp = video_col + 1;
	if (temp == VIDEO_WIDTH)
	{
		video_col = 0;
		if (++video_row == VIDEO_HEIGHT)
			video_row = 0;
	} else {
		video_col++;
	}

	video_cursor_move(video_col, video_row);
}

void video_write(const char *data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		video_put_char(data[i]);
}

void video_write_cstr(const char *data)
{
	video_write(data, strlen(data));
}

void video_cursor_move(size_t x, size_t y)
{
	io_write(0x3D4, 14);
	io_write(0x3D5, (y * VIDEO_WIDTH + x) >> 8);
	io_write(0x3D4, 15);
	io_write(0x3D5, (y * VIDEO_WIDTH + x));
}