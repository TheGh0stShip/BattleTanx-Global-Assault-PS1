extern void func_8009F51C(unsigned char *p, int a);
extern void func_8009F53C(unsigned char *p, int a);
extern void func_8009F55C(unsigned char *p, int a);
extern void func_8009F57C(unsigned char *p);

void func_8009F080(unsigned char *p) {
    switch (p[70]) {
    case 2:
        func_8009F51C(p, p[71]);
        break;
    case 3:
        func_8009F53C(p, p[71]);
        break;
    case 4:
        if (p[72] == 0) {
            func_8009F55C(p, p[71]);
        } else {
            func_8009F57C(p);
        }
        break;
    }
}
