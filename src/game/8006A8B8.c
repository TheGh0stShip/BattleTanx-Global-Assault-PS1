extern unsigned char *D_800E3E74;
extern int D_800E53FC[];

void func_8006A8B8(void) {
    int value;

    D_800E53FC[1] = *(int *)(D_800E3E74 + 0x10);
    value = *(int *)(D_800E3E74 + 0x1C);
    D_800E53FC[3] = value;
    D_800E53FC[2] = value;
}
