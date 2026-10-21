typedef struct {
    unsigned int addr;
    unsigned int size;
} SpuMemEntry;

extern int D_800B7BD4;
extern SpuMemEntry *D_800B7BD8;

void func_8009ABD4(void) {
    int i;
    int j;
    unsigned int a;
    unsigned int s;
    unsigned int tag;
    unsigned int mask;
    unsigned int hi;

    for (i = 0; i <= D_800B7BD4;) {
        hi = 0x80000000;
        tag = 0x2FFFFFFF;
        mask = 0x0FFFFFFF;
        if (D_800B7BD8[i].addr & hi) {
            j = i + 1;
            for (;;) {
                unsigned int v = D_800B7BD8[j].addr;
                if (v != tag) break;
                j++;
            }
            if ((D_800B7BD8[j].addr & hi) &&
                (D_800B7BD8[j].addr & mask) ==
                    (D_800B7BD8[i].addr & mask) + D_800B7BD8[i].size) {
                D_800B7BD8[j].addr = tag;
                D_800B7BD8[i].size += D_800B7BD8[j].size;
                continue;
            }
        }
        i++;
    }
    for (i = 0; i <= D_800B7BD4; i++) {
        if (D_800B7BD8[i].size == 0) {
            D_800B7BD8[i].addr = 0x2FFFFFFF;
        }
    }
    for (i = 0; i <= D_800B7BD4; i++) {
        if (D_800B7BD8[i].addr & 0x40000000) {
            break;
        }
        for (j = i + 1; j <= D_800B7BD4; j++) {
            if (D_800B7BD8[j].addr & 0x40000000) {
                break;
            }
            if ((D_800B7BD8[j].addr & 0x0FFFFFFF) < (D_800B7BD8[i].addr & 0x0FFFFFFF)) {
                a = D_800B7BD8[i].addr;
                D_800B7BD8[i].addr = D_800B7BD8[j].addr;
                s = D_800B7BD8[i].size;
                D_800B7BD8[i].size = D_800B7BD8[j].size;
                D_800B7BD8[j].addr = a;
                D_800B7BD8[j].size = s;
            }
        }
    }
    for (i = 0; i <= D_800B7BD4; i++) {
        if (D_800B7BD8[i].addr & 0x40000000) {
            break;
        }
        if (D_800B7BD8[i].addr == 0x2FFFFFFF) {
            D_800B7BD8[i].addr = D_800B7BD8[D_800B7BD4].addr;
            D_800B7BD8[i].size = D_800B7BD8[D_800B7BD4].size;
            D_800B7BD4 = i;
            break;
        }
    }
    for (i = D_800B7BD4 - 1; i >= 0; i--) {
        if (!(D_800B7BD8[i].addr & 0x80000000)) {
            break;
        }
        D_800B7BD8[i].addr = (D_800B7BD8[i].addr & 0x0FFFFFFF) | 0x40000000;
        D_800B7BD8[i].size += D_800B7BD8[D_800B7BD4].size;
        D_800B7BD4 = i;
    }
}
