#include "../headers/idt.h"
#include "../headers/common.h"

#define IDT_SIZE 256

#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08


struct IDT_entry
{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

extern "C" void idt_init(void)
{
    unsigned long keyboard_address;
    unsigned long idt_address;
    unsigned long idt_ptr[2];

    /* populate IDT entry of keyboard's interrupt */
    keyboard_address = (unsigned long) keyboard_handler;
    IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
    IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = INTERRUPT_GATE;
    IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

    /*     Ports
    *	 PIC1	PIC2
    *Command 0x20	0xA0
    *Data	 0x21	0xA1
    */

    /* ICW1 - begin initialization */
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    /* ICW2 - remap offset address of IDT */
    /*
    * In x86 protected mode, we have to remap the PICs beyond 0x20 because
    * Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
    */
    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    /* ICW3 - setup cascading */
    outb(0x21, 0x00);
    outb(0xA1, 0x00);

    /* ICW4 - environment info */
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    /* Initialization finished */

    /* mask interrupts */
    outb(0x21, 0xff);
    outb(0xA1, 0xff);

    /* fill the IDT descriptor */
    idt_address = (unsigned long) IDT;
    idt_ptr[0] = (sizeof(struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
}

extern "C" void kb_init(void)
{
    /* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
    outb(0x21, 0xFD);
}