void func_800942D8(int value) {
    register int argument asm("$5") = value;

    asm("break 260" : : "r"(argument));
}
