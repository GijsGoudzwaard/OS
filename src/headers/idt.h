#ifndef IDT_H
#define IDT_H

extern void load_idt(unsigned long *idt_ptr);
extern void keyboard_handler(void);

void idt_init();
void kb_init();

#endif
