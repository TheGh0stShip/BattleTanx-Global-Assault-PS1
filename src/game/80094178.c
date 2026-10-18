int func_80094178(void) {
    register int result asm("$2");

    asm("mfc0 $2,$13" : "=r"(result));
    return result;
}
