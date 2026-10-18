void func_80086C74(int value) {
    register volatile int *global_pointer asm("$28");

    global_pointer[0x38 / 4] = value;
    global_pointer[0x3C / 4] = value;
}
