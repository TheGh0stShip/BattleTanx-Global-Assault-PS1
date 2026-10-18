typedef struct Cell {
    int head;
    char pad04[4];
    unsigned short next;
    char pad0A[0x28 - 0xA];
} Cell;
typedef struct Bounds {
    char pad00[0xC];
    short x0;
    short z0;
    short x1;
    short z1;
} Bounds;
extern Cell D_800C62B0[1300];
extern short D_800C6288;
extern short D_800A4370;
extern Bounds *D_800D2FE4;
void func_8008AA48(void *, int, int);
void func_80015A80(int, int, int, int);

void func_800159B0(void) {
    unsigned short i;

    func_8008AA48(D_800C62B0, 0, sizeof(D_800C62B0));
    for (i = 0; i < 1299; i++) {
        D_800C62B0[i].next = i + 1;
        D_800C62B0[i].head = -1;
    }
    D_800C62B0[1299].next = 0xFFFF;
    D_800C62B0[1299].head = -1;
    D_800C6288 = 0;
    D_800A4370 = 0;
    func_80015A80(D_800D2FE4->x0, D_800D2FE4->z0, D_800D2FE4->x1, D_800D2FE4->z1);
    func_80015A80(-12000, -12000, 12000, 12000);
}
