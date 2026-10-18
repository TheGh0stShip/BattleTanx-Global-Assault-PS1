typedef struct {
    unsigned short flags;
    signed char state;
    signed char sounds[6];
    char pad9[3];
    void *stream;
} Channel;
extern Channel D_800E474C[];
extern void func_8005AAEC(unsigned short);
extern void func_80059004(void *);

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

void func_8005992C(unsigned short index) {
    int parent;
    Channel *p;
    unsigned short j;
    unsigned short found;

    release_channel(index);
    parent = D_800E474C[index].state;
    if (parent < 0) {
        return;
    }
    if (D_800E474C[parent].flags == 0) {
        return;
    }
    p = &D_800E474C[parent];
    found = 0;
    for (j = 0; j < 6; j++) {
        if (p->sounds[j] == index) {
            p->sounds[j] = -1;
            break;
        }
        if (p->sounds[j] > 0) {
            found = 1;
        }
    }
    if (found == 0) {
        if (p->flags & 1) {
            p->flags |= 0x40;
        } else {
            p->flags |= 0x41;
            func_80059004(p->stream);
        }
    }
}
