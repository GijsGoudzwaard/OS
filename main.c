#include "headers/vga.h"
#include "headers/colors.h"

/**
 * The main method that is called from assembly.
 *
 * @return void
 */
void kernel_main(void)
{
	// Clear the default text that is set in qemu.
	// TODO: Set the color parameter to the default background color.
	clear_screen(BLACK);

	println("This is\nA mulitline\nMessage");
	print("test");
}