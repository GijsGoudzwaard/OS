#include "../headers/keyboard.h"
#include "../headers/vga.h"
#include "../headers/string.h"

//extern "C" {
  #include "../headers/common.h"
  #include "../headers/colors.h"
//}

char *row_buffer = 0;

/**
 * Handles the keyboard interrupts.
 *
 * @param  void
 * @return void
 */
extern "C"
void keyboard_handler_main(void)
{
  static uint8_t shift = 0;
  unsigned char keycode;

  /* write EOI */
  outb(0x20, 0x20);
  if (keycode == SHIFT_KEY_CODE) {
    shift = 1;
  }

  if ((keycode == SHIFT_KEY_CODE) & 0x80) {
    shift = 0;
  }

  keycode = inb(KEYBOARD_DATA_PORT);

  // If keypress up, don't do anything.
  if ((keycode & KEY_UP) == KEY_UP)
    return;

  if (keycode < 0)
    return;

  if (keycode == ENTER_KEY_CODE) {
    if (string::compare(row_buffer, "help") == 0) {
      vga::println("\nclear - Clears the screen");
    } else if (string::compare(row_buffer, "clear") == 0) {
      vga::clear_screen(WHITE);
    } else {
      vga::println("\nCommand not found");
    }

    // Reset the row buffer.
    *row_buffer = 0;

    return;
  }

  char key[2] = "";
  string::append(key, keyboard_map[keycode]);

  if (shift) {
    key[0] = keyboard_map[keycode + 90];
  }

  string::append(row_buffer, keyboard_map[keycode]);

  vga::print(key);
}
