typedef struct CardState {
    char pad00[0xC];
    int status[8];
} CardState;

extern CardState D_800EE588;
extern void func_80096008(int);
extern int func_80094E18(int);
extern int func_8009506C(int);
extern void func_80086CAC(int, int *, int *);

int func_80086FC4(unsigned int chan) {
    int result = 0;
    int event;
    int code;
    int slot = ((chan >> 2) & 4) | (chan & 3);

    event = 0;
    func_80096008(result);
    if (func_80094E18(chan)) {
        func_80086CAC(0x18, &event, &code);
    }
    if (event == 1) {
        switch (code) {
        case 0:
            result = D_800EE588.status[slot];
            if (result != (int)0xFFFF0000) {
                goto done;
            }
            break;
        case 3:
            break;
        default:
            goto done;
        }
        event = 0;
        if (func_8009506C(chan)) {
            func_80086CAC(0xA4, &event, &code);
        }
        if (event == 2) {
            if (code == 3) {
                event = 0;
                if (func_8009506C(chan)) {
                    func_80086CAC(0xA4, &event, &code);
                }
            }
            if (event == 2) {
                if (code == 0) {
                    result = 7;
                } else if ((unsigned int)code < 5) {
                    if ((unsigned int)code >= 3) {
                        result = 5;
                    }
                }
            }
        }
    }
done:
    D_800EE588.status[slot] = result;
    return result;
}
