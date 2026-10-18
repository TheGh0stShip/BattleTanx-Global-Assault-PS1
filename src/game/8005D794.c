typedef struct Holder {
    int pad[2];
    int *target;
} Holder;

typedef struct Menu {
    int pad;
    unsigned char *base;
} Menu;

extern unsigned int D_800A6084[];
extern unsigned int D_800A6094[];
extern int D_800EADD0;
extern int D_800EAE1C;
extern int D_800EAE2C;
extern int D_800EAE40;
extern int D_800EAE44;
extern int D_800EAE48;
extern int D_800EAF64;
extern int D_800EADE0;
extern int D_800EAE24;
extern signed char D_800A606C;

static inline void select_index_style(Holder *holder, unsigned int index) {
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

static inline void update_player_rows(unsigned char *base, unsigned short player) {
    Holder *holder;

    if (D_800A6084[player] == 0) {
        base[0x40] = 1;
        base[0x60] = 1;
        base[0x41] = 1;
        base[0x61] = 1;
    } else {
        base[0x40] = 4;
        base[0x60] = 4;
        base[0x41] = 16;
        base[0x61] = 16;
    }
    holder = (Holder *)(base + 0x60);
    switch (D_800A6094[player]) {
    case 2:
        holder->target = &D_800EAF64;
        break;
    case 1:
        holder->target = &D_800EAE24;
        break;
    case 3:
        holder->target = &D_800EADE0;
        break;
    default:
        holder->target = &D_800EAF64;
        break;
    }
    select_index_style((Holder *)(base + 0x20), D_800A6084[player]);
}

void func_8005D794(Menu *menu, unsigned short player) {
    unsigned char *base;

    base = menu->base;
    if (D_800A606C == 1) {
        update_player_rows(base, player);
    } else {
        update_player_rows(base, player);
    }
}
