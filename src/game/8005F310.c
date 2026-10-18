extern unsigned int D_800A6074;
extern int D_800EAF5C;
extern int D_800EAF60;
extern int D_800EAF64;

typedef struct Holder {
    int pad[2];
    int *target;
} Holder;

typedef struct Page {
    char pad[0x20];
    Holder holder;
} Page;

static inline void select_mode_slot(Holder *holder) {
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

int func_8005F310(int unused, Page *page) {
    D_800A6074++;
    if (D_800A6074 >= 4) {
        D_800A6074 = 1;
    }
    select_mode_slot(&page->holder);
    return 0;
}
