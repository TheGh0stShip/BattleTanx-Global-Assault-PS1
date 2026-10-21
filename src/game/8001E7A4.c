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

int abs(int);
static inline int fixed_to_int(int value) {
    int result;
    result = value >= 0 ? value >> 12 : -(-value >> 12);
    return result;
}
static inline void get_tile_points(int tile, Point *points) {
    Tile *t = &D_800C62B0[tile];
    func_80016FF4(t, points);
}
void func_8001E7A4(Body *body, unsigned short tile) {
    Point points[4];
    Contact contacts[8];
    unsigned short i;
    unsigned short j;
    unsigned short count;
    unsigned short have_points;
    int floor;
    int height;

    D_800C628C = 0;
    count = func_80017AAC(tile, 0xE0, contacts, 0, 0);
    have_points = 0;
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
            x = (short)((unsigned int)fixed_to_int(points[i].x) >> 2);
            z = (short)(fixed_to_int(points[i].y) >> 2);
            if (func_80016D78(x, z, contacts[j].tile)) {
                switch (D_800C62B0[contacts[j].tile].flags & 0xE0) {
                case 0x40:
                    __asm__ volatile("" : : : "memory");
                    height = func_8001DA70(contacts[j].tile, &points[i]);
                    break;
                case 0x20: {
                    Tile *hit = &D_800C62B0[contacts[j].tile];
                    if (abs(hit->rise_x) > abs(hit->rise_z)) {
                        height = (short)(hit->rise_x + hit->height) << 14;
                    } else {
                        height = (short)(hit->rise_z + hit->height) << 14;
                    }
                    break;
                }
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
        body->height[i] = height;
        body->velocity[i] = 0;
    }
}
