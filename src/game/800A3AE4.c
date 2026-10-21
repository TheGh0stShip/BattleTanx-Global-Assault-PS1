extern int (*D_800B8C8C)(void);
extern int D_800BD45C;
void func_8009E8D0(int a, int b);

void func_800A3AE4(int a)
{
    D_800BD45C = D_800B8C8C();
    func_8009E8D0(a, -2);
}
