typedef struct { short f0; short f2; short kind; } Hit;
typedef struct { int f0; int f4; int f8; int damage; unsigned short f10; short f12; int f14; } HitData;
typedef union { int code; struct { unsigned char flag; char pad[3]; int x; int z; } pos; } Reply;
typedef struct {
    char pad[0xC];
    int x;
    int f10;
    int z;
    char pad2[0x1A - 0x18];
    unsigned short sound;
    char pad3[0x20 - 0x1C];
    unsigned char destroyed;
    char pad4[3];
    int health;
} Target;
extern void func_8001B094(int);
extern void func_80022CAC(Target *);
extern int func_80024114(int, int);

void func_800378E8(Target *obj_arg, Hit *hit, unsigned int msg, HitData *data, Reply *reply)
{
    int d;
    Target *obj = obj_arg;

    switch (msg) {
    case 0:
        switch (hit->kind) {
        case 7:
        case 12:
        case 39:
        case 40:
        case 52:
            if (obj->destroyed) {
                reply->code = 2;
            } else {
                obj->health -= data->f10;
                reply->code = 1;
            }
            break;
        case 4:
            obj->health -= 30000;
            reply->code = 9;
            break;
        default:
            reply->code = 1;
            break;
        }
        break;
    case 2:
        func_8001B094(obj->sound);
        func_80022CAC(obj);
        break;
    case 5:
        if (*(int *)data == 0 && !obj->destroyed && obj->health != 0) {
            reply->pos.flag = 1;
            reply->pos.x = obj->x;
            reply->pos.z = obj->z;
        }
        break;
    case 6:
        if (!obj->destroyed && obj->health != 0) {
            d = func_80024114(data->f14, data->f8);
            if (d > 0) {
                obj->health -= d;
            }
        }
        break;
    case 3:
        if (obj->health != 0) {
            obj->health -= data->damage;
        }
        break;
    }
}
