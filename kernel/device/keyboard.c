#include "keyboard.h"

#include "../io.h"
#include "video.h"
#include "keyboard_map.h"

void keyboard_enable(void)
{
	io_write(0x21, 0xFD);
}

void keyboard_handler_main(void)
{
	io_write(0x20, 0x20);

	uint8_t status = io_read(KEYBOARD_STATUS_PORT);
	if (status & 0x01)
	{
		char keycode = io_read(KEYBOARD_DATA_PORT);

		if (keycode == 0x1C)
		{
			video_move_row(1, false);
			video_move_col(-video_get_col(), false);
			video_scroll();
			return;
		}
		else if (keycode == 0x0E)
		{
			video_move_col(-1, true);
			return;
		}

		if (keycode < 0)
		{
			return;
		}

		const char c[1] = {keyboard_map[(unsigned char)keycode]};
		video_write(c, 1);
	}
}
