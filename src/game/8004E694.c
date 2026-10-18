typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Path {
    int kind;
    unsigned short current;
    unsigned short count;
    Vector points[1];
} Path;
typedef struct PathTank {
    char pad000[0x184];
    Path path;
    char pad198[0x218 - 0x198];
    int status;
} PathTank;
void func_8004E160(PathTank *, Vector *, int, int);
void func_8004D7D8(PathTank *);

static inline void path_add(Path *path, int x, int z) {
    Vector *point;

    path->count++;
    point = &path->points[path->count];
    path->kind = 2;
    point->x = x;
    point->z = z;
}

void func_8004E694(PathTank *tank, int alternate) {
    Path *path = &tank->path;

    path->kind = 2;
    tank->status &= ~0x100;
    path->current = 0;
    path->count = 0;
    if (alternate == 0) {
        path->kind = 2;
        tank->path.points[0].x = 1600 << 12;
        tank->path.points[0].z = -1050 << 12;
        path_add(path, 700 << 12, -1050 << 12);
        path_add(path, 700 << 12, -500 << 12);
        path_add(path, 1600 << 12, -500 << 12);
        path->count++;
    } else {
        path->kind = 2;
        tank->path.points[0].x = 700 << 12;
        tank->path.points[0].z = -1050 << 12;
        path_add(path, 1600 << 12, -1050 << 12);
        path_add(path, 1600 << 12, -1500 << 12);
        path_add(path, 700 << 12, -1500 << 12);
        path->count++;
    }
    func_8004E160(tank, &path->points[path->current], 100 << 12, 1);
    func_8004D7D8(tank);
}
