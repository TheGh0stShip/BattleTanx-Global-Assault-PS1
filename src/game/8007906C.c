typedef struct {
    char pad0[4];
    unsigned short held;
    unsigned short pressed;
    unsigned short released;
    char padA[0xF];
    signed char axis;
    char pad1A[0x72];
} PadState;

extern PadState D_800EE028[];
extern unsigned short D_800EC0AC[][19];
extern int D_800EC0F8[];

int func_8007906C(unsigned int button, unsigned char port, int *pressed, int *released, int *analog) {
    int held;
    int v;

    unsigned short pr = D_800EE028[port].pressed;
    unsigned short hd = D_800EE028[port].held;
    unsigned short rl = D_800EE028[port].released;

    held = hd & D_800EC0AC[port][button];
    *pressed = pr & D_800EC0AC[port][button];
    *released = rl & D_800EC0AC[port][button];
    *analog = 0;
    switch (button) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        break;
    case 12:
    case 13:
        if (D_800EC0F8[port] == 1) {
            *analog = D_800EE028[port].axis;
        } else if (D_800EC0F8[port] == 6) {
            v = D_800EE028[port].axis;
            if ((v > 40 && button == 13) || (v < -40 && button == 12)) {
                return 1;
            }
        }
        break;
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        break;
    }
    return held;
}
