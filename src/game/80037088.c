typedef struct { unsigned char flag; char pad[3]; int x; int z; } Reply;
typedef struct { char pad[8]; int x; int y; int z; char pad2[8]; int started; int start_time; } Obj;
extern unsigned int func_80086C84(void);
extern int D_800D2FE0;

void func_80037088(Obj *obj, int unused, int msg, int *arg, Reply *reply)
{
    switch (msg) {
    case 5:
        if (*arg == 0) {
            reply->flag = 1;
            reply->x = obj->x;
            reply->z = obj->z;
        }
        break;
    case 6:
        if (obj->started == 0) {
            obj->started = 1;
            obj->start_time = D_800D2FE0 - func_80086C84() % 60;
        }
        break;
    }
}
