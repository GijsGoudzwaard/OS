#include "../headers/keyboard.h"
#include "../headers/vga.h"
#include "../headers/string.h"
#include "../headers/common.h"
#include "../headers/colors.h"

// TODO: Change to char pointer once memory works
char row_buffer[80];
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

    if (keycode == ENTER_KEY_CODE) {
        if (string::compare(row_buffer, "help") == string::STATUS_EQUAL) {
            vga::printf("\nAvailable commands: \n");
            vga::printf("\thelp  - Shows the available commands\n");
            vga::printf("\tclear - Clears the screen\n");
        } else if (string::compare(row_buffer, "clear") == string::STATUS_EQUAL) {
            vga::clear_screen(WHITE);
        } else {
            vga::printf("\nCommand '%s' not found\n", row_buffer);
        }

        // Reset the row buffer.
        *row_buffer = 0;

        return;
    }

    char key[2] = "";
    string::append(key, keyboard_map[keycode]);

    // Check if shift or caps lock is pressed and if not both are pressed.
    if ((shift || caps_lock) && !(shift && caps_lock)) {
        key[0] = keyboard_map[keycode + 90];
    }

    string::append(row_buffer, keyboard_map[keycode]);

    vga::printf(key);
}
