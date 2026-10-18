typedef struct {
    unsigned char v[8];
} Fade;

typedef struct {
    char pad0[6];
    unsigned short buttons;
} Pad;

extern signed char D_800A606C;
extern int D_800A6070;
extern int D_800A48DC;
extern unsigned char D_800D2FEC;
extern unsigned char D_800D3034[];
extern int D_800D2FE0;
extern unsigned char D_800AEA45;
extern unsigned char D_800AACE1;
extern Pad D_800EE028;
extern Fade D_800BD570;
extern void func_8003C79C(void);
extern void func_8003A200(int);
extern void func_800206B0(void);
extern void func_80084898(int);
extern void func_8007FA74(int);
extern void func_80088870(int);
extern void func_8007FBF8(Fade *, int, int, int);
extern void func_80020924(void);
extern void func_8003DDB4(void);

void func_80020D50(void) {
    Fade fade;
    int players;

    players = D_800A606C;
    if (players == 1) {
        D_800D2FEC = players;
    } else if (players == 2) {
        D_800D2FEC = players;
    }
    D_800D3034[0] = 0;
    D_800D3034[1] = 0;
    D_800D2FE0 = 0;
    if (D_800A48DC == 0) {
        func_8003C79C();
    }
    if (D_800A6070 == 1) {
        if (D_800A48DC == 0) {
            func_8003A200(5);
            D_800AEA45 = 1;
            func_800206B0();
            D_800AEA45 = 2;
            do {
                func_80084898(100);
            } while (!(D_800EE028.buttons & 0x4000));
            D_800AEA45 = 0;
        } else {
            func_8007FA74(0);
            func_80088870(0);
            fade = D_800BD570;
            func_8007FBF8(&fade, 0, 0, 0);
            func_800206B0();
        }
    } else {
        if (D_800A48DC == 0) {
            D_800AACE1 = 1;
        } else {
            func_8007FA74(0);
            func_80088870(0);
            fade = D_800BD570;
            func_8007FBF8(&fade, 0, 0, 0);
        }
        func_80020924();
        D_800AACE1 = 0;
    }
    func_80088870(0);
    func_80088870(0);
    func_8007FA74(0);
    func_8003DDB4();
    D_800A48DC = 0;
}
