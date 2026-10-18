void func_80015090(void *output) {
    asm("swc2 $25,0($4)\n\tswc2 $26,4($4)\n\tswc2 $27,8($4)" : : "r"(output) : "memory");
}
