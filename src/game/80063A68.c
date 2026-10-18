typedef struct Status {
    short value;
    char pad[0x12];
    unsigned char flag;
    char pad2[0x83];
} Status;

extern Status D_800E4ACC[];
extern short D_800ABA68[];
extern short D_800ABA54[];
extern short D_800ABA58;
extern unsigned short D_800E4D6C;
extern void func_80063DB8(unsigned short);

void func_80063A68(void) {
    unsigned short i;

    for (i = 0; i < 2; i++) {
        D_800E4ACC[i].value = 0;
        D_800E4ACC[i].flag = 0;
        func_80063DB8(i);
    }
    D_800ABA68[0] = 0;
    D_800ABA68[1] = 0;
    D_800ABA54[0] = 0;
    D_800ABA54[1] = 0;
    D_800ABA58 = 0;
    D_800E4D6C = 0;
}
