typedef unsigned short u16;

extern int D_800D2E14[];

void func_80069494(int type, void *position, u16 third, u16 fourth, u16 fifth, int zero);

void func_8006A158(int type, void *position, u16 third, u16 fourth, u16 fifth) {
    func_80069494(D_800D2E14[type], position, third, fourth, fifth, 0);
}
