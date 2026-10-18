typedef struct Msg {
    int pad[2];
    unsigned char ***data;
} Msg;

extern unsigned short D_800E4994;
extern unsigned short D_800AACDE;
extern int D_800A8B18;
extern void func_80057CF0(void *, int);

int func_80060C64(int unused, Msg *msg) {
    if (D_800E4994 == 0) {
        if (D_800AACDE >= 10) {
            return 0;
        }
        func_80057CF0(&D_800A8B18, ***msg->data);
        D_800AACDE++;
    }
    return 0;
}
