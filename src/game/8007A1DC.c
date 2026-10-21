typedef struct Blob20 {
    unsigned char b[20];
} Blob20;

typedef struct Group {
    char pad0[20];
    Blob20 *slots[51];
} Group;

typedef struct SlotState {
    int phase;
    int scale;
    unsigned char *cur;
    unsigned char value;
    unsigned char extra;
    unsigned char flag;
    unsigned char pad;
} SlotState;

typedef struct SlotDef {
    signed char group;
    unsigned char index;
    unsigned char flags;
    unsigned char extra;
} SlotDef;

typedef struct VehicleDef {
    char pad0[204];
    SlotDef *slots;
} VehicleDef;

typedef struct Obj {
    char pad0[156];
    int type;
    char pad1[616];
    Group groups[2];
    Blob20 copies[5];
    SlotState state[5];
} Obj;

extern VehicleDef D_800A4EF4[];

void func_8007A1DC(Obj *o) {
    Obj *obj = o;
    int i;
    Blob20 *copies = obj->copies;
    unsigned char *cur;
    Group *groups = obj->groups;
    SlotDef *def;

    def = D_800A4EF4[obj->type].slots;
    for (i = 0; i < 5; i++) {
        if (def[i].group != -1) {
            copies[i] = *groups[def[i].group].slots[def[i].index];
            obj->groups[def[i].group].slots[def[i].index] = &obj->copies[i];
            obj->state[i].phase = 0;
            obj->state[i].scale = 4096;
            obj->state[i].extra = def[i].extra;
            obj->state[i].flag = (def[i].flags >> 1) & 1;
            cur = &copies[i].b[def[i].flags & 1];
            obj->state[i].value = *cur;
            obj->state[i].cur = cur;
        } else {
            obj->state[i].cur = 0;
        }
    }
}
