typedef struct {
    short left;
    short right;
} SpuVolume;
typedef struct {
    unsigned long voice;
    unsigned long mask;
    SpuVolume volume;
    SpuVolume volmode;
    SpuVolume volumex;
    unsigned short pitch;
    unsigned short note;
    unsigned short sample_note;
    short envx;
    unsigned long addr;
    unsigned long loop_addr;
    long a_mode;
    long s_mode;
    long r_mode;
    unsigned short ar;
    unsigned short dr;
    unsigned short sr;
    unsigned short rr;
    unsigned short sl;
    unsigned short adsr1;
    unsigned short adsr2;
} SpuVoiceAttr;
typedef struct {
    unsigned long addr;
    char pad4[0x10 - 4];
    unsigned short pitch;
    short voice;
} Sound;
typedef struct {
    char pad0[3];
    unsigned char sound;
} Voice;
extern Sound *D_800E4658;
extern Voice D_800E465C[];
extern int D_800E46BC;
extern unsigned short D_800E4654;
extern int func_800533B4(int);
extern void func_80090794(SpuVoiceAttr *);
extern void func_80053790(unsigned char, int, int);
typedef struct {
    char pad0[8];
    int x8;
    char padC[4];
    int x10;
    char pad14[0x218 - 0x14];
    int status;
} Emitter;

static inline int play_sound(unsigned char id) {
    SpuVoiceAttr attr;
    Sound *sound = &D_800E4658[id];
    int voice;

    if (id == 255) {
        return 100;
    }
    if (D_800E46BC != 0) {
        return 100;
    }
    voice = sound->voice = (unsigned char)func_800533B4(0);
    if (voice == 100) {
        return 100;
    }
    D_800E465C[voice].sound = id;
    attr.voice = 1 << sound->voice;
    attr.mask = 147;
    attr.addr = sound->addr;
    attr.volume.left = D_800E4654;
    attr.volume.right = D_800E4654;
    attr.pitch = sound->pitch;
    func_80090794(&attr);
    return (unsigned char)sound->voice;
}

void func_80054DF8(Emitter *e, unsigned char id) {
    if (e->status & 2) {
        play_sound(id);
    } else {
        func_80053790(id, e->x8, e->x10);
    }
}
