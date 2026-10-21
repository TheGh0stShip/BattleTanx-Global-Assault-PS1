typedef struct {
    char pad0[8];
    int x;
    char padC[4];
    int z;
} Body;
typedef struct Waypoint {
    char pad000[0x5C];
    Body *body;
    char pad060[0x114 - 0x60];
} Waypoint;
typedef struct {
    char pad0[8];
    unsigned char count;
} Game;
extern Waypoint D_800E3E68[];
extern Game D_800D2FE4;
extern unsigned short D_800E4654;
extern int abs(int);

static inline Waypoint *waypoint(int index) {
    if (index == 127) {
        return 0;
    }
    return &D_800E3E68[index];
}

static inline int to_int(int x) {
    return x >= 0 ? x >> 12 : -(-x >> 12);
}

short func_80053598(int x, int z) {
    short best = 0;
    int frame_pad[3];
    unsigned short i;
    int hx;
    int hz;
    int px;
    int pz;
    unsigned int d;
    short volume;

    hx = to_int(x);
    hz = to_int(z);
    for (i = 0; i < D_800D2FE4.count; i++) {
        px = to_int(waypoint(i)->body->x);
        pz = to_int(waypoint(i)->body->z);
        {
            int dz = hz - pz;
            int dx = abs(hx - px);
            int max = abs(dz);
            int min;
            if (max < dx) max = dx;
            min = dx < abs(dz) ? dx : abs(dz);
            d = (max + min * 3 / 8) / 3;
        }
        if (d > (short)D_800E4654) {
            d = (short)D_800E4654;
        }
        volume = D_800E4654 - d;
        if (volume > best) {
            best = volume;
        }
    }
    if (best > 0) {
        return best;
    }
    return 0;
}
