typedef struct { int x; int y; int z; } Vector;
typedef struct { char pad[8]; Vector pos; char pad2[156 - 20]; } View;
typedef struct { unsigned char f0; unsigned char current; char pad[2]; View views[1]; } ViewSet;
typedef struct { char pad[20]; Vector rel; Vector pos; } Obj;
extern ViewSet D_800D3034;

static inline int round_int(int a, int b)
{
    int r;
    int v;

    v = a - b;
    if (v >= 0) {
        r = v + 2048;
        if (r >= 0) {
            return r >> 12;
        }
        return -(-r >> 12);
    }
    r = v - 2048;
    if (r >= 0) {
        return r >> 12;
    }
    return -((2048 - v) >> 12);
}

static inline void relative_pos(Vector *out, Vector *pos, View *ref)
{
    out->x = round_int(pos->x, ref->pos.x);
    out->y = round_int(pos->y, ref->pos.y);
    out->z = round_int(pos->z, ref->pos.z);
}

void func_8003EA5C(Obj *obj)
{
    relative_pos(&obj->rel, &obj->pos, &D_800D3034.views[D_800D3034.current]);
}
