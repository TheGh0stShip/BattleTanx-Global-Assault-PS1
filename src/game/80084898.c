typedef struct PadAct {
    unsigned char act[2];
    unsigned short flags;
} PadAct;

typedef struct PadState {
    unsigned int mask;
    unsigned int unmask;
    unsigned int taps;
    PadAct act[8];
    int repeat[8];
    int flags;
    signed char threshold;
    char pad51[3];
    int mode;
    char pad58[8];
    int active;
    int hold[8];
    int timer[8];
} PadState;

typedef struct PadInput {
    int type;
    unsigned short buttons;
    unsigned short pressed;
    unsigned short released;
    unsigned short out_buttons;
    unsigned short out_pressed;
    unsigned short out_released;
    signed char x1;
    signed char y1;
    signed char cx1;
    signed char cy1;
    signed char lx1;
    signed char ly1;
    signed char hx1;
    signed char hy1;
    signed char dead1;
    signed char x2;
    signed char y2;
    signed char cx2;
    signed char cy2;
    signed char lx2;
    signed char ly2;
    signed char hx2;
    signed char hy2;
    signed char dead2;
    unsigned char b0;
    unsigned char b1;
    char pad24[4];
    unsigned short slot;
    char pad2A[0x62];
} PadInput;

extern PadState D_800EDF78;
extern PadInput D_800EE028[8];
extern PadAct D_800EDF84[8];
extern unsigned char D_800EEFF8[];
extern unsigned char D_800EF01A[];
extern unsigned char D_800B0DD0[];
extern int func_80094B50(int);
extern void func_80094D1C(int, unsigned char *, int);
extern int func_80094CE4(int, unsigned char *);
extern void func_80083E0C(int, int, int);
extern signed char func_80083CD4(signed char, signed char, signed char, signed char, signed char);
extern void func_80083C70(int);
extern void func_80083F6C(int, int);
extern void func_80084298(int);
extern void func_800844CC(int);
extern unsigned short func_80084034(int, unsigned short);

