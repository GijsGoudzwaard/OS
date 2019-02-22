#include "headers/vga.h"
#include "headers/idt.h"
#include "headers/colors.h"

/**
 * The main method that is called from assembly.
 *
 * @return void
 */
extern "C"
void kernel_start(void)
{
    vga::setup();

    idt_init();
    kb_init();

    // Keep the program alive.
    while (1);
}