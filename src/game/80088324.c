typedef struct CardState {
    int mode;
    volatile unsigned char active;
    char pad05[0x27];
    int channel;
    int port;
    unsigned int limit;
    unsigned int used;
    char pad3C[0x94];
    unsigned int done;
} CardState;

extern CardState D_800EE588;
extern int func_80086D3C(int, int);
extern void func_800871E0(void);
extern int func_80086FC4(int);
extern int func_80087268(int);
extern int func_80087830(int, int);
extern int func_80087950(int, int);
extern int func_80087460(int);
extern int func_8008775C(int, int);
extern int func_80088094(int, int, int, int);
extern int func_80087D4C(int, int, int, int);
extern int func_8008756C(int, int);
extern int func_80087664(void);
extern void func_8008DA04(char *, int);

int func_80088324(int cmd, ...) {
    int result = 0;
    char *ap = (char *)&cmd + 4;
    int *out;
    char *name;
    int n;

    switch ((unsigned int)cmd) {
    case 0:
        result = 0;
        D_800EE588.mode = *(int *)ap;
        break;
    case 1:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            int *zero_out = *(int **)ap;
            result = func_80086D3C(a, b);
            if (zero_out != 0) {
                *zero_out = 0;
            }
        }
        break;
    case 2:
        {
            int a = *(int *)ap;
            if (D_800EE588.active) {
                func_800871E0();
            }
            result = func_80086FC4(a);
        }
        break;
    case 3:
        result = func_80087268(*(int *)ap);
        break;
    case 5:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            out = ((int **)ap)[1];
            n = func_80087830(a, b);
        }
        goto size_out;
    case 6:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            out = *(int **)ap;
            n = func_80087950(a, b);
        }
    size_out:
        if (n != 0 && out != 0) {
            *out = D_800EE588.limit - D_800EE588.used;
        }
        result = n;
        break;
    case 7:
        result = func_80087460(*(int *)ap);
        break;
    case 8:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            result = func_8008775C(a, *(int *)ap);
        }
        break;
    case 4:
    case 9:
        result = 0;
        break;
    case 10:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b;
            int c;
            int d;
            ap += 4;
            b = (ap += 4, *(int *)(ap - 4));
            c = (ap += 4, *(int *)(ap - 4));
            d = (ap += 4, *(int *)(ap - 4));
            result = func_80088094(a, b, c, d);
        }
        break;
    case 11:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b;
            int c;
            int d;
            ap += 4;
            b = (ap += 4, *(int *)(ap - 4));
            c = (ap += 4, *(int *)(ap - 4));
            d = (ap += 4, *(int *)(ap - 4));
            result = func_80087D4C(a, b, c, d);
        }
        break;
    case 12:
        {
        int a = (ap += 4, *(int *)(ap - 4));
        int b = *(int *)ap;
        result = 1;
        if (D_800EE588.port == a) {
            if (b != 0) {
                while (D_800EE588.active) {
                }
            }
            result = D_800EE588.active == 0;
        }
        }
        break;
    case 13:
        {
            int port = *(int *)ap;
            if (D_800EE588.port == port) {
                func_800871E0();
            }
        }
        break;
    case 14:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            int len;
            name = *(char **)ap;
            len = func_8008756C(a, b);
            if (len != 0) {
                func_8008DA04(name, len);
                result = 1;
            } else {
                *name = 0;
            }
        }
        break;
    case 15:
        {
            int len;
            name = *(char **)ap;
            len = func_80087664();
            if (len != 0) {
                func_8008DA04(name, len);
                result = 1;
            } else {
                *name = 0;
            }
        }
        break;
    case 16:
        {
            int port = *(int *)ap;
            result = 0;
            if (D_800EE588.port == port) {
                result = D_800EE588.done;
            }
        }
        break;
    }
    return result;
}
