typedef struct { char pad[32]; int x; int y; int z; int pad2[4]; int value; } Target;
typedef struct {
    int pad[2];
    Target *target;
    int pad2[2];
    int value;
    char pad3[52 - 24];
    unsigned char locked;
    unsigned char pad4;
    unsigned char state;
    unsigned char pad5;
    int hp;
} Obj;
typedef struct { int pad; unsigned short type; } Msg;
typedef struct { int pad[3]; unsigned short source; short pad2; int amount; } MsgData;
void func_80035238(Obj *, int);
int func_8008AE30(int, int);

typedef struct { unsigned char valid; char pad[3]; int x; int z; } Query;
typedef struct { int x; int z; } Hit2;
typedef struct { int x; int y; int z; int drain; } Hit3;

static inline void handle_msg(Obj *obj, Msg *msg, MsgData *data, int *result) {
    int v;
    int state;

    switch ((short)msg->type) {
    case 7:
    case 12:
    case 39:
    case 40:
    case 52:
        *result = 1;
        if (obj->state == 3) {
            v = obj->hp - data->amount;
            obj->hp = v;
            if (v <= 0) {
                func_80035238(obj, data->source);
            } else if (v < 125 && obj->value != 0) {
                obj->target->value = obj->value;
            }
        } else if (obj->locked == 0) {
            func_80035238(obj, data->source);
        }
        break;
    case 4:
        state = obj->state;
        if (state == 2 || state == 3) {
            *result = 1;
        } else if (state == 6) {
            *result = 1;
        } else {
            *result = 9;
            if (obj->locked == 0) {
                func_80035238(obj, data->source);
            }
        }
        break;
    case 30:
    case 75:
        *result = 1;
        break;
    }
}

void func_800354D0(Obj *obj, Msg *msg, unsigned int event, void *data, void *out) {
    Obj *self = obj;
    int angle;
    int v;

    switch (event) {
    case 0:
        handle_msg(self, msg, data, out);
        break;
    case 5:
        if (*(int *)data == 0) {
            ((Query *)out)->valid = 1;
            ((Query *)out)->x = obj->target->x;
            ((Query *)out)->z = obj->target->z;
        }
        break;
    case 6:
        func_80035238(obj, (func_8008AE30(obj->target->x - ((Hit2 *)data)->x, obj->target->z - ((Hit2 *)data)->z) &
                            0xFFF)
                               << 4);
        break;
    case 3:
        angle = (func_8008AE30(obj->target->x - ((Hit3 *)data)->x, obj->target->z - ((Hit3 *)data)->z) & 0xFFF) << 4;
        if (msg == 0) {
            break;
        }
        if (obj->state == 3) {
            v = obj->hp - ((Hit3 *)data)->drain;
            obj->hp = v;
            if (v <= 0) {
                func_80035238(obj, angle);
            } else if (v < 75 && obj->value != 0) {
                obj->target->value = obj->value;
            }
        } else if (obj->locked == 0) {
            func_80035238(obj, angle);
        }
        break;
    }
}
