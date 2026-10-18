typedef struct {
    short x, y, z, end;
} Point;

int func_8007374C(Point *out, int i, int count, Point *points) {
    Point max;
    Point min;
    Point *p;

    max.z = -32000;
    max.y = -32000;
    max.x = -32000;
    min.z = 32000;
    min.y = 32000;
    min.x = 32000;
    do {
        p = &points[i];
        if (p->x < min.x) {
            min.x = p->x;
        }
        if (p->y < min.y) {
            min.y = p->y;
        }
        if (p->z < min.z) {
            min.z = p->z;
        }
        if (p->x > max.x) {
            max.x = p->x;
        }
        if (max.y < p->y) {
            max.y = p->y;
        }
        if (max.z < p->z) {
            max.z = p->z;
        }
        i++;
    } while (i < count && points[i].end == 0);
    out->x = (min.x + max.x) / 2;
    out->y = (min.y + max.y) / 2;
    out->z = (min.z + max.z) / 2;
    return i;
}
