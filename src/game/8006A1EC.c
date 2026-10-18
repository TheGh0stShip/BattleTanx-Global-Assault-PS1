typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;

typedef struct Bounds {
    int min_x;
    int min_z;
    int max_x;
    int max_z;
} Bounds;

extern Bounds D_800D2E04;

int func_8006A1EC(int margin, Vector *pos) {
    if (pos->x + margin < D_800D2E04.min_x << 12 || pos->z + margin < D_800D2E04.min_z << 12 ||
        D_800D2E04.max_x << 12 < pos->x - margin || D_800D2E04.max_z << 12 < pos->z - margin) {
        return 0;
    }
    return 1;
}
