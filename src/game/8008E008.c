typedef struct {
    volatile int flags;
    int handle;
    char pad8[64];
    void (*on_done)(int, int);
    void (*on_data)(int, int, int, int);
} S8008E008;
extern S8008E008 D_800EEBE0;

void func_8008E008(int a0, int a1, int a2, int a3) {
    S8008E008 *s = &D_800EEBE0;
    void (*done)(int, int);
    void (*data)(int, int, int, int);

    s->flags &= ~0x10;
    if ((done = s->on_done) != 0) {
        s->on_done = 0;
        done(s->handle, a3);
    }
    if ((data = s->on_data) != 0) {
        s->on_data = 0;
        data(s->handle, a1, a2, a3);
    }
}
