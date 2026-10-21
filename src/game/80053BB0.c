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

typedef struct {
    char pad0[8];
    int x;
    char padC[4];
    int z;
} Body;
typedef struct Waypoint {
    char pad000[0x5C];
    Body *body;
    char pad060[0x114 - 0x60];
} Waypoint;
typedef struct {
    char pad0[8];
    unsigned char count;
} Game;
extern Waypoint D_800E3E68[];
extern Game D_800D2FE4;
extern int abs(int);

static inline Waypoint *waypoint(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

static inline int to_int(int x) {
    return x >= 0 ? x >> 12 : -(-x >> 12);
}

static inline void play_at(unsigned char id, int level) {
    SpuVoiceAttr attr;
    Sound *sound = &D_800E4658[id];
    int voice;

    if (D_800E46BC != 0) {
        return;
    }
    voice = sound->voice = (unsigned char)func_800533B4(0);
    if (voice == 100) {
        return;
    }
    D_800E465C[voice].sound = id;
    attr.voice = 1 << sound->voice;
    attr.mask = 147;
    attr.addr = sound->addr;
    attr.pitch = sound->pitch;
    attr.volume.left = level;
    attr.volume.right = level;
    func_80090794(&attr);
}

void func_80053BB0(unsigned char id, int x, int z, int scale) {
    short best = 0;
    int i;

    for (i = 0; i < D_800D2FE4.count; i++) {
        int dx;
        int dz;
        int big;
        unsigned int d;
        short volume;
        short v;

        {
            int t = x - waypoint(i)->body->x;
            dx = to_int(t);
        }
        {
            int t = z - waypoint(i)->body->z;
            dz = t >= 0 ? t >> 12 : -(-t >> 12);
        }
        big = abs(dz);
        dx = abs(dx);
        if (big < dx) {
            big = dx;
        }
        dz = abs(dz);
        if (dx < dz) {
            dz = dx;
        }
        d = (big + dz * 3 / 8) / 3;
        if (d > (short)D_800E4654) {
            d = (short)D_800E4654;
        }
        volume = D_800E4654 - d;
        v = to_int(scale * volume);
        if (v > best) {
            best = v;
        }
        if (best > 250) {
            play_at(id, best);
            return;
        }
    }
}
