typedef struct {
    char pad0[0x12];
    short voice;
} SoundEntry;
extern SoundEntry *D_800E4658;
extern void func_80090CE0(int, int, int);
extern void func_800907C4(int, int);

void func_80054EF4(int voice) {
    unsigned char i;

    func_80090CE0((unsigned char)voice, 0, 0);
    for (i = 0; i < 24; i++) {
        if (D_800E4658[i].voice == (unsigned char)voice) {
            D_800E4658[i].voice = -1;
            break;
        }
    }
    func_800907C4(0, 1 << voice);
}
