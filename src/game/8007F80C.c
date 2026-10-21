typedef struct {
    int (*fn[16])();
} GpuDriver;

typedef struct {
    volatile unsigned char version;
    unsigned char reset;
    unsigned char level;
    char pad3;
    unsigned short width;
    unsigned short height;
    char pad8[8];
    char env[92];
    char clip[20];
} GpuState;

extern GpuState D_800B0C60;
extern int D_800B0C18;
extern GpuDriver *D_800B0C58;
extern int (*D_800B0C5C)(char *, ...);
extern unsigned int D_800B0CE0[];
extern unsigned int D_800B0CEC[];
extern char D_800C4B24[];
extern char D_800C4B44[];
extern void func_800943B0(char *, ...);
extern void func_80081E64(void *, int, int);
extern void func_800943F0(void);
extern void func_80094A38(int);
extern int func_8008189C(int);

int func_8007F80C(int mode) {
    switch (mode & 7) {
    case 3:
    case 0:
        func_800943B0(D_800C4B24, &D_800B0C18, &D_800B0C60);
    case 5:
        func_80081E64(&D_800B0C60, 0, 128);
        func_800943F0();
        func_80094A38((int)D_800B0C58 & 0xFFFFFF);
        D_800B0C60.version = func_8008189C(mode);
        D_800B0C60.reset = 1;
        D_800B0C60.width = D_800B0CE0[D_800B0C60.version];
        D_800B0C60.height = D_800B0CEC[D_800B0C60.version];
        func_80081E64(D_800B0C60.env, -1, 92);
        func_80081E64(D_800B0C60.clip, -1, 20);
        return D_800B0C60.version;
    }
    if (D_800B0C60.level >= 2) {
        D_800B0C5C(D_800C4B44, mode);
    }
    return D_800B0C58->fn[13](1);
}
