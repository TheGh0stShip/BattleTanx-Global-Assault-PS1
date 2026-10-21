typedef struct Stream {
    int single;
    int wrapped;
    unsigned int size;
    unsigned int mark;
    unsigned int pos;
    unsigned int mask;
    int header_words;
    int step;
    int type[8];
} Stream;

typedef struct StreamState {
    char pad00[0x54];
    int mode;
    Stream *stream;
} StreamState;

typedef struct PadInput {
    char pad00[4];
    unsigned short buttons;
    char pad06[0xA];
    signed char x1;
    signed char y1;
    char pad12[7];
    signed char x2;
    signed char y2;
    char pad1B[7];
    signed char b0;
    signed char b1;
    short a0;
    short a1;
    char pad28[0x64];
} PadInput;

extern StreamState D_800EDF78;
extern int D_800EDFCC;
extern PadInput D_800EE028[8];
extern unsigned short *func_80084094(Stream *, unsigned short *);
extern void func_800841B8(Stream *, unsigned short *);
extern void func_8008A7BC(void *, void *, int);

void func_80084298(int frames) {
    Stream *st = D_800EDF78.stream;
    unsigned short *p = (unsigned short *)((char *)st + st->pos);
    unsigned short *next = p;
    int same;
    unsigned int i;
    char *q;
    signed char *b;
    unsigned short w;
    int aw;
    PadInput *pad;
    Stream *t;
    unsigned int type;
    unsigned short *us;

    if (*p >= 0xFFFE - (frames & 0xFFFF)) {
        next = func_80084094(st, p);
        if (D_800EDF78.mode == 1) {
            func_8008A7BC(next, p, st->step);
            p = next;
            *p = frames;
        }
    } else {
        *p += frames;
    }
    same = 1;
    if (D_800EDFCC == same) {
        q = (char *)(p + 1);
        for (i = 0, t = st; i < 8; i++) {
            if (same == 0) {
                break;
            }
            if (st->mask & (1 << i)) {
                w = *(unsigned short *)q;
                q += 2;
                if (w != D_800EE028[i].buttons) {
                    goto mismatch;
                }
                type = t->type[0];
                if (type - 2 < 3) {
                    b = (signed char *)q;
                    q += 4;
                    if (*b++ != D_800EE028[i].x1) {
                        goto mismatch;
                    }
                    if (*b++ != D_800EE028[i].y1) {
                        goto mismatch;
                    }
                    if (*b++ != D_800EE028[i].x2) {
                        goto mismatch;
                    }
                    if (*b != D_800EE028[i].y2) {
                        same = 0;
                    }
                } else if (type == 6) {
                    b = (signed char *)q;
                    q += 2;
                    if (*b++ != D_800EE028[i].b0 || *b != D_800EE028[i].b1) {
                        same = 0;
                    }
                    aw = *(unsigned short *)q;
                    q += 2;
                    if (aw != D_800EE028[i].a0) {
                        same = 0;
                    }
                    aw = *(unsigned short *)q;
                    q += 2;
                    if (aw != D_800EE028[i].a1) {
                        same = 0;
                    }
                }
                goto next;
            mismatch:
                same = 0;
            next:
                t = (Stream *)((char *)t + 4);
            }
        }
        if (D_800EDF78.mode == 1 && same == 0) {
            p = func_80084094(st, next);
            if (D_800EDF78.mode == 1) {
                func_800841B8(st, p);
            }
        }
    }
}
