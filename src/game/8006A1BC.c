typedef unsigned short u16;

extern void func_80069494(
    void *first,
    int second,
    u16 third,
    u16 fourth,
    u16 fifth,
    int sixth
);

void func_8006A1BC(
    void *first,
    int second,
    u16 third,
    u16 fourth,
    u16 fifth
) {
    func_80069494(first, second, third, fourth, fifth, 0);
}
