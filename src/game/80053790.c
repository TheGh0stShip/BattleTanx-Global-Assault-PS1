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

typedef struct {
    short m[3][3];
    int t[3];
} Matrix;
typedef struct {
    short vx;
    short vy;
    short vz;
    short pad;
} SVector;
typedef struct {
    Matrix matrix;
    char pad20[156 - 0x20];
} View;
typedef struct {
    char pad0;
    unsigned char view;
    char pad2[84 - 2];
    View views[1];
} ViewState;
extern ViewState D_800D3034;
extern int func_8008AE30(int, int);
extern int func_8008B830(int);

static inline void gte_SetRotMatrix(Matrix *m) {
    __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tctc2 $12, $0\n\tctc2 $13, $1\n\t"
                     "lw $12, 8(%0)\n\tlw $13, 12(%0)\n\tlw $14, 16(%0)\n\tctc2 $12, $2\n\tctc2 $13, $3\n\tctc2 $14, $4"
                     :
                     : "r"(m)
                     : "$12", "$13", "$14");
}

static inline void gte_ldv0(SVector *v) {
    __asm__ volatile("lwc2 $0, 0(%0)\n\tlwc2 $1, 4(%0)" : : "r"(v));
}

static inline void gte_rtv0(void) {
    __asm__ volatile("nop\n\tnop\n\tcop2 0x0486012");
}

static inline void gte_stsv(SVector *v) {
    __asm__ volatile("mfc2 $12, $9\n\tmfc2 $13, $10\n\tmfc2 $14, $11\n\tsh $12, 0(%0)\n\tsh $13, 2(%0)\n\tsh $14, 4(%0)"
                     :
                     : "r"(v)
                     : "$12", "$13", "$14", "memory");
}

static inline void play_pan(unsigned char id, int volume, int pn) {
    SpuVoiceAttr attr;
    Sound *sound = &D_800E4658[id];
    int voice;
    short left;
    short right;
    short pan;

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
    left = volume;
    right = volume;
    pan = pn;
    if (pan != 0) {
        int scaled = abs(pan);
        int full = 0x3FFF;
        scaled = (full - scaled) * volume / full;
        if (pan < 0) {
            right = scaled;
        } else {
            left = scaled;
        }
    }
    attr.pitch = sound->pitch;
    attr.volume.left = left;
    attr.volume.right = right;
    func_80090794(&attr);
}

void func_80053790(unsigned char id, int x, int z) {
    short best = 0;
    unsigned short i;
    int hx;
    int hz;
    int px;
    int pz;
    int dx;
    unsigned int d;
    short volume;
    SVector v;
    SVector out;
    int angle;
    short pan;

    hx = to_int(x);
    hz = to_int(z);
    for (i = 0; i < D_800D2FE4.count; i++) {
        px = to_int(waypoint(i)->body->x);
        pz = to_int(waypoint(i)->body->z);
        pz = hz - pz;
        {
            int max = abs(pz);
            int adx;
            int min;
            dx = hx - px;
            adx = abs(dx);
            if (max < adx) max = adx;
            min = adx < abs(pz) ? adx : abs(pz);
            d = (max + min * 3 / 8) / 3;
        }
        if (d > (short)D_800E4654) {
            d = (short)D_800E4654;
        }
        volume = D_800E4654 - d;
        if (volume > best) {
            best = volume;
        }
        if (best > 250) {
            v.vx = dx;
            v.vy = 0;
            v.vz = pz;
            gte_SetRotMatrix(&D_800D3034.views[D_800D3034.view].matrix);
            gte_ldv0(&v);
            gte_rtv0();
            gte_stsv(&out);
            angle = func_8008AE30(out.vx, out.vz);
            if (func_8008B830(angle) > 1024) {
                pan = ((angle > 0 ? 2048 : -2048) - angle) << 4;
            } else {
                pan = angle << 4;
            }
            play_pan(id, best, pan);
            return;
        }
    }
}
