typedef struct Cell {
    int head;
    char pad04[4];
    unsigned short next[4];
    unsigned short x;
    unsigned short z;
    char pad14[2];
    short min_x;
    short max_x;
    short min_z;
    short max_z;
    char pad1E[0x28 - 0x1E];
} Cell;
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
void func_80016FF4(Cell *, Pos2 *);

int func_80017260(Cell *a, Cell *b) {
    Pos2 c[4];
    int v;

    func_80016FF4(b, c);
    v = c[0].x;
    if (c[1].x < v) {
        v = c[1].x;
    }
    if (c[2].x < v) {
        v = c[2].x;
    }
    if (c[3].x < v) {
        v = c[3].x;
    }
    if (a->max_x << 14 < v) {
        return 1;
    }
    v = c[0].x;
    if (v < c[1].x) {
        v = c[1].x;
    }
    if (v < c[2].x) {
        v = c[2].x;
    }
    if (v < c[3].x) {
        v = c[3].x;
    }
    if (v < a->min_x << 14) {
        return 1;
    }
    v = c[0].z;
    if (c[1].z < v) {
        v = c[1].z;
    }
    if (c[2].z < v) {
        v = c[2].z;
    }
    if (c[3].z < v) {
        v = c[3].z;
    }
    if (a->max_z << 14 < v) {
        return 1;
    }
    v = c[0].z;
    if (v < c[1].z) {
        v = c[1].z;
    }
    if (v < c[2].z) {
        v = c[2].z;
    }
    if (v < c[3].z) {
        v = c[3].z;
    }
    return v < a->min_z << 14;
}
