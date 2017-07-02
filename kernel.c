#include "colors.h"

char *terminal = (char*) 0xB8000;

void write_string(int colour, char *string)
{
    while(*string != 0) {
      *terminal++ = *string++;
      *terminal++ = colour;
    }
}

void print(char *string) {
	write_string(WHITE, string);
}

void println(char *string) {
	// string[] = "\n";
	// int color = color_presets::WHITE;
	write_string(WHITE, string);
}

/**
 * The main method that is called from assembly.
 *
 * @return void
 */
void kernel_main(void)
{
	print("Hai");
}