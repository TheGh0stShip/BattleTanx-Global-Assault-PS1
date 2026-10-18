typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Track {
    int dist;
    int hit;
    int best;
    int timer;
    unsigned char seen;
    unsigned char mode;
    char pad12[2];
    Vector target;
} Track;
typedef struct TrackTank {
    int id;
    char pad004[4];
    Vector position;
    char pad014[0xB8 - 0x14];
    Track track;
    char pad0D8[0x180 - 0xD8];
    int status;
} TrackTank;
typedef struct ProbeHit {
    short *object;
    char pad04[0x1C];
    unsigned short type;
    char pad22[2];
} ProbeHit;
extern short D_800C628C;
extern int D_800D2FE0;
unsigned short func_80019D80(Vector *, Vector *, int, int, int, ProbeHit *);

void func_8004E160(TrackTank *tank, Vector *pos, int dist, int seen) {
    ProbeHit hit;
    Track *track = &tank->track;
    int best = 64000 << 12;
    int timer = D_800D2FE0 + 300;

    tank->track.dist = 0;
    track->hit = 0;
    track->best = best;
    track->seen = 0;
    track->mode = 0;
    track->timer = timer;
    tank->track.dist = dist;
    tank->status &= ~1;
    track->seen = seen;
    D_800C628C = 0;
    if (func_80019D80(pos, &tank->position, 0x87007, 0, tank->id, &hit) && hit.type == 7 && hit.object != 0) {
        track->hit = *hit.object;
    }
    track->target.x = pos->x;
    track->target.z = pos->z;
    track->mode = 2;
}
