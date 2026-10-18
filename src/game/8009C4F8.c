extern void func_800943F0(void);
extern void func_8009C5EC(int state);

void func_8009C4F8(int state) {
    if (state == 0) {
        func_800943F0();
    }
    func_8009C5EC(state);
}
