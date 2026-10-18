void func_800A30B4(int first_value, int second_value, int third_value) {
    register int *destination asm("$1") = (int *)0x800F0000;

    asm("" : "+r"(destination));
    destination[-0xDE4 / 4] = first_value;
    asm("" : : : "memory");
    {
        register int *next asm("$1") = (int *)0x800F0000;
        asm("" : "+r"(next));
        next[-0xDBC / 4] = second_value;
    }
    asm("" : : : "memory");
    {
        register int *last asm("$1") = (int *)0x800F0000;
        asm("" : "+r"(last));
        last[-0xDE8 / 4] = third_value;
    }
}
