extern int func_80099684(void *, int);

typedef struct {
    int flags;
    char pad[12];
    char body[1];
} S8008EB9C;
extern S8008EB9C D_800EEC34;

int func_8008EB9C(int wait) {
    int done;

    do {
        if (D_800EEC34.flags & 0x10) {
            done = func_80099684(D_800EEC34.body, 0);
        } else {
            done = 1;
        }
    } while (done == 0 && wait != 0);
    return done;
}
