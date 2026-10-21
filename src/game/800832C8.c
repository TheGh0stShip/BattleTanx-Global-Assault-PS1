typedef struct Info {
    char pad00[0xC];
    int count;
    int size;
} Info;

extern int func_80082424(int, int);
extern int func_800825A4(int, int);
extern int func_800826A0(int);
extern int func_8008272C(int);
extern int func_80082798(int, int, int);
extern int func_80082854(int, int, int);
extern int func_80082984(int, int, int);
extern int func_80082BEC(int, int, int, int);
extern int func_80082DF4(int, int, int, int);
extern int func_80082FE0(int, int, int, int);
extern int func_8008314C(int, int);
extern void func_80083194(int);
extern int func_80082AA0(int, int, int);
extern int func_80082B20(int, int, int);
extern int func_8008323C(int);
extern int func_8008310C(int);

int func_800832C8(int cmd, ...) {
    int result = 0;
    char *ap = (char *)&cmd + 4;

    switch ((unsigned int)cmd) {
    case 0:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            result = func_80082424(a, b);
        }
        break;
    case 1:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            result = func_800825A4(a, b);
        }
        break;
    case 2:
        result = func_800826A0(*(int *)ap);
        break;
    case 3:
        result = func_8008272C(*(int *)ap);
        break;
    case 4:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            int c = (ap += 4, *(int *)(ap - 4));
            result = func_80082798(a, b, c);
        }
        break;
    case 5:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            int c = (ap += 4, *(int *)(ap - 4));
            result = func_80082854(a, b, c);
        }
        break;
    case 6:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            int c = (ap += 4, *(int *)(ap - 4));
            result = func_80082984(a, b, c);
        }
        break;
    case 7:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            int c = (ap += 4, *(int *)(ap - 4));
            int d = (ap += 4, *(int *)(ap - 4));
            result = func_80082BEC(a, b, c, d);
        }
        break;
    case 8:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            int c = (ap += 4, *(int *)(ap - 4));
            int d = (ap += 4, *(int *)(ap - 4));
            result = func_80082DF4(a, b, c, d);
        }
        break;
    case 9:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            int c = (ap += 4, *(int *)(ap - 4));
            int d = (ap += 4, *(int *)(ap - 4));
            result = func_80082FE0(a, b, c, d);
        }
        break;
    case 10:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            result = func_8008314C(a, b);
        }
        break;
    case 11:
        func_80083194(*(int *)ap);
        break;
    case 12:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            int c = (ap += 4, *(int *)(ap - 4));
            result = func_80082AA0(a, b, c);
        }
        break;
    case 13:
        {
            int a = (ap += 4, *(int *)(ap - 4));
            int b = (ap += 4, *(int *)(ap - 4));
            int c = (ap += 4, *(int *)(ap - 4));
            result = func_80082B20(a, b, c);
        }
        break;
    case 14:
        result = (*(Info **)ap)->count;
        break;
    case 15:
        result = func_8008323C(*(int *)ap);
        break;
    case 16:
        result = (*(Info **)ap)->size;
        break;
    case 17:
        result = func_8008310C(*(int *)ap);
        break;
    }
    return result;
}
