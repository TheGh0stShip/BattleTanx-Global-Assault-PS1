typedef struct {
    volatile int a;
    volatile int b;
    volatile int busy;
    int pad[13];
    void (*callback)(int, int);
} CardState;
typedef struct { int a; int b; } CardResult;
extern CardState D_800EF094;
extern volatile CardResult D_800EF0DC;

int func_8009601C(int mode, int *out_a, int *out_b)
{
    CardState *s;
    int a;
    int b;
    volatile int *p;
    CardState *t;

    s = &D_800EF094;
    __asm__("" : "=r"(s) : "0"(s));

    if (s->a == 0 && s->busy == 0) {
        return -1;
    }
    a = s->a;
    b = s->b;
    if (mode == 0) {
        if (s->busy == 0) {
            p = &s->busy;
            do {
            } while (*p == 0);
        }
        if (out_b != 0) {
            *out_b = D_800EF0DC.b;
        }
        if (out_a != 0) {
            *out_a = D_800EF0DC.a;
        }
        t = &D_800EF094;
        __asm__("" : "=r"(t) : "0"(t));
        t->busy = 0;
        return 1;
    }
    if (s->busy == 0) {
        if (out_b != 0) {
            *out_b = b;
        }
        if (out_a != 0) {
            *out_a = a;
        }
        return 0;
    }
    if (out_b != 0) {
        *out_b = D_800EF0DC.b;
    }
    if (out_a != 0) {
        *out_a = D_800EF0DC.a;
    }
    s->busy = 0;
    return 1;
}
