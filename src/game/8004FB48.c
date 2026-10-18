typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    u32 flags;
    u16 point_index;
    u16 point_count;
    Vector points[1];
} Path;

typedef struct {
    char pad000[0x180];
    u32 flags;
    Path path;
} Tank;

void func_8004E160(Tank *, Vector *, int, int);

void func_8004FB48(Tank *tank) {
    Path *path;
    Vector *point;
    int point_index;

    path = &tank->path;
    if (tank->flags & 1) {
        point_index = (path->point_index + 1) % path->point_count;
        point = &path->points[point_index];
        path->point_index = point_index;
        func_8004E160(tank, point, 0x64000, 1);
    }
}
