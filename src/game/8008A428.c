int func_8008A428(int value) {
    register volatile int *global_pointer asm("$28");
    int previous = global_pointer[0x44 / 4];

    global_pointer[0x44 / 4] = value;
    return previous;
}
