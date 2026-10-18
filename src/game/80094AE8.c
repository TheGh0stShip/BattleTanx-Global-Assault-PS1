int func_80094AE8(void) {
    register int global_pointer asm("$28");
    register int previous asm("$2") = global_pointer;

    asm("" : "+r"(previous));
    global_pointer = 0x800C0000;
    asm("" : "+r"(global_pointer));
    global_pointer += 0x6074;
    asm("" : : "r"(global_pointer));
    return previous;
}
