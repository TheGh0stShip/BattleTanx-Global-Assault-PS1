void func_800736EC(unsigned char *object, int unused, int type, int unused2,
                   int *result) {
    if (type == 7) {
        result[0] = *(int *)(object + 0x08);
        result[1] = *(int *)(object + 0x0C);
        result[2] = *(int *)(object + 0x10);
        result[3] = *(int *)(object + 0x14);
        result[4] = *(int *)(object + 0x18);
        result[5] = *(int *)(object + 0x1C);
    }
}
