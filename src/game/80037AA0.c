typedef struct { char pad[32]; unsigned char shielded; char pad2[3]; int hp; } Obj;
typedef struct { int pad; unsigned short type; } Msg;
typedef struct { int pad[4]; unsigned short amount; } MsgData;

void func_80037AA0(Obj *obj, Msg *msg, MsgData *data, int *result) {
    switch ((short)msg->type) {
    case 7:
    case 12:
    case 39:
    case 40:
    case 52:
        if (obj->shielded != 0) {
            *result = 2;
            return;
        }
        obj->hp -= data->amount;
        *result = 1;
        return;
    case 4:
        obj->hp -= 30000;
        *result = 9;
        return;
    }
    *result = 1;
}
