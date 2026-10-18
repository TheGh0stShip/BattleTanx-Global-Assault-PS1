extern unsigned int D_800A6070;
extern int D_800EAC3C;
extern int D_800EADC0;
extern int D_800EAE88;
extern int D_800EAEE8;
extern int D_800EAEF4;
extern int D_800EAEFC;
extern int D_800EAF04;
extern int D_800EAF40;

typedef struct Holder {
    int pad[2];
    int *target;
} Holder;

void func_800611D4(Holder *holder) {
    switch (D_800A6070) {
    case 5:
        holder->target = &D_800EAE88;
        break;
    case 6:
        holder->target = &D_800EAF40;
        break;
    case 4:
        holder->target = &D_800EADC0;
        break;
    case 3:
        holder->target = &D_800EAEFC;
        break;
    case 7:
        holder->target = &D_800EAF04;
        break;
    case 8:
        holder->target = &D_800EAEF4;
        break;
    case 2:
        holder->target = &D_800EAEE8;
        break;
    case 1:
    default:
        holder->target = &D_800EAC3C;
        break;
    }
}
