typedef struct {
    unsigned char pad0[0x20];
    int v20;
    unsigned char pad24[0x8];
    int v2C;
    unsigned char pad30[0x5];
    unsigned char v35;
    unsigned char v36;
} Obj;
void func_8009F404(Obj *p)
{
    p->v36 = 77;
    p->v35 = 6;
    p->v2C = p->v20;
}
