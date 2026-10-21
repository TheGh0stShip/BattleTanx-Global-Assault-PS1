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
extern int D_800D2FE0;
extern int D_800A5FAC[];
extern int func_800533B4(int);
extern void func_80090794(SpuVoiceAttr *);
extern void func_80090CE0(unsigned char, short, short);
extern void func_800907C4(int, int);
extern void func_800903A4(unsigned char, unsigned short);
extern int abs(int);

typedef struct {
    char pad0[8];
    int active;
} Owner;
typedef struct {
    Owner *owner;
    char pad4[0x3C - 4];
    int speed;
    int top_speed;
    char pad44[0x9C - 0x44];
    int type;
    char padA0[0x218 - 0xA0];
    unsigned int status;
    char pad21C[0x290 - 0x21C];
    unsigned char engine_voice;
    unsigned char move_voice;
    unsigned char start_voice;
    char pad293;
    int start_time;
} Tank;

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline void gte_ldlzc(int value) {
    __asm__ volatile("mtc2 %0, $30\n\tnop\n\tnop" : : "r"(value));
}

static inline void gte_stlzc(int *result) {
    __asm__ volatile("swc2 $31, 0(%0)" : : "r"(result) : "memory");
}

static inline int leading_zeros(int value) {
    int count;

    gte_ldlzc(value);
    gte_stlzc(&count);
    return count;
}


int abs(int);
static inline int fixed_div(int numerator, int denominator) {
    int negative;
    int n;
    int d;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int result;

    if (denominator == 0) {
        denominator = 2;
    }
    negative = (numerator & 0x80000000) ^ (denominator & 0x80000000);
    __asm__("" : : "r"(negative));
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        n <<= n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = (unsigned int)n / (d >> scale);
            } else {
                quotient = (unsigned int)n / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = (unsigned int)n / (d >> -excess);
        }
    } else {
        n <<= 12;
        quotient = (unsigned int)n / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static inline int to_int(int x) {
    return x >= 0 ? x >> 12 : -(-x >> 12);
}

static inline unsigned char play_voice(int id, int volume) {
    SpuVoiceAttr attr;
    Sound *sound = &D_800E4658[id];
    int voice;

    if (D_800E46BC == 0) {
        voice = sound->voice = (unsigned char)func_800533B4(1);
        if (voice != 100) {
            D_800E465C[voice].sound = id;
            attr.voice = 1 << sound->voice;
            attr.mask = 147;
            attr.addr = sound->addr;
            attr.pitch = sound->pitch;
            attr.volume.left = volume;
            attr.volume.right = volume;
            func_80090794(&attr);
            return sound->voice;
        }
    }
    return 100;
}

static inline void set_volume(unsigned char voice, short volume) {
    func_80090CE0(voice, volume, volume);
}


static inline void release_voice(unsigned char voice) {
    unsigned char i;

    set_volume(voice, 0);
    for (i = 0; i < 24; i++) {
        if (D_800E4658[i].voice == voice) {
            D_800E4658[i].voice = -1;
            break;
        }
    }
    func_800907C4(0, 1 << voice);
}

static inline int scale_pitch(int pitch) {
    int k = 1500;

    return pitch * k;
}

static inline void set_pitch(unsigned char voice, int value) {
    int pitch = to_int(value);

    if ((unsigned short)pitch >= 16384) {
        pitch = 16383;
    }
    func_800903A4(voice, pitch);
}

static inline unsigned short clamp_pitch(int pitch) {
    if ((unsigned short)pitch >= 16384) {
        pitch = 16383;
    }
    return pitch;
}

void func_80053FF4(Tank *tank) {
    int ratio;
    int elapsed;
    int sound;
    int pitch;
    short level;

    if (!(tank->status & 2) || tank->owner->active == 0 || D_800E46BC != 0) {
        return;
    }
    {
        int num = tank->speed;
        int den = tank->top_speed;
        int negative;
        int n;
        int d;
        int n_zeros;
        int d_zeros;
        int excess;
        int scale;
        unsigned int quotient;

        if (den == 0) {
            den = 2;
        }
        negative = (num & 0x80000000) ^ (den & 0x80000000);
        __asm__("" : : "r"(negative));
        n = abs(num);
        d = abs(den);
        n_zeros = leading_zeros(n);
        excess = n_zeros - 12;
        if (excess < 0) {
            n <<= n_zeros;
            d_zeros = leading_zeros(d);
            n_zeros = d_zeros - n_zeros;
            if (n_zeros >= 0) {
                scale = 12 - d_zeros;
                if (scale >= 0) {
                    quotient = (unsigned int)n / (d >> scale);
                } else {
                    quotient = (unsigned int)n / (d << -scale);
                }
                quotient <<= n_zeros;
            } else {
                quotient = (unsigned int)n / (d >> -excess);
            }
        } else {
            n <<= 12;
            quotient = (unsigned int)n / d;
        }
        ratio = quotient;
        if (negative) {
            ratio = -ratio;
        }

    }
    elapsed = D_800D2FE0 - tank->start_time;
    if (elapsed < 8) {
        if (tank->start_voice == 100) {
            tank->start_voice = play_voice(14, (short)D_800E4654);
        }
        if (elapsed >= 5) {
            set_volume(tank->start_voice, (short)D_800E4654 * (elapsed - 4) / 4);
        }
    } else {
        if (tank->start_voice != 100) {
            release_voice(tank->start_voice);
            tank->start_voice = 100;
        }
    }
    sound = 46;
    if (tank->type == 4) {
        sound = 24;
    }
    if (tank->engine_voice == 100) {
        tank->engine_voice = play_voice(sound, (short)D_800E4654 / 2);
    }
    pitch = fixed_div(ratio + 2048, 6144);
    pitch = fixed_mul(D_800A5FAC[tank->type], pitch);
    if (tank->type == 4) {
        pitch >>= 1;
    }
    set_pitch(tank->engine_voice, scale_pitch(pitch));
    set_volume(tank->engine_voice, (short)D_800E4654 / 2);
    if (tank->type == 4) {
        return;
    }
    if (ratio >= 820) {
        if (tank->move_voice == 100) {
            tank->move_voice = play_voice(48, (short)D_800E4654 / 2);
        }
        if (tank->status & 0x800) {
            int t = (short)D_800E4654 << 11;
            level = to_int(t);
        } else {
            level = to_int(ratio * (short)D_800E4654);
        }
        set_volume(tank->move_voice, level);
        set_pitch(tank->move_voice, scale_pitch(D_800A5FAC[tank->type]));
    } else {
        if (tank->move_voice != 100) {
            release_voice(tank->move_voice);
            tank->move_voice = 100;
        }
    }
}
