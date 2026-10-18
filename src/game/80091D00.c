typedef unsigned char u8;

typedef struct State {
    u8 pad_00[0x24];
    short first;
    short second;
} State;

extern State D_800EEE3C;
extern void func_80091B18(int first, int second, int third, int fourth, int fifth);

void func_80091D00(int first) {
    func_80091B18(first, D_800EEE3C.first, D_800EEE3C.second, 0, 0);
}
