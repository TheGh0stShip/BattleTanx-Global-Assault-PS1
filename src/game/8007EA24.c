extern char D_800EC288[];
extern void func_8007E974(char *, char *);
extern int func_80094268(char *, int, int);
extern int func_800942B4(int, int, int);

int func_8007EA24(char *name, int mode, int *size) {
    int fd;

    func_8007E974(D_800EC288, name);
    fd = func_80094268(D_800EC288, mode, 0);
    if (fd != -1) {
        if (size != 0) {
            *size = func_800942B4(fd, 0, 2);
            func_800942B4(fd, 0, 0);
        }
        fd++;
    } else {
        fd = 0;
    }
    return fd;
}
