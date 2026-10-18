typedef struct {
    unsigned int voice;
    unsigned int mask;
    char pad8[12];
    unsigned short pitch;
    char pad16[42];
} VoiceAttr;
typedef struct {
    char pad0[3];
    unsigned char sound;
} VoiceSlot;
typedef struct {
    char pad0[0x10];
    unsigned short pitch;
    short link;
} SoundEntry;
extern int D_800E46BC;
extern SoundEntry *D_800E4658;
extern VoiceSlot D_800E465C[];
extern void func_80090C54(unsigned char *);
extern void func_80090E10(VoiceAttr *);

void func_80054CA0(void) {
    VoiceAttr attr;
    unsigned char status[24];
    unsigned char i;

    func_80090C54(status);
    for (i = 0; i < 24; i++) {
        if (status[i] == 1) {
            attr.voice = 1 << i;
            attr.mask = 16;
            attr.pitch = D_800E4658[D_800E465C[i].sound].pitch;
            func_80090E10(&attr);
        }
    }
    D_800E46BC = 0;
}
