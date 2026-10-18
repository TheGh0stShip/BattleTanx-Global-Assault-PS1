void func_80094198(void) {
    register int service asm("$4") = 1;

    asm("syscall" : : "r"(service));
}
