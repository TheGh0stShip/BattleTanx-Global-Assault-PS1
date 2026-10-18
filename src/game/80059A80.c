typedef struct {
    unsigned short flags;
    signed char state;
    signed char sounds[6];
    char pad9[3];
    void *stream;
} Channel;
extern Channel D_800E474C[];
extern void func_8005AAEC(unsigned short);

static inline void release_channel(unsigned short index) {
    unsigned short k;

    for (k = 0; k < 6; k++) {
        if (D_800E474C[index].sounds[k] > 0) {
            func_8005AAEC(D_800E474C[index].sounds[k]);
            D_800E474C[index].sounds[k] = -1;
        }
    }
    D_800E474C[index].flags = 0;
}

void func_80059A80(void *stream) {
    unsigned short i;
    unsigned short j;
    int child;

    for (i = 0; i < 10; i++) {
        if (D_800E474C[i].stream == stream) {
            for (j = 0; j < 6; j++) {
                child = D_800E474C[i].sounds[j];
                if (child > 0) {
                    release_channel(child);
                    D_800E474C[i].sounds[j] = -1;
                }
            }
            return;
        }
    }
}
