typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int unk0;
    unsigned short tile;
    char pad6[30];
} Contact;

typedef struct {
    unsigned int flags;
    char pad4[16];
    short height;
    short x0;
    short x1;
    short z0;
    short z1;
    short rise_x;
    short rise_z;
    char pad22[6];
} Tile;

typedef struct {
    char pad0[32];
    int gravity;
    int floor;
    int bounce;
    char pad2C[8];
    short pitch;
    short roll;
    char pad38[4];
    int height[4];
    int velocity[4];
    unsigned char contact_flags;
    char pad5D[3];
    int locked;
} Body;

extern int D_800DE30C;
extern unsigned short D_800C628C;
extern Tile D_800C62B0[];

extern unsigned short func_80017AAC(int tile, int mask, Contact *contacts, int arg3, int arg4);
extern void func_80016FF4(Tile *tile, Point *points);
extern unsigned short func_80016D78(short x, short z, unsigned short tile);
extern int func_8001DA70(unsigned short tile, Point *point);
extern short func_8001D860(int delta, int extent);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline void gte_ldlzc(int value) {
    __asm__ volatile("mtc2 %0, $30\n\tnop\n\tnop" : : "r"(value));
}

static inline void gte_stlzc(int *result) {
    __asm__ volatile("swc2 $31, 0(%0)" : : "r"(result) : "memory");
}

static inline int leading_zeros(int value) {
    int count;

    gte_ldlzc(value);
    gte_stlzc(&count);
    return count;
}

int abs(int);

static inline int fixed_div(int numerator, int denominator) {
    int negative;
    int n;
    int d;
    int n_zeros;
    int d_zeros;
    int excess;
    int scale;
    unsigned int quotient;
    int result;

    negative = (numerator & 0x80000000) ^ (denominator & 0x80000000);
    __asm__("" : : "r"(negative));
    n = abs(numerator);
    d = abs(denominator);
    n_zeros = leading_zeros(n);
    excess = n_zeros - 12;
    if (excess < 0) {
        n <<= n_zeros;
        d_zeros = leading_zeros(d);
        n_zeros = d_zeros - n_zeros;
        if (n_zeros >= 0) {
            scale = 12 - d_zeros;
            if (scale >= 0) {
                quotient = (unsigned int)n / (d >> scale);
            } else {
                quotient = (unsigned int)n / (d << -scale);
            }
            quotient <<= n_zeros;
        } else {
            quotient = (unsigned int)n / (d >> -excess);
        }
    } else {
        n <<= 12;
        quotient = (unsigned int)n / d;
    }
    result = quotient;
    if (negative) {
        result = -result;
    }
    return result;
}

static inline int fixed_to_int(int value) {
    return value >= 0 ? value >> 12 : -(-value >> 12);
}

static inline int average(int total, int count) {
    return total / count;
}

static inline void get_tile_points(int tile, Point *points) {
    func_80016FF4(&D_800C62B0[tile], points);
}

static inline void get_tile_extent(Tile *tile, short *extent_x, short *extent_z) {
    *extent_x = tile->x1 - tile->x0 >= 0 ? tile->x1 - tile->x0 : tile->x0 - tile->x1;
    *extent_z = tile->z1 - tile->z0 >= 0 ? tile->z1 - tile->z0 : tile->z0 - tile->z1;
}

void func_8001E0A4(Body *body, unsigned short tile, int *out_height) {
    Point points[4];
    int previous[4];
    Contact contacts[8];
    unsigned short i;
    unsigned short j;
    unsigned short count;
    unsigned char changed;
    unsigned char have_points;
    int floor;
    int height;
    int delta;
    int divisor;
    int scaled;
    Tile *hit;

    if (body->locked != 0) {
        body->contact_flags |= 0xF;
        return;
    }

    for (i = 0; i < 4; i++) {
        body->velocity[i] -= fixed_mul(D_800DE30C, body->gravity);
        previous[i] = body->height[i];
        body->height[i] += body->velocity[i];
    }

    body->pitch = 0;
    body->roll = 0;
    D_800C628C = 0;
    count = func_80017AAC(tile, 0xE0, contacts, 0, 0);
    have_points = 0;
    changed = 0;
    body->contact_flags &= 0xF0;
    floor = body->floor;

    for (i = 0; i < 4; i++) {
        height = floor;
        for (j = 0; j < count; j++) {
            short x;
            short z;

            if (!have_points) {
                get_tile_points(tile, points);
                have_points = 1;
            }
            x = fixed_to_int(points[i].x) >> 2;
            z = fixed_to_int(points[i].y) >> 2;
            if (func_80016D78(x, z, contacts[j].tile)) {
                switch (D_800C62B0[contacts[j].tile].flags & 0xE0) {
                case 0x40:
                    __asm__ volatile("" : : : "memory");
                    height = func_8001DA70(contacts[j].tile, &points[i]);
                    break;
                case 0x20:
                    hit = &D_800C62B0[contacts[j].tile];
                    if (abs(hit->rise_x) > abs(hit->rise_z)) {
                        height = (short)(hit->rise_x + hit->height) << 14;
                    } else {
                        height = (short)(hit->rise_z + hit->height) << 14;
                    }
                    break;
                }
                break;
            }
        }
        if (height < floor) {
            if (height < 0) {
                height += floor;
            } else {
                height = floor;
            }
        }
        if (body->height[i] < height) {
            body->height[i] = height;
            delta = height - previous[i];
            if (delta >= 0) {
                scaled = fixed_mul(delta, body->bounce);
                divisor = D_800DE30C;
                if (divisor == 0) {
                    divisor = 2;
                }
                body->velocity[i] = fixed_div(scaled, divisor);
            } else {
                body->velocity[i] = fixed_mul(-2048, body->velocity[i]);
            }
            switch (i) {
            case 0:
                body->contact_flags |= 1;
                break;
            case 1:
                body->contact_flags |= 2;
                break;
            case 2:
                body->contact_flags |= 4;
                break;
            default:
                body->contact_flags |= 8;
                break;
            }
        }
        if (body->height[i] != body->floor) {
            changed = 1;
        }
    }

    if (changed) {
        short extent_x;
        short extent_z;
        int span_x;
        int span_z;

        get_tile_extent(&D_800C62B0[tile], &extent_x, &extent_z);
        span_z = extent_z << 14;
        span_x = extent_x << 14;
        height = body->height[0] - body->height[1];
        if (height != 0) {
            body->pitch = func_8001D860(height, span_z);
        }
        height = body->height[3] - body->height[2];
        if (height != 0) {
            body->pitch += func_8001D860(height, span_z);
        }
        height = body->height[3] - body->height[0];
        if (height != 0) {
            body->roll = func_8001D860(height, span_x);
        }
        height = body->height[2] - body->height[1];
        if (height != 0) {
            body->roll += func_8001D860(height, span_x);
        }
        *out_height = average(body->height[0] + body->height[1] + body->height[2] + body->height[3], 4);
    } else {
        *out_height = body->floor;
    }
}
