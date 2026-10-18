typedef struct { char pad[32]; int hp; int pad2; unsigned char dead; } Obj;
typedef struct { int pad; unsigned short type; } Msg;
typedef struct { int pad[4]; int amount; } MsgData;
void func_8002E260(Obj *, int, int);

void func_8002E69C(Obj *obj, Msg *msg, MsgData *data, int *result) {
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
