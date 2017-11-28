#include "../headers/keyboard.h"
#include "../headers/common.h"
#include "../headers/vga.h"

/*  This is a scancode table
 *  used to layout a standard US keyboard. I have left some
 *  comments in to give you an idea of what key is what, even
 *  though I set it's ar ray index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
unsigned char keyboard_map[256] = {
  0, 27, '1', '2', '3', '4', '5', '6', '7', '8',  /* 9 */
  '9', '0', '-', '=', '\b',  /* Backspace */
  '\t',      /* Tab */
  'q', 'w', 'e', 'r',  /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',  /* Enter key */
  0,      /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',  /* 39 */
  '\'', '`', 0,    /* Left shift */
  '\\', 'z', 'x', 'c', 'v', 'b', 'n',      /* 49 */
  'm', ',', '.', '/', 0,        /* Right shift */
  '*',
  0,  /* Alt */
  ' ',  /* Space bar */
  0,  /* Caps lock */
  0,  /* 59 - F1 key ... > */
  0, 0, 0, 0, 0, 0, 0, 0,
  0,  /* < ... F10 */
  0,  /* 69 - Num lock*/
  0,  /* Scroll Lock */
  0,  /* Home key */
  0,  /* Up Arrow */
  0,  /* Page Up */
  '-',
  0,  /* Left Arrow */
  0,
  0,  /* Right Arrow */
  '+',
  0,  /* 79 - End key*/
  0,  /* Down Arrow */
  0,  /* Page Down */
  0,  /* Insert Key */
  0,  /* Delete Key */
  0, 0, 0,
  0,  /* F11 Key */
  0,  /* F12 Key */
  0,
  0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
  '\b', '\t',
  'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
  0,
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
  '\"', '~', 0, '|',
  'Z', 'X', 'C', 'V', 'B', 'N', 'M',
  '<', '>', '?', 0, '*',
  0,  /* Alt */
  ' ',  /* Space bar */
  0,  /* Caps lock */
  0,  /* 59 - F1 key ... > */
  0, 0, 0, 0, 0, 0, 0, 0,
  0,  /* < ... F10 */
  0,  /* 69 - Num lock*/
  0,  /* Scroll Lock */
  0,  /* Home key */
  0,  /* Up Arrow */
  0,  /* Page Up */
  '-',
  0,  /* Left Arrow */
  0,
  0,  /* Right Arrow */
  '+',
  0,  /* 79 - End key*/
  0,  /* Down Arrow */
  0,  /* Page Down */
  0,  /* Insert Key */
  0,  /* Delete Key */
  0, 0, 0,
  0,  /* F11 Key */
  0,  /* F12 Key */
  0

};

/**
 * Handles the keyboard interrupt
 *
 * @param  void
 * @return void
*/
void keyboard_handler_main(void)
{
  uint8_t static shift = 0;
  unsigned char status;
  unsigned char keycode;
  /* write EOI */
  outb(0x20, 0x20);

  status = inb(KEYBOARD_STATUS_PORT);

  /* If the top bit of the byte we read from the keyboard is
*  set, that means that a key has just been released */
  if (keycode == 42) {
    shift = 1;
  }

  if ((keycode == 42) & 0x80) {
    shift = 0;
  }

  // Lowest bit of status will be set if buffer is not empty
  if (status & 0x01) {
    keycode = inb(KEYBOARD_DATA_PORT);
    if (keycode < 0)
      return;

    if (keycode == ENTER_KEY_CODE) {
      println("");
      return;
    }

    // Convert the char to a string
    char key[2];
    if (shift) {
      key[0] = keyboard_map[keycode + 90];
    } else {
      key[0] = keyboard_map[keycode];
    }

    key[1] = '\0';

    print(key);
  }
}
