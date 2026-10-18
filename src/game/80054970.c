typedef struct {
    short left;
    short right;
} Volume;
typedef struct {
    unsigned int mask;
    Volume mvol;
    char pad8[32];
} CommonAttr;
typedef struct {
    unsigned int voice;
    unsigned int mask;
    Volume volume;
    char pad0C[8];
    unsigned short pitch;
    char pad16[14];
    int a_mode;
    int s_mode;
    int r_mode;
    unsigned short ar;
    unsigned short dr;
    unsigned short sr;
    unsigned short rr;
    unsigned short sl;
    char pad3A[6];
} VoiceAttr;
extern char D_800E43CC[];
extern int D_800E46BC;
extern short D_800E4654;
extern void func_80090254(int, char *);
extern void func_80090414(CommonAttr *);
extern void func_80090E10(VoiceAttr *);
extern void func_8006B028(void);

void func_80054970(void) {
    CommonAttr common;
    VoiceAttr voice;
    VoiceAttr *attr;

    func_80090254(80, D_800E43CC);
    common.mask = 3;
    common.mvol.left = 0x3FFF;
    common.mvol.right = 0x3FFF;
    func_80090414(&common);
    D_800E46BC = 0;
    D_800E4654 = 5461;
    attr = &voice;
    attr->mask = 0xFF93;
    voice.voice = 0xFFFFFF;
    attr->volume.left = 0x3FFF;
    attr->volume.right = 0x3FFF;
    attr->pitch = 4096;
    attr->a_mode = 1;
    attr->s_mode = 1;
    attr->r_mode = 3;
    voice.ar = 0;
    voice.dr = 0;
    voice.sr = 0;
    voice.rr = 0;
    attr->sl = 15;
    func_80090E10(attr);
    func_8006B028();
}
