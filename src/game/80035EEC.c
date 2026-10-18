typedef struct { char pad[44]; int hp; } Obj;
typedef struct { int pad; short type; } Msg;
typedef struct { int pad[4]; int amount; int source; } MsgData;
void func_800530E0(int, int, int);

void func_80035EEC(Obj *obj, Msg *msg, int sender, MsgData *data, int *handled) {
    int v;

    if (sender == 0) {
        switch (msg->type) {
        case 12:
        case 39:
        case 40:
        case 52:
            if (obj->hp > 0) {
                v = obj->hp - data->amount;
                obj->hp = v;
                if (v <= 0) {
                    func_800530E0(data->source, 2000, 0);
                }
            }
            *handled = 1;
            break;
        }
    }
}
