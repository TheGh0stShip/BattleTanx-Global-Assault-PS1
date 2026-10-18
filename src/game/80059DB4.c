typedef struct {
    unsigned short flags;
    signed char state;
    signed char sounds[6];
    char pad9[3];
    void *stream;
} Channel;
extern Channel D_800E474C[];
extern void func_8005AB98(unsigned short);
extern void func_80057E40(void *);

static inline void stop_channel(unsigned short index) {
    unsigned short j;

    for (j = 0; j < 6; j++) {
        if (D_800E474C[index].sounds[j] > 0) {
            func_8005AB98(D_800E474C[index].sounds[j]);
        }
    }
    if (D_800E474C[index].flags & 1) {
        func_80057E40(D_800E474C[index].stream);
    }
}

void func_80059DB4(void) {
    short i;

    for (i = 0; i < 10; i++) {
        if (D_800E474C[i].flags != 0 && D_800E474C[i].state < 0) {
            stop_channel(i);
        }
    }
}
