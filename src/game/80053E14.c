typedef struct {
    char pad0[0x12];
    short voice;
} Sound;
typedef struct {
    char pad0[0x290];
    unsigned char voice_b;
    unsigned char voice_c;
    unsigned char voice_a;
} Obj;
extern Sound *D_800E4658;
extern void func_80090CE0(int, int, int);
extern void func_800907C4(int, int);

static inline void stop_voice(unsigned char voice) {
    unsigned char i;

    func_80090CE0(voice, 0, 0);
    for (i = 0; i < 24; i++) {
        if (D_800E4658[i].voice == voice) {
            D_800E4658[i].voice = -1;
            break;
        }
    }
    func_800907C4(0, 1 << voice);
}

void func_80053E14(Obj *obj) {
    if (obj->voice_a != 100) {
        stop_voice(obj->voice_a);
        obj->voice_a = 100;
    }
    if (obj->voice_b != 100) {
        stop_voice(obj->voice_b);
        obj->voice_b = 100;
    }
    if (obj->voice_c != 100) {
        stop_voice(obj->voice_c);
        obj->voice_c = 100;
    }
}
