void func_80094168(void) {
    register int service asm("$4") = 2;

    asm("syscall" : : "r"(service));
}
