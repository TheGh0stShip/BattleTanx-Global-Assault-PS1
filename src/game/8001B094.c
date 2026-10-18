typedef struct Cell {
    int flags;
    void *owner;
    unsigned short next[4];
    char pad10[0x28 - 0x10];
} Cell;
extern Cell D_800C62B0[];
extern unsigned short D_800C6288;
extern unsigned short D_800A4370;
void func_80015E24(unsigned short);

void func_8001B094(unsigned short id) {
    Cell *e;

    if (id == 0xFFFF) {
        return;
    }
    e = &D_800C62B0[id];
    if (e->flags == -1) {
        return;
    }
    if (D_800C6288 == id) {
        return;
    }
    e->flags = -1;
    func_80015E24(id);
    e->next[0] = D_800C6288;
    D_800C6288 = id;
    e->owner = 0;
    D_800A4370--;
}
