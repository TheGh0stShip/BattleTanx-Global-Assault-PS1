typedef struct { char pad[52]; int value; } Obj;
typedef struct { int pad; unsigned short type; } Msg;
typedef struct { int pad[4]; int amount; } MsgData;

void func_80031528(Obj *obj, Msg *msg, MsgData *data, int *handled) {
    int v;

    switch ((short)msg->type) {
    case 7:
    case 12:
    case 39:
    case 40:
    case 52:
        if (obj->value > 0) {
            v = obj->value - data->amount;
            obj->value = v;
            if (v < 0) {
                obj->value = 0;
            }
        }
    case 30:
    case 75:
        *handled = 1;
        break;
    case 4:
        break;
    }
}
