extern int D_800EADD0;
extern int D_800EAE2C;
extern int D_800EAE40;
extern int D_800EAE44;
extern int D_800EAE48;

typedef struct Holder {
    int pad[2];
    int *target;
} Holder;

void func_800612FC(Holder *holder, unsigned int index) {
    switch (index) {
    case 1:
        holder->target = &D_800EAE2C;
        break;
    case 2:
        holder->target = &D_800EAE48;
        break;
    case 3:
        holder->target = &D_800EAE40;
        break;
    case 4:
        holder->target = &D_800EAE44;
        break;
    case 0:
    default:
        holder->target = &D_800EADD0;
        break;
    }
}
