extern void func_8008F628(void);
extern void func_8008AA48(void *, int, int);
extern int func_80099DEC(int, int, int);
extern void func_8009A04C(void *);
extern void func_8008F7A0(void);
extern void func_8008F410(int);
extern void func_8008F368(int);

typedef struct {
    char pad0[8];
    int baud;
    int flags;
    char pad16[4];
    int low_water;
    char pad24[4];
    void *ring;
    int size;
    char pad36[32];
} S8008F824;
extern S8008F824 D_800EEDF4;

void func_8008F824(void) {
    if (D_800EEDF4.flags & 4) {
        func_8008F628();
    }
}

void func_8008F854(void) {
    S8008F824 *s = &D_800EEDF4;

    func_8008AA48(s, 0, 68);
    s->size = 518;
    s->low_water = 389;
    func_80099DEC(2, 0, 0);
    func_80099DEC(1, 1, 7);
    func_80099DEC(1, 2, 76);
    func_80099DEC(1, 3, 115200);
    s->baud = 115200;
    func_8009A04C(func_8008F7A0);
    func_80099DEC(1, 1, 23);
    func_8008F410(1);
    func_8008F368(1);
}

int func_8008F914(void *(*alloc)(int, int, int), int arg) {
    S8008F824 *s = &D_800EEDF4;
    int r = 0;

    if (s->ring == 0 && s->size != 0) {
        s->ring = alloc(r, arg, s->size);
        r = -1;
        if (s->ring != 0) {
            r = s->size;
        }
    }
    return r;
}
