typedef struct { short x, y, z, pad; } Vert;
typedef struct { short x, y; } Delta;
void func_8003AF64(short, short, int, short);
void func_8003B738(short, short, short);

void func_800399D0(Vert *v, int shift) {
    int mask;
    short i;
    short top;
    short miny;
    short maxy;
    Delta d[4];
    short right;
    short left;
    short y;
    short right_end;
    short left_end;
    int right_x;
    int left_x;
    int right_step;
    int left_step;
    short w;
    short dy;
    short j;

    mask = 0xFFFF << shift;
    top = 0;
    miny = maxy = v[0].y;
    for (i = 1; i < 4; i++) {
        if (v[i].y < miny) {
            miny = v[i].y;
            top = i;
        }
        if (v[i].y == miny && v[i].x < v[top].x) {
            top = i;
        }
        if (maxy < v[i].y) {
            maxy = v[i].y;
        }
    }
    for (i = 0; i < 4; i++) {
        d[i].x = v[i].x - v[(i + 1) & 3].x;
        d[i].y = v[i].y - v[(i + 1) & 3].y;
    }
    while (d[top].y == 0) {
        top = (top + 1) & 3;
    }
    right = top;
    y = v[right].y;
    right_x = v[right].x << 16;
    right_end = v[(right + 1) & 3].y;
    right_step = (d[right].x << 16) / d[right].y;
    j = right;
    while (d[(j - 1) & 3].y == 0) {
        j = (j - 1) & 3;
    }
    left = (j - 1) & 3;
    left_x = v[j].x << 16;
    left_end = v[left].y;
    left_step = (d[left].x << 16) / d[left].y;
    do {
        if (y >= left_end) {
            left_x = v[left].x << 16;
            do {
                left = (left - 1) & 3;
                dy = d[left].y;
            } while (dy == 0);
            left_end = v[left].y;
            left_step = (d[left].x << 16) / dy;
        }
        if (y >= right_end) {
            do {
                right = (right + 1) & 3;
                dy = d[right].y;
            } while (dy == 0);
            right_end = v[(right + 1) & 3].y;
            right_x = v[right].x << 16;
            right_step = (d[right].x << 16) / dy;
        }
        w = ((left_x >> 16) - (right_x >> 16)) >> shift;
        switch (shift) {
        case 1:
            func_8003AF64((mask & (right_x >> 16)) << 6, (y & mask) << 6, 1, w);
            break;
        case 2:
            func_8003B738((mask & (right_x >> 16)) << 6, (y & mask) << 6, w);
            break;
        }
        y += 1 << shift;
        right_x += right_step << shift;
        left_x += left_step << shift;
    } while (y <= maxy);
}
