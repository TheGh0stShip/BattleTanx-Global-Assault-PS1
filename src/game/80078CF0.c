typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;

extern char *D_800A4358;
extern char D_800AE9B8[];
extern char D_800AEB24[];
extern char D_800C3E04[];
typedef struct BytePair {
    u8 first;
    u8 second;
} BytePair;

extern BytePair D_800EBBB4;
extern s32 D_800EBC38;
extern s32 D_800EBC3C;
extern s32 D_800EBC44;
extern u16 D_800EBC50;
extern char D_800EBC54[];
extern s32 func_80086E6C(void *state);
extern void func_80086EA8(s32 mode);
extern void func_80088618(s32 count, void *table);
extern void func_80088644(void *destination, void *source, s32 zero_a,
                          s32 zero_b, void *table, s32 count);
extern void func_8008DA04(void *destination, void *source);

void func_80078CF0(void) {
    register s32 count asm("$17") = 100;
    register char *state asm("$16");
    s32 offset;

    func_80088618(0x41, D_800AEB24);
    func_80088644(D_800A4358 + 0x94, D_800A4358 + 0x14, 0, 0,
                  D_800AE9B8, count);
    func_80086EA8(1);
    state = D_800EBC54;
    offset = func_80086E6C(state);
    asm volatile("" : : "r"(state));
    func_8008DA04(state + offset, D_800C3E04);
    D_800EBC50 = count;
    D_800EBC3C = 0;
    D_800EBBB4.second = 0;
    D_800EBC38 = 0;
    D_800EBBB4.first = 0;
    D_800EBC44 = 0;
}
