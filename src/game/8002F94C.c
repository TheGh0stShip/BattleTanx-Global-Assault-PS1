typedef struct { char pad[22]; signed char value; } Obj;
typedef struct { int pad; unsigned short type; } Msg;
typedef struct { int pad[4]; int amount; } MsgData;

void func_8002F94C(Obj *obj, Msg *msg, MsgData *data, int *handled) {
    int v;

    switch ((short)msg->type) {
    case 7:
    case 12:
    case 39:
    case 40:
    case 52:
        v = obj->value - data->amount;
        if (v <= 0) {
            obj->value = 0;
        } else {
            obj->value = v;
        }
    case 4:
    case 30:
    case 75:
        *handled = 1;
        break;
    }
}
