typedef struct {
    int state;
    int unk4;
    int unk8;
    int unkC;
    int handle;
    int buf;
    int size;
    int port;
} CardState;

extern CardState D_800EF094;
extern char D_800C52E8[];
extern char D_800C5218[];
extern char D_800C530C[];
void func_800943B0(const char *, ...);
void func_8009F5AC(int (*)(int *));
int func_80095538(int *);

int func_80095494(int port, int buf, int size)
{
    char *msg;

    if (D_800EF094.handle < 0) {
        msg = D_800C52E8;
    } else if (D_800EF094.state != 0) {
        msg = D_800C5218;
    } else if ((size & 0x7F) == 0) {
        D_800EF094.state = 5;
        D_800EF094.unk4 = 0;
        D_800EF094.unk8 = 0;
        D_800EF094.buf = buf;
        D_800EF094.port = port;
        D_800EF094.size = size;
        func_8009F5AC(func_80095538);
        return 1;
    } else {
        msg = D_800C530C;
    }
    func_800943B0(msg);
    return 0;
}
