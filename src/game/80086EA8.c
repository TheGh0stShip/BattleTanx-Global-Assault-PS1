extern unsigned char D_800EE588[];

int func_80086EA8(int value) {
    int previous = D_800EE588[8] == 1;
    D_800EE588[8] = value != 0;
    return previous;
}
