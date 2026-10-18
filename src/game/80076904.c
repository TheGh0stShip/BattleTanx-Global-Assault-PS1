typedef struct Entry {
    void *value;
    void *(*getter)(int, int);
    unsigned int kind;
    char name[16];
    int step;
    struct Entry *next;
} Entry;

typedef struct Choice {
    unsigned char *selected;
    void *options[1];
} Choice;

extern int D_800AEA48;
extern Entry *D_800EAFE4;
extern Entry *D_800EAFE8;

void func_80076904(int dir) {
    Entry *entry;
    Choice *choice;
    unsigned char *sel;
    unsigned char value;
    int index;
    void *option;

    if (D_800AEA48 == 0) {
        return;
    }
    entry = D_800EAFE8;
    switch (entry->kind) {
    case 10:
    case 11:
    case 12:
        entry->value = entry->getter(0, dir * entry->step);
        break;
    case 13:
        choice = entry->value;
        sel = choice->selected;
        value = *sel + dir * entry->step;
        index = (signed char)value;
        option = ((void **)choice)[index + 1];
        if ((index >= 0 && option != 0) || index == -1) {
            *sel = value;
        }
        break;
    case 0:
    case 3:
    case 4:
        *(int *)entry->value += dir * entry->step;
        break;
    case 5:
    case 6:
        *(unsigned short *)entry->value += dir * entry->step;
        break;
    case 7:
    case 8:
        *(unsigned char *)entry->value += dir * entry->step;
        break;
    case 14:
        if (dir == 1) {
            D_800EAFE8 = D_800EAFE4 = entry->value;
        }
        break;
    case 15:
        if (dir == -1) {
            D_800EAFE8 = D_800EAFE4 = entry->value;
        }
        break;
    case 1:
    case 2:
    case 9:
        break;
    }
}
