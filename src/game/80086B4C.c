extern int func_80086A70(int a);
extern int func_80086AB4(int a, int b);
extern void func_80086B00(int a);
extern int func_80086B34(void);

int func_80086B4C(int cmd, int first, ...) {
    int result = 0;
    int a;

    switch ((unsigned int)cmd) {
    case 0:
        result = func_80086A70((&first)[1]);
        break;
    case 1:
        result = func_80086AB4((&first)[1], ((int *)__builtin_next_arg(first))[1]);
        break;
    case 2:
        func_80086B00((&first)[1]);
        break;
    case 3:
        result = func_80086B34();
        break;
    }
    return result;
}
