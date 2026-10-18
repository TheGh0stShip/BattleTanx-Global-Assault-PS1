void func_8008A40C(void) {
    register volatile unsigned int *global_pointer asm("$28");

    global_pointer[0x40 / 4] = 0x1F800000;
    global_pointer[0x44 / 4] = 0x1F800400;
}
