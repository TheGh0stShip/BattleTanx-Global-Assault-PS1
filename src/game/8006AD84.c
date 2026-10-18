extern int func_80093D5C(void);
extern void func_80093B7C(int index, int value, void (*callback)(void *));

void func_8006AD84(void *context) {
    if (context != 0) {
        func_80093B7C(func_80093D5C(), 0, func_8006AD84);
    }
}
