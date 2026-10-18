typedef struct {
    char pad[0xB8];
    short x;
    short y;
    char padBC[0x10];
    char disp[0x5C];
} DisplayBuffer;

typedef struct {
    char pad[0x30];
    int text_size;
    char pad34[0x18];
    int glyph_size;
} Message;

extern int D_800A48B0;
extern DisplayBuffer D_800DDB9C[];
extern unsigned short D_800EE02E;
extern int func_80083A5C(int mode);
extern void *func_80068F34(int size);
extern void func_80068F9C(void *p);
extern void func_8009304C(Message *m, void *text, int text_size, void *glyphs, int glyph_size);
extern int func_80093508(Message *m);
extern int func_80093248(Message *m, int x, int y, int elapsed);
extern void func_80083B2C(int mode);
extern void func_8007FFD8(void *env);
extern void func_8007FF18(void *env);
extern void func_80084898(int elapsed);
extern void func_80093470(Message *m);
extern void func_800934BC(Message *m);

void func_8006A8E4(Message *msg, unsigned char skippable) {
    int now;
    int prev;
    void *text;
    void *glyphs;

    now = func_80083A5C(2);
    prev = now;
    text = func_80068F34(msg->text_size);
    glyphs = func_80068F34(msg->glyph_size);
    func_8009304C(msg, text, msg->text_size, glyphs, msg->glyph_size);
    while (func_80093508(msg)) {
        if (func_80093248(msg, D_800DDB9C[D_800A48B0].x, D_800DDB9C[D_800A48B0].y, now - prev)) {
            func_80083B2C(3);
            func_8007FFD8(&D_800DDB9C[D_800A48B0].x);
            func_8007FF18(D_800DDB9C[D_800A48B0].disp);
            D_800A48B0 ^= 1;
        }
        prev = now;
        now = func_80083A5C(2);
        func_80084898(now - prev);
        if ((D_800EE02E & 0x4008) && skippable) {
            func_80093470(msg);
            break;
        }
    }
    func_80068F9C(text);
    func_80068F9C(glyphs);
    func_800934BC(msg);
}
