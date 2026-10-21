typedef struct PadInput {
    int type;
    unsigned short buttons;
    char pad06[10];
    signed char lx;
    signed char ly;
    char pad12[7];
    signed char rx;
    signed char ry;
    char pad1B[113];
} PadInput;

extern PadInput D_800EE028[];
extern int D_800EC0F8[];
extern unsigned short D_800EC0AC[][19];
extern signed char D_800EC094[];
extern signed char D_800EC09C[];
extern signed char D_800EC0A4[];
extern int D_800A6070;

static inline void dead29(signed char *out, signed char v) {
    *out = v;
    if ((unsigned char)(v + 29) < 59) {
        *out = 0;
    }
}

static inline void dead40(signed char *out, signed char v) {
    *out = v;
    if ((unsigned char)(v + 40) < 81) {
        *out = 0;
    }
}

static inline void clamp85(signed char *out, signed char v) {
    if (v > 85) {
        *out = 85;
    }
    if (v < -85) {
        *out = -85;
    }
}

int func_800791C8(unsigned char slot, signed char *steer, signed char *drive, signed char *aim) {
    signed char lx = D_800EE028[slot].lx;
    signed char ry = D_800EE028[slot].ry;
    signed char ly = D_800EE028[slot].ly;
    signed char rx = D_800EE028[slot].rx;
    unsigned short buttons = D_800EE028[slot].buttons;
    short sum;
    short v;

    *aim = 0;
    *drive = 0;
    *steer = 0;
    switch (D_800EE028[slot].type) {
    case 2:
    case 3:
    case 4:
        switch (D_800EC0F8[slot]) {
        case 1:
        case 6:
            dead29(steer, ly);
            *drive = 0;
            dead40(aim, lx);
            break;
        case 3:
            dead29(steer, ly);
            dead40(drive, lx);
            dead40(aim, rx);
            clamp85(aim, rx);
            break;
        case 4:
            dead29(steer, ry);
            dead40(drive, rx);
            dead40(aim, lx);
            clamp85(aim, lx);
            break;
        case 5:
            sum = (ly + ry) / 2;
            if ((unsigned short)(sum + 29) < 59) {
                *steer = 0;
            } else {
                *steer = sum;
            }
            v = ry - ly;
            if (v < -125) {
                *drive = -125;
            } else if (v > 125) {
                *drive = 125;
            } else if ((unsigned short)(v + 40) < 81) {
                *drive = 0;
            } else {
                *drive = v;
            }
            *aim = 0;
            break;
        case 0:
        case 2:
            dead29(steer, ly);
            dead40(drive, lx);
            *aim = 0;
            break;
        }
        if (D_800A6070 == 7) {
            dead29(steer, ly);
            dead40(drive, lx);
            *aim = 0;
        }
    case 1:
    case 5:
        if ((*steer | *drive | *aim) == 0) {
            switch ((unsigned int)D_800EC0F8[slot]) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 6:
                if ((buttons & D_800EC0AC[slot][0]) || (buttons & D_800EC0AC[slot][1])) {
                    *steer = D_800EC094[slot];
                    if (*steer == 0) {
                        if (buttons & D_800EC0AC[slot][0]) {
                            *steer = -40;
                        } else {
                            *steer = 40;
                        }
                    } else {
                        if ((buttons & D_800EC0AC[slot][0]) && *steer > 0) {
                            *steer = -40;
                        }
                        if ((buttons & D_800EC0AC[slot][1]) && *steer < 0) {
                            *steer = 40;
                        }
                    }
                    v = *steer + (*steer >> 3);
                    if (v > 120) {
                        v = 120;
                    }
                    if (v < -120) {
                        v = -120;
                    }
                    D_800EC094[slot] = v;
                    *steer = v;
                } else {
                    D_800EC094[slot] = 0;
                    *steer = 0;
                }
                if ((buttons & D_800EC0AC[slot][2]) || (buttons & D_800EC0AC[slot][3])) {
                    *drive = D_800EC09C[slot];
                    if (*drive == 0) {
                        if (buttons & D_800EC0AC[slot][2]) {
                            *drive = -40;
                        } else {
                            *drive = 40;
                        }
                    } else {
                        if ((buttons & D_800EC0AC[slot][2]) && *drive > 0) {
                            *drive = -40;
                        }
                        if ((buttons & D_800EC0AC[slot][3]) && *drive < 0) {
                            *drive = 40;
                        }
                    }
                    v = *drive + (*drive >> 3);
                    if (v > 120) {
                        v = 120;
                    }
                    if (v < -120) {
                        v = -120;
                    }
                    D_800EC09C[slot] = v;
                    *drive = v;
                } else {
                    D_800EC09C[slot] = 0;
                    *drive = 0;
                }
                if ((buttons & D_800EC0AC[slot][4]) || (buttons & D_800EC0AC[slot][5])) {
                    *aim = D_800EC0A4[slot];
                    if (*aim == 0) {
                        if (buttons & D_800EC0AC[slot][4]) {
                            *aim = -40;
                        } else {
                            *aim = 40;
                        }
                    } else {
                        if ((buttons & D_800EC0AC[slot][4]) && *aim > 0) {
                            *aim = -40;
                        }
                        if ((buttons & D_800EC0AC[slot][5]) && *aim < 0) {
                            *aim = 40;
                        }
                    }
                    v = *aim + (*aim >> 3);
                    if (v > 120) {
                        v = 120;
                    }
                    if (v < -120) {
                        v = -120;
                    }
                    D_800EC0A4[slot] = v;
                    *aim = v;
                } else {
                    D_800EC0A4[slot] = 0;
                    *aim = 0;
                }
                break;
            case 5:
                if ((buttons & D_800EC0AC[slot][0]) || (buttons & D_800EC0AC[slot][1])) {
                    *steer = D_800EC094[slot];
                    if (*steer == 0) {
                        if (buttons & D_800EC0AC[slot][0]) {
                            *steer = -40;
                        } else {
                            *steer = 40;
                        }
                    } else {
                        if ((buttons & D_800EC0AC[slot][0]) && *steer > 0) {
                            *steer = -40;
                        }
                        if ((buttons & D_800EC0AC[slot][1]) && *steer < 0) {
                            *steer = 40;
                        }
                    }
                    v = *steer + (*steer >> 3);
                    if (v > 120) {
                        v = 120;
                    }
                    if (v < -120) {
                        v = -120;
                    }
                    D_800EC094[slot] = v;
                    *steer = v;
                } else {
                    D_800EC094[slot] = 0;
                    *steer = 0;
                }
                if ((buttons & D_800EC0AC[slot][10]) || (buttons & D_800EC0AC[slot][14])) {
                    *drive = D_800EC09C[slot];
                    if (*drive == 0) {
                        if (buttons & D_800EC0AC[slot][10]) {
                            *drive = -40;
                        } else {
                            *drive = 40;
                        }
                    } else {
                        if ((buttons & D_800EC0AC[slot][10]) && *drive > 0) {
                            *drive = -40;
                        }
                        if ((buttons & D_800EC0AC[slot][14]) && *drive < 0) {
                            *drive = 40;
                        }
                    }
                    v = *drive + (*drive >> 3);
                    if (v > 120) {
                        v = 120;
                    }
                    if (v < -120) {
                        v = -120;
                    }
                    D_800EC09C[slot] = v;
                    *drive = v;
                } else {
                    D_800EC09C[slot] = 0;
                    *drive = 0;
                }
                ly = *steer;
                rx = *drive;
                sum = (*steer + *drive) / 2;
                if ((unsigned short)(sum + 39) < 79) {
                    *steer = 0;
                } else {
                    *steer = sum;
                }
                v = rx - ly;
                if (v < -120) {
                    *drive = -120;
                } else if (v > 120) {
                    *drive = 120;
                } else if ((unsigned short)(v + 39) < 79) {
                    *drive = 0;
                } else {
                    *drive = v;
                }
                *aim = 0;
                break;
            }
        }
        break;
    case 0:
    case 6:
        break;
    }
    return (signed char)(*steer | *drive | *aim);
}
