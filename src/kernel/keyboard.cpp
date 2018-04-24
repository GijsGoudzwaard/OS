#include "../headers/keyboard.h"
#include "../headers/vga.h"
#include "../headers/string.h"
#include "../headers/common.h"
#include "../headers/colors.h"

char *row_buffer = nullptr;
bool caps_lock = false;
bool shift = false;

/**
 * Handles the keyboard interrupts.
 *
 * @param  void
 * @return void
 */
extern "C"
void keyboard_handler_main(void)
{
  unsigned char keycode;

  /* write EOI */
  outb(0x20, 0x20);

  keycode = inb(KEYBOARD_DATA_PORT);

  if (keycode == SHIFT_PRESSED_KEY_CODE || keycode == SHIFT_RELEASED_KEY_CODE) {
    shift = !shift;
  }

  if (keycode == CAPS_LOCK_KEY_CODE) {
    caps_lock = !caps_lock;
  }

  // If keypress up, don't do anything.
  if (keycode & KEY_UP)
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

  if ((shift || caps_lock) && ! (shift && caps_lock)) {
    key[0] = keyboard_map[keycode + 90];
  }

  string::append(row_buffer, keyboard_map[keycode]);

  vga::print(key);
}
