typedef struct { char pad[0x14]; short height; char pad2[0x24 - 0x16]; unsigned short heading; char pad3[40 - 0x26]; } Voice;
typedef struct { char pad[8]; int x; int y; int z; char pad2[0x2C - 0x14]; unsigned short heading; char pad3[0x2B8 - 0x2E]; unsigned short voice; } Obj;
extern Voice D_800C62B0[];
static inline Voice *voice_get(int id)
{
    return &D_800C62B0[id];
}
extern void func_80015F64(int, short, short);

static inline int to_int(int v)
{
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

static inline void voice_update(unsigned int id, unsigned short heading, short x, short z)
{
    if (id != 0xFFFF) {
        voice_get(id)->heading = heading;
        func_80015F64(id, x, z);
    }
}

void func_80040380(Obj *obj)
{
    short x;
    short z;
    int y;
    unsigned int id;

    if (obj->voice != 0xFFFF) {
        x = to_int(obj->x) >> 2;
        z = to_int(obj->z) >> 2;
        y = (short)(to_int(obj->y) >> 2);
        id = obj->voice;
        voice_update(id, obj->heading, x, z);
        voice_get(id)->height = y;
    }
}
