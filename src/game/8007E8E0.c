void func_8007E8E0(void) {
    register int global_pointer asm("$28") = 0x80080000;

    asm("" : "+r"(global_pointer));
    global_pointer = *(int *)(global_pointer - 0x1724);
    asm("" : : "r"(global_pointer));
}
