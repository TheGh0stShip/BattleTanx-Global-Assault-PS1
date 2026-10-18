extern unsigned int D_800A6074;
extern int D_800EAF5C;
extern int D_800EAF60;
extern int D_800EAF64;

typedef struct Holder {
    int pad[2];
    int *target;
} Holder;

void func_8006128C(Holder *holder) {
    switch (D_800A6074) {
    case 2:
        holder->target = &D_800EAF64;
        break;
    case 1:
        holder->target = &D_800EAF5C;
        break;
    case 3:
        holder->target = &D_800EAF60;
        break;
    default:
        holder->target = &D_800EAF64;
        break;
    }
}
