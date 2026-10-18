typedef struct { char pad[20]; int x; int pad2; int z; int hp; int pad3; unsigned char dead; } Obj;
typedef struct { int pad; unsigned short type; } Msg;
typedef struct { int pad[4]; int amount; } MsgData;
typedef struct { unsigned char valid; char pad[3]; int x; int z; } Query;
typedef struct { int x; int z; } Hit2;
typedef struct { int x; int y; int z; } Hit3;
int func_8008AE30(int, int);
void func_8002E260(Obj *, int, int);

static inline void handle_msg(Obj *obj, Msg *msg, MsgData *data, int *result) {
    int v;

    switch ((short)msg->type) {
    case 7:
    case 12:
    case 39:
    case 40:
    case 52:
        if (obj->dead == 0) {
            *result = 1;
            v = obj->hp - data->amount;
            obj->hp = v;
            if (v < 0) {
                func_8002E260(obj, 0, 0);
            }
        }
        break;
    case 4:
        if (obj->dead != 0) {
            *result = 8;
        } else {
            *result = 1;
        }
        break;
    case 30:
    case 75:
        *result = 1;
        break;
    case 13:
    case 23:
        func_8002E260(obj, 0, 0);
        break;
    }
}

void func_8002E3B8(Obj *obj, Msg *msg, unsigned int event, void *data, void *out) {
    Obj *self = obj;

    switch (event) {
    case 0:
        handle_msg(self, msg, data, out);
        break;
    case 5:
        if (*(int *)data == 0 && obj->dead == 0) {
            ((Query *)out)->valid = 1;
            ((Query *)out)->x = obj->x;
            ((Query *)out)->z = obj->z;
        }
        break;
    case 6:
        if (obj->dead == 0) {
            func_8002E260(obj, (func_8008AE30(obj->x - ((Hit2 *)data)->x, obj->z - ((Hit2 *)data)->z) & 0xFFF) << 4, 1);
        }
        break;
    case 3:
        if (obj->dead == 0) {
            func_8002E260(obj, (func_8008AE30(obj->x - ((Hit3 *)data)->x, obj->z - ((Hit3 *)data)->z) & 0xFFF) << 4, 1);
        }
        break;
    }
}
