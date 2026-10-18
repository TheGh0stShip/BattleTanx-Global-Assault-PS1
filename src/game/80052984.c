typedef unsigned short u16;

extern unsigned char D_800E3E68[];

void func_80052984(int index, int delta) {
    unsigned char *record;
    u16 *value;

    if (index == 0x7F) {
        record = 0;
    } else {
        record = D_800E3E68 + index * 276;
    }
    value = *(u16 **)(record + 0x0C);
    *value += delta;
    *(u16 *)(record + 0xD0) += delta;
}
