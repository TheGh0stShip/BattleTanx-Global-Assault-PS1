typedef struct { int x, y, z; } Vector;
typedef struct Turret Turret;
typedef struct { char pad[76]; Turret *turret; char rest[156 - 80]; } Player;
struct Turret {
    int pad[2];
    Vector pos;
    int pad2[2];
    int pitch;
    unsigned short yaw_offset;
    short pad3;
    int pad4;
    unsigned short yaw;
    unsigned char pad5;
    unsigned char flags;
    unsigned char player;
};
extern Player D_800D3034[];
void func_8006A158(int, Vector *, unsigned short, unsigned short, int);

void func_8002C928(Turret *t) {
    Turret *q = t;

    if ((t->flags & 8) == 0) {
        if (D_800D3034[t->player].turret == t) {
            func_8006A158(102, &t->pos, (t->pitch - 16384) / 5, t->yaw + t->yaw_offset, 0);
        } else {
            func_8006A158(102, &q->pos, (q->pitch - 16384) / 5, q->yaw, 0);
        }
    }
}
