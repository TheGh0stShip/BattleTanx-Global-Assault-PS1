typedef struct { int x; int y; int z; } Vector;
typedef struct { int f0; int a; int b; } Spec;
extern char *func_800237D0(int, int);
extern void func_80026340(int, int, void *, int);
extern void func_800162F0(void *, short, short, int, int, int, int, int, int, int, int, int);

static inline int to_int(int v)
{
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

void func_80037380(Spec *spec, int owner, Vector *pos)
{
    char *obj;

    obj = func_800237D0(18, 56);
    if (obj != 0) {
        func_80026340(owner, spec->a, obj + 8, 1);
        func_80026340(owner, spec->b, obj + 20, 3);
        func_800162F0(obj, to_int(pos->x) >> 2, to_int(pos->z) >> 2, 0, -60, 60, -60, 60, 0, 300, 0, 8192);
    }
}
