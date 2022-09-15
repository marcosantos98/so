#ifndef VIDEO_H
#define VIDEO_H

#include <stddef.h>
#include <stdint.h>

#define VIDEO_MEM_BEGIN 0xB8000
#define VIDEO_WIDTH 80
#define VIDEO_HEIGHT 25

typedef enum
{
  VC_BLACK = 0,
  VC_BLUE = 1,
  VC_GREEN = 2,
  VC_CYAN = 3,
  VC_RED = 4,
  VC_MAGENTA = 5,
  VC_BROWN = 6,
  VC_LIGHT_GREY = 7,
  VC_DARK_GREY = 8,
  VC_LIGHT_BLUE = 9,
  VC_LIGHT_GREEN = 10,
  VC_LIGHT_CYAN = 11,
  VC_LIGHT_RED = 12,
  VC_LIGHT_MAGENTA = 13,
  VC_LIGHT_BROWN = 14,
  VC_WHITE = 15,
} VideoColor;

void video_main();
void video_clear_mem();
void video_set_color(uint8_t);
void video_set_entry_at(char, uint8_t, size_t, size_t);
void video_put_char(char);
void video_write(const char *, size_t);
void video_write_cstr(const char *);
void video_cursor_move(size_t, size_t);

static inline uint8_t video_entry_color(VideoColor fg, VideoColor bg)
{
  return fg | bg << 4;
}

static inline uint16_t video_entry(unsigned char uc, uint8_t color)
{
  return (uint16_t)uc | (uint16_t)color << 8;
}

#endif