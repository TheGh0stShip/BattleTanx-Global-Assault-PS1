typedef struct {
    int busy;
    int unk4;
    int unk8;
    int channel;
} CardState;
extern volatile int D_800EF090;
extern CardState D_800EF094;

extern char D_800C5368[];
void func_800943B0(const char *, ...);
void func_80096714(int, char *);
void func_80096AF0(void);
void func_8009F78C(char *);
int func_80096CD0(void);
int func_8009663C(int);
void func_8009F79C(void);
void func_8009F7AC(int, int, signed char *);

int func_800964FC(int port)
{
    char name[64];

    CardState *card;

    card = &D_800EF094;
    __asm__ volatile("" : "=r"(card) : "0"(card));

    if (card->busy != 0) {
        func_800943B0(D_800C5368);
        return -1;
    }
    D_800EF090 |= 1 << card->channel;
    func_80096714(port, name);
    func_80096AF0();
    func_8009F78C(name);
    return func_8009663C(func_80096CD0());
}

int func_80096588(int port)
{
    signed char buf[128];
    int i;
    signed char c;
    CardState *card;

    card = &D_800EF094;
    __asm__("" : "=r"(card) : "0"(card));
    if (card->busy != 0) {
        func_800943B0(D_800C5368);
        return -1;
    }
    c = -1;
    for (i = 127; i >= 0; i--) {
        buf[i] = c;
    }
    for (i = 0; i < 15; i++) {
        func_80096AF0();
        func_8009F79C();
        func_8009F7AC(port, i, buf);
        if (func_80096CD0() != 0) {
            return 0;
        }
    }
    return 1;
}
