extern unsigned short D_800D3260[];
extern unsigned char *D_800D3258;

void *func_80023870(unsigned char *record, unsigned int index) {
    int slot;
    unsigned short raw_slot;
    void *result = 0;

    if (record == 0) {
        raw_slot = D_800D3260[index];
    } else {
        raw_slot = *(unsigned short *)(record + 2);
    }
    slot = (short)raw_slot;
    if (slot != -1) {
        result = D_800D3258 + slot * 64;
    }
    return result;
}
