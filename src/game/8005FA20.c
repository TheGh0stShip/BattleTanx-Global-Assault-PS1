typedef unsigned char u8;
typedef unsigned short u16;

extern u8 D_800AACD9;
extern u8 D_800AACDA;
extern u16 D_800E4A90;
extern void func_8003DEF8(void);
extern void func_80059A80(void *object);
extern void func_80075AEC(void);

int func_8005FA20(void *object) {
    D_800E4A90 = 1;
    D_800AACD9 = 0;
    D_800AACDA = 0;
    func_8003DEF8();
    func_80075AEC();
    func_80059A80(object);
    return 0;
}
