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

typedef struct ReplayState {
    unsigned int mask;
    unsigned int unmask;
    char pad08[0x44];
    int flags;
    signed char threshold;
    char pad51[3];
    int mode;
    Stream *stream;
    int counter;
    int type;
} ReplayState;

typedef struct PadInput {
    int type;
    unsigned short buttons;
    unsigned short pressed;
    unsigned short released;
    char pad0A[6];
    signed char x1;
    signed char y1;
    char pad12[7];
    signed char x2;
    signed char y2;
    char pad1B[7];
    unsigned char b0;
    unsigned char b1;
    unsigned short a0;
    unsigned short a1;
    char pad28[0x64];
} PadInput;

extern ReplayState D_800EDF78;
extern PadInput D_800EE028[8];
extern unsigned short *func_80084094(Stream *, unsigned short *);
extern void func_80083F6C(int, int);
extern void func_80083C70(int);

void func_800844CC(int frames) {
    Stream *st = D_800EDF78.stream;
    unsigned short *p;
    unsigned short *q;
    unsigned int i;
    int n;
    unsigned int buttons;
    unsigned int old;
    unsigned int changed;
    int counter;
    int type;

    p = (unsigned short *)((char *)st + st->pos);
    counter = D_800EDF78.counter + frames;
    D_800EDF78.counter = counter;
    if ((unsigned short)(*(unsigned short *)&D_800EDF78.counter + 1) >= *p) {
        D_800EDF78.counter = counter - *p;
        p = func_80084094(st, p);
    }
    if (D_800EDF78.mode != 4) {
        return;
    }
    n = 0;
    q = p + 1;
    for (i = 0; i < 8; i++) {
        if (st->mask & (1 << i)) {
            buttons = *q++;
            type = st->type[n];
            D_800EE028[i].type = type;
            old = D_800EE028[i].buttons;
            if (type == 6) {
                D_800EE028[i].b0 = ((unsigned char *)q)[0];
                D_800EE028[i].b1 = ((unsigned char *)q)[1];
                D_800EE028[i].x2 = 0;
                D_800EE028[i].y2 = 0;
                D_800EE028[i].x1 = D_800EE028[i].b0;
                D_800EE028[i].y1 = D_800EE028[i].b1;
                q++;
                if (D_800EDF78.flags & 6) {
                    if (D_800EE028[i].x1 >= D_800EDF78.threshold) {
                        buttons |= 0x20;
                    } else if (D_800EE028[i].x1 <= -D_800EDF78.threshold) {
                        buttons |= 0x80;
                    }
                    if (D_800EE028[i].y1 >= D_800EDF78.threshold) {
                        buttons |= 0x40;
                    } else if (D_800EE028[i].y1 <= -D_800EDF78.threshold) {
                        buttons |= 0x10;
                    }
                }
                D_800EE028[i].a0 = *q++;
                D_800EE028[i].a1 = *q++;
            } else if ((unsigned int)(type - 2) < 3) {
                D_800EE028[i].x1 = ((unsigned char *)q)[0];
                D_800EE028[i].y1 = ((unsigned char *)q)[1];
                q++;
                D_800EE028[i].x2 = ((unsigned char *)q)[0];
                D_800EE028[i].y2 = ((unsigned char *)q)[1];
                q++;
                if (D_800EDF78.flags & 2) {
                    if (D_800EE028[i].x1 >= D_800EDF78.threshold) {
                        buttons |= 0x20;
                    } else if (D_800EE028[i].x1 <= -D_800EDF78.threshold) {
                        buttons |= 0x80;
                    }
                    if (D_800EE028[i].y1 >= D_800EDF78.threshold) {
                        buttons |= 0x40;
                    } else if (D_800EE028[i].y1 <= -D_800EDF78.threshold) {
                        buttons |= 0x10;
                    }
                }
                if (D_800EDF78.flags & 4) {
                    if (D_800EE028[i].x2 >= D_800EDF78.threshold) {
                        buttons |= 0x20;
                    } else if (D_800EE028[i].x2 <= -D_800EDF78.threshold) {
                        buttons |= 0x80;
                    }
                    if (D_800EE028[i].y2 >= D_800EDF78.threshold) {
                        buttons |= 0x40;
                    } else if (D_800EE028[i].y2 <= -D_800EDF78.threshold) {
                        buttons |= 0x10;
                    }
                }
            } else {
                if (D_800EDF78.flags & 1) {
                    if (buttons & 0x80) {
                        D_800EE028[i].x1 = -128;
                    } else if (buttons & 0x20) {
                        D_800EE028[i].x1 = 127;
                    } else {
                        D_800EE028[i].x1 = 0;
                    }
                    if (buttons & 0x10) {
                        D_800EE028[i].y1 = -128;
                    } else if (buttons & 0x40) {
                        D_800EE028[i].y1 = 127;
                    } else {
                        D_800EE028[i].y1 = 0;
                    }
                } else {
                    D_800EE028[i].x1 = 0;
                    D_800EE028[i].y1 = 0;
                }
                D_800EE028[i].x2 = 0;
                D_800EE028[i].y2 = 0;
            }
            changed = buttons ^ old;
            D_800EE028[i].pressed = buttons & changed;
            D_800EE028[i].released = changed & ~buttons;
            D_800EE028[i].buttons = buttons;
            if (D_800EE028[i].type != 6) {
                func_80083F6C(i, frames);
            }
            n++;
        } else {
            func_80083C70(i);
        }
        {
            unsigned int mask = st->mask;
            D_800EDF78.mask = mask;
            D_800EDF78.unmask = ~mask;
        }
    }
}
