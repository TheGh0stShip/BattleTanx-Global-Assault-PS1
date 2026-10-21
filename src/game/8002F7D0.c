typedef struct {
    int pad[2];
    int x;
    int pad2;
    int z;
    short pad3;
    signed char hp;
    char pad4[53 - 23];
    unsigned char state;
    char pad5;
    unsigned char team;
} Obj;
typedef struct { int pad; unsigned short type; } Msg;
typedef struct { int pad[3]; int drain; int amount; } MsgData;
typedef struct { unsigned char valid; char pad[3]; int x; int z; } Query;
extern unsigned char D_800D5A88;
void func_8002F3D8(Obj *, Msg *, MsgData *);

static inline void handle_msg(Obj *obj, Msg *msg, MsgData *data, int *handled) {
    int v;

    switch ((short)msg->type) {
    case 7:
    case 12:
    case 39:
    case 40:
    case 52:
        v = obj->hp - data->amount;
        if (v <= 0) {
            obj->hp = 0;
        } else {
            obj->hp = v;
        }
        *handled = 1;
        break;
    case 4:
    case 30:
    case 75:
        *handled = 1;
        break;
    }
}

void func_8002F7D0(Obj *obj, Msg *msg, unsigned int event, MsgData *data, Query *out) {
    register MsgData *d asm("$9") = data;
    register Obj *self asm("$8") = obj;

    __asm__("" : "+r"(d));
    switch (event) {
    case 0:
        handle_msg(self, msg, d, (int *)out);
        break;
    case 5:
        if (*(int *)d == 0) {
            if (obj->team == 1 && D_800D5A88 == 97) {
                break;
            }
            switch (obj->state) {
            case 0:
            case 1:
            case 2:
            case 3:
                out->valid = 1;
                out->x = obj->x;
                out->z = obj->z;
                break;
            }
        }
        break;
    case 6:
        func_8002F3D8(obj, msg, d);
        break;
    case 3:
        if (obj->hp < d->drain) {
            obj->hp = 0;
        } else {
            obj->hp -= d->drain;
        }
        break;
    }
}
