typedef struct { char pad[32]; int x; int y; int z; } Target;
typedef struct { int pad[2]; Target *target; int pad2[3]; unsigned char busy; } Obj;
typedef struct { unsigned char valid; char pad[3]; int x; int z; } Query;
void func_8002D128(Obj *, int, int *, Query *);
void func_8002D378(Obj *, int, int *, Query *);
void func_8002D4A4(Obj *, int, int *);

void func_8002D5D0(Obj *obj, int arg, unsigned int event, int *data, Query *q) {
    switch (event) {
    case 0:
        func_8002D128(obj, arg, data, q);
        break;
    case 5:
        if (*data == 0 && obj->busy == 0) {
            q->valid = 1;
            q->x = obj->target->x;
            q->z = obj->target->z;
        }
        break;
    case 6:
        func_8002D378(obj, arg, data, q);
        break;
    case 3:
        func_8002D4A4(obj, arg, data);
        break;
    }
}
