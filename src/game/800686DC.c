extern unsigned int D_800AD9EC[];

unsigned int func_800686DC(unsigned int first, unsigned int second) {
    unsigned int previous = D_800AD9EC[0];
    D_800AD9EC[1] = first;
    D_800AD9EC[0] = first;
    D_800AD9EC[4] = second;
    D_800AD9EC[3] = second;
    D_800AD9EC[5] = 0;
    return previous;
}
