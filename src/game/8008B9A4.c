extern unsigned int D_800EEBAC;
extern void func_80098D40(unsigned int first, unsigned int second);

void func_8008B9A4(unsigned int value) {
    D_800EEBAC = value;
    func_80098D40(value / 3, value / 4);
}
