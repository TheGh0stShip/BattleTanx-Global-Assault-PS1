typedef struct SystemConfig {
    int enabled;
    char pad04[0x30 - 4];
    unsigned int heap_start;
    unsigned int heap_end;
} SystemConfig;
extern SystemConfig D_80086058;
extern char D_80086B4C[];
extern char D_8007F0E0[];
extern char D_8008A078[];
extern char D_80088324[];
extern char D_80085FAC[];
extern char D_800832C8[];
extern char D_80014750[];
extern char D_800BD484[];
extern char D_800BD488[];
extern char D_800BD48C[];
extern char D_800BD490[];
extern int D_800C60C0;
void func_80086800(void);
void func_8007F708(int, int);
int func_800868E0(char *, int);
void func_80082110(char *);
int func_800854EC(int, unsigned int, unsigned int, int);
void func_8008A428(int);
void func_80086BF4(char *, int);
void func_80086C68(char *);
void func_80083C50(void);
void func_8007A154(void);
void func_80083B18(void *);
void func_8007F5F8(char *);
int func_80082224(char *);
void func_8007EF30(int);
void func_800821AC(char *, int);
void func_800831F4(char *);
void func_80086C74(int);

int func_80014074(void) {
    int ok;

    D_80086058.heap_end = 0x80200000;
    func_80086800();
    func_8007F708(0, 0);
    ok = func_800868E0(D_80086B4C, 0);
    if (ok != 0) {
        func_80082110(D_8007F0E0);
        func_80082110(D_8008A078);
        func_80082110(D_80088324);
    }
    if (D_80086058.heap_start > D_80086058.heap_end) {
        ok = 0;
    }
    if (ok != 0) {
        if (func_800854EC(-1, D_80086058.heap_start, D_80086058.heap_end, 0) == 0) {
            ok = 0;
        }
    }
    D_80086058.heap_start = D_80086058.heap_end;
    func_8008A428(0x1F800300);
    if (ok != 0) {
        func_80086BF4(D_80085FAC, -1);
        func_80086C68(D_800832C8);
        func_80083C50();
        func_8007A154();
        func_80083B18(D_80014750);
        if (D_80086058.enabled != 0) {
            func_8007F5F8(D_800BD484);
            func_80082224(D_800BD488);
            func_8007EF30(1);
            func_800821AC(D_800BD48C, 0);
        }
        D_800C60C0 = func_80082224(D_800BD48C);
        func_800831F4(D_800BD490);
        func_80086C74(666);
    }
    return ok;
}
