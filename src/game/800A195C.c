typedef struct Link {
    int unk00;
    volatile int flags;
    char pad08[0x1C];
    int last_time;
    char pad28[8];
    unsigned char cmd;
    unsigned char seq;
    char pad32[2];
    int count;
    int data38;
    int data3C;
    int data40;
    int data44;
    int data48;
} Link;

extern Link *D_800EFE14;
extern void func_800A19E4(int);

extern int func_800A2914(int, int, int);

unsigned char func_800A195C(Link *c) {
    unsigned char seq = c->seq + 1;
    while (seq == 0x1B || seq == 0xAB) {
        seq++;
    }
    return seq;
}

int func_800A1994(int unused, int a, int b, int d) {
    return func_800A2914(a, b, d);
}

int func_800A19BC(int unused, int a, int b, int d) {
    return func_800A2914(a, b, d);
}