void func_80084898(int frames) {
    int port;
    PadAct *acts;
    int tapbit;
    int base;
    int tapbase;
    int slot;
    int bit;
    int count;
    int mask;
    int unmask;
    int id;
    int idx;
    unsigned char *p;
    register int dual asm("s6");
    int type;
    int padid;
    unsigned int btn;
    unsigned int old;
    unsigned int changed;
    unsigned char kind;
    unsigned int raw;

    if (frames == 0) {
        return;
    }
    idx = 0;
    bit = 1;
    mask = 0;
    unmask = 0;
    D_800EDF78.active = 0;
    D_800EDF78.taps = 0;
    p = D_800EEFF8;
    acts = D_800EDF84;
    tapbit = 1;
    base = 0;
    tapbase = 1;
    for (port = 0; port < 2; port++) {
        if (*p++ == 0) {
            if ((*p & 0xF0) == 0x80) {
                id = tapbase;
                count = 4;
                D_800EDF78.taps |= tapbit;
                p++;
            } else {
                p--;
                count = 1;
                id = base;
            }
            for (slot = 0; slot < count; slot++) {
                dual = 0;
                padid = (port << 4) | slot;
                type = func_80094B50(padid);
                switch (type) {
                case 0:
                case 1:
                    goto clear;
                case 6:
                    dual = 1;
                case 4:
                    if (!(D_800EDF78.act[idx].flags & 1)) {
                        func_80094D1C(padid, (unsigned char *)(idx * 4 + (int)acts), 2);
                        D_800EDF78.act[idx].flags |= 1;
                    }
                    if (type == 6 && !(D_800EDF78.act[idx].flags & 2)) {
                        if (func_80094CE4(padid, D_800B0DD0)) {
                            D_800EDF78.act[idx].flags |= 2;
                        } else {
                        clear:
                            D_800EDF78.act[idx].flags = 0;
                        }
                    }
                    break;
                case 2:
                case 3:
                case 5:
                    break;
                }
                if (*p == 0) {
                    kind = p[1] & 0xFC;
                    if (kind == 0x40 || kind == 0x70 || kind == 0x10) {
                        D_800EE028[idx].slot = id;
                        mask |= bit;
                        btn = ~*(unsigned short *)(p + 2);
                        raw = btn;
                        btn &= ~2;
                        if (D_800EDF78.mode == 4) {
                            if (raw & 0xFFF9) {
                                D_800EDF78.active = 1;
                            }
                        } else {
                            old = D_800EE028[idx].buttons;
                            if (kind == 0x10) {
                                D_800EE028[idx].type = 6;
                                switch ((int)(btn & 0xC00)) {
                                case 0x800:
                                    btn = 0x4000;
                                    break;
                                case 0x400:
                                    btn = 0x1000;
                                    break;
                                case 0xC00:
                                    btn = 0x5000;
                                    break;
                                case 0:
                                default:
                                    btn = 0;
                                    break;
                                }
                                func_80083E0C(idx, (signed char)p[4], (signed char)p[5]);
                                D_800EE028[idx].x2 = 0;
                                D_800EE028[idx].y2 = 0;
                                D_800EE028[idx].x1 = D_800EE028[idx].b0;
                                D_800EE028[idx].y1 = D_800EE028[idx].b1;
                                if (D_800EDF78.flags & 6) {
                                    if (D_800EE028[idx].x1 >= D_800EDF78.threshold) {
                                        btn |= 0x20;
                                    } else if (D_800EE028[idx].x1 <= -D_800EDF78.threshold) {
                                        btn |= 0x80;
                                    }
                                    if (D_800EE028[idx].y1 >= D_800EDF78.threshold) {
                                        btn |= 0x40;
                                    } else if (D_800EE028[idx].y1 <= -D_800EDF78.threshold) {
                                        btn |= 0x10;
                                    }
                                }
                            } else if (kind == 0x70) {
                                if (dual) {
                                    D_800EE028[idx].type = 4;
                                } else {
                                    D_800EE028[idx].type = 2;
                                }
                                D_800EE028[idx].x2 = p[4] + 128;
                                D_800EE028[idx].y2 = p[5] + 128;
                                D_800EE028[idx].x1 = p[6] + 128;
                                D_800EE028[idx].y1 = p[7] + 128;
                                D_800EE028[idx].x1 = func_80083CD4(D_800EE028[idx].x1, D_800EE028[idx].cx1, D_800EE028[idx].lx1, D_800EE028[idx].hx1, D_800EE028[idx].dead1);
                                D_800EE028[idx].y1 = func_80083CD4(D_800EE028[idx].y1, D_800EE028[idx].cy1, D_800EE028[idx].ly1, D_800EE028[idx].hy1, D_800EE028[idx].dead1);
                                D_800EE028[idx].x2 = func_80083CD4(D_800EE028[idx].x2, D_800EE028[idx].cx2, D_800EE028[idx].lx2, D_800EE028[idx].hx2, D_800EE028[idx].dead2);
                                D_800EE028[idx].y2 = func_80083CD4(D_800EE028[idx].y2, D_800EE028[idx].cy2, D_800EE028[idx].ly2, D_800EE028[idx].hy2, D_800EE028[idx].dead2);
                                if (D_800EDF78.flags & 2) {
                                    if (D_800EE028[idx].x1 >= D_800EDF78.threshold) {
                                        btn |= 0x20;
                                    } else if (D_800EE028[idx].x1 <= -D_800EDF78.threshold) {
                                        btn |= 0x80;
                                    }
                                    if (D_800EE028[idx].y1 >= D_800EDF78.threshold) {
                                        btn |= 0x40;
                                    } else if (D_800EE028[idx].y1 <= -D_800EDF78.threshold) {
                                        btn |= 0x10;
                                    }
                                }
                                if (D_800EDF78.flags & 4) {
                                    if (D_800EE028[idx].x2 >= D_800EDF78.threshold) {
                                        btn |= 0x20;
                                    } else if (D_800EE028[idx].x2 <= -D_800EDF78.threshold) {
                                        btn |= 0x80;
                                    }
                                    if (D_800EE028[idx].y2 >= D_800EDF78.threshold) {
                                        btn |= 0x40;
                                    } else if (D_800EE028[idx].y2 <= -D_800EDF78.threshold) {
                                        btn |= 0x10;
                                    }
                                }
                            } else {
                                if (dual) {
                                    D_800EE028[idx].type = 5;
                                } else {
                                    D_800EE028[idx].type = 1;
                                }
                                if (D_800EDF78.flags & 1) {
                                    if (btn & 0x80) {
                                        D_800EE028[idx].x1 = -128;
                                    } else if (btn & 0x20) {
                                        D_800EE028[idx].x1 = 127;
                                    } else {
                                        D_800EE028[idx].x1 = 0;
                                    }
                                    if (btn & 0x10) {
                                        D_800EE028[idx].y1 = -128;
                                    } else if (btn & 0x40) {
                                        D_800EE028[idx].y1 = 127;
                                    } else {
                                        D_800EE028[idx].y1 = 0;
                                    }
                                } else {
                                    D_800EE028[idx].x1 = 0;
                                    D_800EE028[idx].y1 = 0;
                                }
                                D_800EE028[idx].x2 = 0;
                                D_800EE028[idx].y2 = 0;
                            }
                            changed = btn ^ old;
                            D_800EE028[idx].pressed = btn & changed;
                            D_800EE028[idx].released = changed & ~btn;
                            D_800EE028[idx].buttons = btn;
                            if (D_800EE028[idx].type != 6) {
                                func_80083E0C(idx, D_800EE028[idx].x1, D_800EE028[idx].y1);
                                func_80083F6C(idx, frames);
                            }
                        }
                    } else {
                        if (D_800EDF78.mode != 4) {
                            func_80083C70(idx);
                        }
                        unmask |= bit;
                    }
                                } else {
                    if (D_800EDF78.mode != 4) {
                        func_80083C70(idx);
                    }
                }
                p += 8;
                idx++;
                bit <<= 1;
                id++;
            }
        }
        if (idx == 0) {
            if (D_800EDF78.mode != 4) {
                func_80083C70(0);
            }
            idx = 1;
            bit <<= idx;
        }
        p = D_800EF01A;
        tapbit = 2;
        base = 5;
        tapbase = 6;
    }
    if (D_800EDF78.mode != 4) {
        for (; idx < 8; idx++) {
            func_80083C70(idx);
        }
    }
    D_800EDF78.mask = mask;
    D_800EDF78.unmask = unmask;
    if (D_800EDF78.mode == 1) {
        func_80084298(frames);
    } else if (D_800EDF78.mode == 4) {
        func_800844CC(frames);
    }
    for (idx = 0; idx < 8; idx++) {
        if ((D_800EE028[idx].buttons & 9) == 9) {
            switch ((unsigned int)D_800EDF78.hold[idx]) {
            case 0:
                break;
            case 1:
                D_800EDF78.hold[idx] = 2;
                D_800EDF78.timer[idx] = 0;
                break;
            case 2:
                D_800EDF78.timer[idx] += frames;
                if ((unsigned int)D_800EDF78.timer[idx] < 2000) {
                    break;
                }
                D_800EDF78.hold[idx] = 3;
                goto set;
            case 3:
            set:
                D_800EE028[idx].buttons |= 2;
                D_800EE028[idx].pressed |= 2;
                break;
            }
        } else if ((D_800EE028[idx].buttons & 9) == 1) {
            D_800EDF78.hold[idx] = 1;
        } else {
            D_800EDF78.hold[idx] = 0;
        }
    }
    for (idx = 0; idx < 8; idx++) {
        if (D_800EDF78.mask & (1 << idx)) {
            D_800EE028[idx].out_buttons = (D_800EE028[idx].buttons == 0 || D_800EDF78.repeat[idx] == 0) ? D_800EE028[idx].buttons : func_80084034(idx, D_800EE028[idx].buttons);
            D_800EE028[idx].out_pressed = (D_800EE028[idx].pressed == 0 || D_800EDF78.repeat[idx] == 0) ? D_800EE028[idx].pressed : func_80084034(idx, D_800EE028[idx].pressed);
            D_800EE028[idx].out_released = (D_800EE028[idx].released == 0 || D_800EDF78.repeat[idx] == 0) ? D_800EE028[idx].released : func_80084034(idx, D_800EE028[idx].released);
        }
    }
}
