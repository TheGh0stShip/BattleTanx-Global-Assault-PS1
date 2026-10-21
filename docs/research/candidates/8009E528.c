typedef struct DriverState {
    int state;
    unsigned int flags;
} DriverState;

typedef struct PairState {
    int first;
    int second;
} PairState;

extern int D_800B8CA8;
extern int D_800B8CAC;
extern void (*D_800B8C78)(int value);
extern DriverState *D_800B8CD4;
extern unsigned char D_800EFC38;
extern PairState D_800EFC48;
extern void func_80094168(void);
extern void func_80094198(void);
extern void func_8009700C(int command, int value);
extern void func_800A3A04(int channel, void *state);
extern void func_800A3A14(int channel, void *state);

void func_8009E528(void) {
    void *transfer_state = &D_800EFC38;

    D_800B8CAC = 0;
    func_80094198();
    func_800A3A04(2, transfer_state);
    func_800A3A14(2, transfer_state);
    D_800B8CD4->state = -2;
    D_800B8CD4->flags |= 1;
    func_8009700C(3, 0);
    func_80094168();
    D_800B8C78(D_800B8CA8);
    D_800B8C78(D_800B8CA8 + 0xF0);
    D_800EFC48.second = 0;
    D_800EFC48.first = 0;
    D_800B8CAC = 1;
}
