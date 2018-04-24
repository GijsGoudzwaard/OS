#include "headers/vga.h"

//extern "C" {
  #include "headers/idt.h"
  #include "headers/colors.h"
//}

/**
 * Set the welcome screen.
 *
 * @return void
 */
void welcome_screen()
{
  vga::println(" ____________________________________");
  vga::println("< Welcome to Aperture Science, GLaDOS >");
  vga::println(" ------------------------------------");
  vga::println("        \\   ^__^");
  vga::println("         \\  (oo)\\_______");
  vga::println("            (__)\\       )\\/\\");
  vga::println("                ||----w |");
  vga::println("                ||     ||");
}

/**
 * The main method that is called from assembly.
 *
 * @return void
 */
extern "C" void kernel_start(void)
{
  // Clear the default text that is set in qemu.
  // TODO: Set the color parameter to the default background color.
  vga::clear_screen(WHITE);

  welcome_screen();

  // set_default_cursor_location();

  idt_init();
  kb_init();

  while (1);
}