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
    char *options[1];
} Choice;

typedef struct Line {
    char label[16];
    char value[15];
} Line;

typedef struct Font {
    char data[16392];
} Font;

extern int D_800AEA48;
extern int D_800A48B4;
extern Entry *D_800EAFE4;
extern Entry *D_800EAFE8;
extern Line D_800EAFF4[];
extern Font D_800D5B94[];
extern void func_8008AC90(void *, int);
extern char *func_80094044(char *, char *, int);
extern int func_8008AFB0(char *, char *, ...);
extern void func_80092350(Font *, int, int, int, int, char *, ...);

static inline int int_part(int v) {
    if (v < 0) {
        return -(-v >> 12);
    }
    return v >> 12;
}

void func_80076524(void) {
    Entry *entry;
    Entry *first;
    Line *line;
    Choice *choice;
    int *ip;
    int count;
    int j;
    short x;
    int index;
    unsigned char *sel;
    unsigned char value;
    char *option;
    int i;
    short y;
    char text[15];

    if (D_800AEA48 == 0) {
        return;
    }
    func_8008AC90(D_800EAFF4, 434);
    i = 0;
    first = D_800EAFE8;
    entry = first;
    do {
        switch (entry->kind) {
        case 9:
        case 10:
            func_80094044(text, entry->value, 15);
            text[14] = 0;
            func_8008AFB0(D_800EAFF4[i].label, "%s", entry->name);
            func_8008AFB0(D_800EAFF4[i].value, "%s", text);
            break;
        case 13:
            choice = entry->value;
            sel = choice->selected;
            index = (signed char)*sel;
            value = *sel;
            option = ((char **)choice)[index + 1];
            if (index >= 0 && option != 0) {
                func_80094044(text, option, 15);
                text[14] = 0;
            } else {
                func_8008AFB0(text, "%d", (signed char)value);
            }
            func_8008AFB0(D_800EAFF4[i].label, "%s", entry->name);
            func_8008AFB0(D_800EAFF4[i].value, "%s", text);
            break;
        case 0:
        case 11:
            ip = entry->value;
            func_8008AFB0(D_800EAFF4[i].label, "%s", entry->name);
            func_8008AFB0(D_800EAFF4[i].value, "%d.%d", int_part(*ip), *ip & 0xFFF);
            break;
        case 1:
            func_8008AFB0(D_800EAFF4[i].label, "%s", "u64 is not supported.");
            break;
        case 2:
            func_8008AFB0(D_800EAFF4[i].label, "%s", "s64 is not supported.");
            break;
        case 3:
            ip = entry->value;
            func_8008AFB0(D_800EAFF4[i].label, "%s", entry->name);
            func_8008AFB0(D_800EAFF4[i].value, "%d", *ip);
            break;
        case 4:
            ip = entry->value;
            func_8008AFB0(D_800EAFF4[i].label, "%s", entry->name);
            func_8008AFB0(D_800EAFF4[i].value, "%d", *(unsigned int *)ip);
            break;
        case 5:
        case 12:
            ip = entry->value;
            func_8008AFB0(D_800EAFF4[i].label, "%s", entry->name);
            func_8008AFB0(D_800EAFF4[i].value, "%d", *(unsigned short *)ip);
            break;
        case 6:
            ip = entry->value;
            func_8008AFB0(D_800EAFF4[i].label, "%s", entry->name);
            func_8008AFB0(D_800EAFF4[i].value, "%d", *(short *)ip);
            break;
        case 7:
            ip = entry->value;
            func_8008AFB0(D_800EAFF4[i].label, "%s", entry->name);
            func_8008AFB0(D_800EAFF4[i].value, "%d", *(unsigned char *)ip);
            break;
        case 8:
            ip = entry->value;
            func_8008AFB0(D_800EAFF4[i].label, "%s", entry->name);
            func_8008AFB0(D_800EAFF4[i].value, "%d", *(signed char *)ip);
            break;
        case 14:
            func_8008AFB0(D_800EAFF4[i].label, "    %s", entry->name);
            break;
        case 15:
            func_8008AFB0(D_800EAFF4[i].label, "    BACK");
            break;
        }
        if (D_800EAFF4[i].value[0] == '-') {
            D_800EAFF4[i].value[0] = 'N';
        }
        i++;
        entry = entry->next;
        if (entry == 0) {
            entry = D_800EAFE4;
        }
    } while (i < D_800AEA48 && entry != first);
    count = D_800AEA48;
    line = D_800EAFF4;
    x = 25;
    for (j = 0, y = 140; j < count; y += 9, j++) {
        func_80092350(&D_800D5B94[D_800A48B4], x, y, 0x64FF64, 0, "%s", &line[j]);
    }
}
