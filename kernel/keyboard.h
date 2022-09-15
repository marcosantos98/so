#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

extern void keyboard_handler(void);

void keyboard_enable(void);
void keyboard_main(void);

#endif