extern unsigned char D_800EE588[];

void func_800877E4(int first, int unused, int third, int fourth) {
    unsigned char *state = D_800EE588;
    int count = *(int *)(state + 0x30);
    unsigned int flag = state[8];

    *(int *)(state + 0x2C) = first;
    *(int *)(state + 0xC0) = 0;
    *(int *)(state + 0xBC) = fourth;
    *(int *)(state + 0x2FC) = 0;
    *(int *)(state + 0x30) = count + 1;
    if (flag != 0) {
        *(int *)(state + 0xBC) = fourth - 4;
    }
    *(int *)(state + 0x34) = third;
    *(int *)(state + 0x38) = fourth;
    state[6] = 1;
    asm volatile("" : : : "memory");
}
