typedef unsigned char u8;
typedef unsigned short u16;

extern u8 D_800ABA60[];

void func_80063BD4(u16 index) {
    if (index < 2) {
        D_800ABA60[index] = 0;
    }
}
