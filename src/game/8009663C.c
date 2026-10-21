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
int func_8009F694(void);
void func_8009F628(void);

int func_8009663C(int code)
{
    int r = 0;

    switch (code) {
    case 0:
        break;
    case 2:
        r = 1;
        break;
    default:
        r = code | 0x8000;
        break;
    case 4:
        r = 3;
        break;
    case 1:
        r = 2;
        break;
    }
    return r;
}

void func_80096690(void)
{
    CardState *s;
    volatile CardResult *d;
    void (*cb)(int, int);

    if (func_8009F694() == 0) {
        func_8009F628();
        if (func_8009F694() != 0) {
            s = &D_800EF094;
            s->busy = 1;
            d = &D_800EF0DC;
            d->a = s->a;
            d->b = s->b;
            cb = s->callback;
            s->a = 0;
            s->b = 0;
            if (cb != 0) {
                cb(d->a, d->b);
            }
        }
    }
}
