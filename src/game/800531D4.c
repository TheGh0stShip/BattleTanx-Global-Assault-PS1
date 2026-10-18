typedef struct {
    char pad0[6];
    unsigned char flags;
    unsigned char channel;
    char pad8[0xDC - 8];
    int last_time[1];
} Emitter;
typedef struct {
    unsigned char id;
    char pad[3];
} SoundRef;
extern int D_800D2FE0;
extern int D_800AE74C[];
extern SoundRef D_800A5B3C[];
extern void func_80063018(int, int, int);
extern void func_80054A30(int);

void func_800531D4(Emitter *emitter, int index) {
    int now;

    if (emitter != 0 && (emitter->flags & 2)) {
        now = D_800D2FE0;
        if (now - emitter->last_time[index] > 60) {
            emitter->last_time[index] = now;
            func_80063018(emitter->channel, D_800AE74C[index], 45);
            func_80054A30(D_800A5B3C[index].id);
        }
    }
}
