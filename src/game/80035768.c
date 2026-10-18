typedef struct { char pad[60]; int value; } Target;
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

void func_80035768(Obj *obj, Msg *msg, MsgData *data, int *result) {
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
                goto destroy;
            }
            if (v < 125 && obj->value != 0) {
                obj->target->value = obj->value;
            }
            break;
        }
        goto check;
    case 4:
        state = obj->state;
        if (state == 2 || state == 3) {
            *result = 1;
            break;
        }
        if (state == 6) {
            *result = 1;
            break;
        }
        *result = 9;
    check:
        if (obj->locked != 0) {
            break;
        }
    destroy:
        func_80035238(obj, data->source);
        break;
    case 30:
    case 75:
        *result = 1;
        break;
    }
}
