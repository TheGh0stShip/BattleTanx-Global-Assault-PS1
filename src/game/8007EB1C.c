typedef struct FileCtl {
    int handle;
    char pad4[276];
    int (*retry)(int);
} FileCtl;

extern FileCtl D_800EC200;
extern unsigned int D_800EC330;
extern int func_800941A8(int, char *, unsigned int);
extern unsigned int func_800942B4(int, unsigned int, int);

int func_8007EB1C(int handle, char *buf, unsigned int len) {
    register char *data asm("$22") = buf;
    unsigned int done = 0;
    unsigned int size = -1;
    int fd = handle + size;
    unsigned int pos;
    int again;

    do {
        again = 0;
        done += func_800941A8(fd, data + done, len - done);
        if (done != len) {
            pos = func_800942B4(fd, again, 1);
            if (size == -1) {
                size = func_800942B4(fd, again, 2);
                func_800942B4(fd, pos, again);
            }
            if (pos < size) {
                again = 1;
                if (D_800EC200.retry != 0) {
                    again = D_800EC200.retry(again);
                }
            }
        }
    } while (again);
    D_800EC330 = done;
    return done == len;
}
