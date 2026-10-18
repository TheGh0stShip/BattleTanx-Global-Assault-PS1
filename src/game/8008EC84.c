extern void func_8008EC40(void);
extern void func_80099738(void *, int, int, int, int, void *);
extern void func_8008E860(void);

typedef struct {
    int flags;
    int arg;
    char pad[8];
    char body[1];
} S8008EC84;
extern S8008EC84 D_800EEC34;

void func_8008EC84(int a0, int a1, int a2, int a3, int a4) {
    func_8008EC40();
    D_800EEC34.arg = a4;
    func_80099738(D_800EEC34.body, a0, a1, a2, a3, func_8008E860);
}
