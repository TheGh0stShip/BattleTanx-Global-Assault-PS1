typedef struct Stream {
    char pad00[0x2C];
    int user;
    unsigned char open;
    unsigned char state31;
    unsigned char reading;
    unsigned char ready;
    char pad34[4];
    unsigned char cached;
    unsigned char seeking;
    char pad3A[2];
    unsigned char pending;
    char pad3D[0x1B];
    unsigned int start;
    unsigned int end;
    char pad60[8];
    void (*callback)(int, int);
    char pad6C[0x24];
    unsigned int sector;
    unsigned int target;
} Stream;

extern Stream D_800EEAE8;
extern void func_80091984(void);
extern void func_80088FB0(void);
extern void func_800916F4(void);
extern void func_8009194C(void);
extern int func_80089294(void);

int func_800893AC(unsigned int pos, void (*cb)(int, int)) {
    int result = 1;
    int buffered;

    if (D_800EEAE8.open != 0) {
        buffered = 0;
        if (pos >= D_800EEAE8.start) {
            buffered = pos < D_800EEAE8.end;
        }
        if (buffered) {
            pos = D_800EEAE8.end;
        }
        if (D_800EEAE8.cached != 0 && D_800EEAE8.seeking != 0
            && (buffered || D_800EEAE8.sector == (pos & ~0x7FF))) {
            if (cb != 0) {
                cb(D_800EEAE8.user, 1);
            }
        } else {
            func_80091984();
            if (D_800EEAE8.ready == 0 || D_800EEAE8.reading == 0 || D_800EEAE8.seeking != 0
                || D_800EEAE8.pending != 0) {
                func_80088FB0();
            }
            func_800916F4();
            func_8009194C();
            D_800EEAE8.reading = 0;
            D_800EEAE8.state31 = 0;
            D_800EEAE8.callback = cb;
            D_800EEAE8.target = pos;
            result = func_80089294();
        }
    } else if (cb != 0) {
        cb(D_800EEAE8.user, 0);
        result = 0;
    }
    return result;
}
