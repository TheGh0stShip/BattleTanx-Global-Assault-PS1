typedef struct Entry {
    unsigned char kind;
    unsigned char flag;
    char pad[6];
    int *value;
    char pad2[0x14];
} Entry;

extern signed char D_800A606C;
extern Entry *D_800AA20C;
extern Entry *D_800AA97C;
extern int D_800E4A60;
extern unsigned int D_800A6084;
extern unsigned int D_800A6088;
extern unsigned int D_800A608C;
extern unsigned int D_800A6090;

static inline void set_team_flag(Entry *entry, unsigned int team) {
    switch (team) {
    case 1:
        entry->flag = team;
        break;
    case 2:
        entry->flag = team;
        break;
    case 3:
        entry->flag = team;
        break;
    case 4:
        entry->flag = team;
        break;
    default:
        entry->flag = 16;
        break;
    }
}

void func_8005D494(void) {
    Entry *entry;

    if (D_800A606C == 1) {
        entry = D_800AA20C;
    } else {
        entry = D_800AA97C;
    }
    for (; entry->kind != 0; entry++) {
        if (entry->value == &D_800E4A60) {
            break;
        }
    }
    set_team_flag(&entry[0], D_800A6084);
    set_team_flag(&entry[1], D_800A6088);
    set_team_flag(&entry[2], D_800A608C);
    set_team_flag(&entry[3], D_800A6090);
}
