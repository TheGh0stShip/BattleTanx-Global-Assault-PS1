typedef struct {
    int madr;
    int bcr;
    int chcr;
    int unk;
} DMA_CONTROL;

extern volatile unsigned char *D_800B8A0C;
extern volatile int *D_800B8A24;
extern volatile unsigned char *D_800B8A28;
extern char D_800C5A68[];
extern void func_800943B0(char *, ...);

void func_8009C350(int id, void *addr, unsigned int blocks, unsigned int size,
                   unsigned int control, unsigned char completion,
                   unsigned int unused)
{
    int i;
    int temp;
    int temp2;
    unsigned char v;
    volatile int ret;
    volatile int *ptr;

    for (i = 0; *(volatile unsigned int *)(0x1F801088 + (id << 4)) & 0x01000000; i++) {
        if (i == 0x10000) {
            func_800943B0(D_800C5A68, *(volatile unsigned int *)(0x1F801088 + (id << 4)));
            break;
        }
    }
    if (completion == 1) {
        unsigned char *q = (unsigned char *)D_800B8A28;
        v = q[2];
        v |= 1 << id;
        q[2] = v;
    } else {
        unsigned char *q = (unsigned char *)D_800B8A28;
        v = q[2];
        v &= ~(1 << id);
        q[2] = v;
    }
    do {
        ret = *(volatile int *)D_800B8A28;
    } while (0);
    temp2 = id << 2;
    temp2 = temp2 + 3;
    temp = 1;
    temp = temp << temp2;
    ptr = &((volatile DMA_CONTROL *)0x1F801080)[id].madr;
    temp2 = *D_800B8A24;
    temp2 |= temp;
    *D_800B8A24 = temp2;
    *ptr++ = (int)addr;
    *ptr++ = (blocks << 16) | size;
    while (!(*D_800B8A0C & 0x40)) {
    }
    *ptr = control;
    do {
        ret = *ptr;
    } while (0);
}
