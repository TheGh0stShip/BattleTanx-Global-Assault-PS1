typedef struct { int pad[3]; int x; int y; int z; } Obj;
int func_80022814(Obj *);
void func_80061CC0(int, int, int, int, int);

static inline int to_int(int v) {
    if (v >= 0) {
        return v >> 12;
    }
    return -(-v >> 12);
}

void func_80034410(Obj *o) {
    if (func_80022814(o) != 0) {
        int x = (short)to_int(o->x);
        register int z asm("$4") = to_int(o->z);
        __asm__("" : "=r"(z) : "0"(z));
        func_80061CC0(x, (short)z, 0, 1, 28);
    }
}
