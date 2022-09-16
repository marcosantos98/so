#include "isr.h"

#include "device/video.h"

void isr_handler(registers_t registers)
{
    video_write_cstr("ISR not handled! ");
    video_put_dec(registers.int_no);
    video_put_char(' ');
    video_put_dec(registers.err_code);
    video_put_char('\n');
}
