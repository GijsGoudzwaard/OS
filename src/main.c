#include "headers/vga.h"
#include "headers/colors.h"
#include "headers/idt.h"

/**
 * Set the welcome screen.
 *
 * @return void
 */
void welcome_screen()
{
  println(" __________________________________________");
  println("< Hi there, welcome to my operating system >");
  println(" ------------------------------------------");
  println("        \\   ^__^");
  println("         \\  (oo)\\_______");
  println("            (__)\\       )\\/\\");
  println("                ||----w |");
  println("                ||     ||");
}

/**
 * The main method that is called from assembly.
 *
 * @return void
 */
void main(void)
{
  // Clear the default text that is set in qemu.
  // TODO: Set the color parameter to the default background color.
  clear_screen(WHITE);

  welcome_screen();

  set_default_cursor_location();

  idt_init();
  kb_init();

  while(1);
}