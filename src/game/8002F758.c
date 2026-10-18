typedef struct { int x, y, z; } Vector;
typedef struct { char pad[60]; int value; } Target;
typedef struct { int pad[2]; Vector pos; int pad2[2]; int a; int b; int value; int pad3; Target *target; int pad4; unsigned char count; unsigned char state; } Linker;
void func_80027DE0(int, int, int, Target *, Vector *);

void func_8002F758(Linker *l) {
    if (l->state == 4) {
        l->target->value = l->value;
        func_80027DE0(l->a, l->b, (l->count << 12) / 15, l->target, &l->pos);
    }
}
