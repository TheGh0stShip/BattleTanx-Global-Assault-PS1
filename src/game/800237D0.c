extern unsigned int D_800A4388;

struct Node;
extern struct Node *func_80022B64(int kind);

struct Node *func_800237D0(int kind, int requested_size) {
    if (D_800A4388 < 0x40) {
        return 0;
    }
    return func_80022B64(kind);
}
