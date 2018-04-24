#ifndef IDT_H
#define IDT_H

extern "C" void load_idt(unsigned long *idt_ptr);

extern "C" void keyboard_handler(void);

extern "C" void idt_init();
extern "C" void kb_init();

#endif
