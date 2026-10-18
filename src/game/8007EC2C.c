typedef struct Pending {
    int handle;
    char pad4[264];
    int active;
    void (*callback)(int, int);
    void (*callback4)(int, int, int, int);
    int pad118;
    int arg;
    char pad120[8];
    int busy;
} Pending;

extern Pending D_800EC200;

void func_8007EC2C(void) {
    Pending *p = &D_800EC200;
    void (*cb)(int, int) = p->callback;
    void (*cb4)(int, int, int, int) = p->callback4;
    int active = p->active;

    p->callback = 0;
    p->callback4 = 0;
    p->active = 0;
    p->busy = 0;
    if (active != 0) {
        if (cb != 0) {
            cb(D_800EC200.handle, 0);
        } else if (cb4 != 0) {
            cb4(D_800EC200.handle, p->arg, 0, 0);
        }
    }
}
