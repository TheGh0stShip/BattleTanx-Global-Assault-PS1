typedef struct Entry {
    void *value;
    void *(*getter)(int, int);
    unsigned int kind;
    char name[16];
    int data;
    struct Entry *next;
} Entry;

typedef struct Menu {
    char pad[32];
    Entry *entries;
} Menu;

extern Entry *D_800EAFEC;
extern char D_800C3CEC[];
extern char *func_80094044(char *, char *, int);
extern int func_8008AFB0(char *, char *, ...);

void func_80076A90(void *(*source)(int, int), unsigned int kind, char *label, int data, Menu *menu) {
    char name[16];
    Entry *next;

    if (D_800EAFEC == 0) {
        return;
    }
    func_80094044(name, label, 16);
    name[15] = 0;
    switch (kind) {
    case 10:
    case 11:
    case 12:
        D_800EAFEC->getter = source;
        D_800EAFEC->value = source(1, 0);
        break;
    default:
        D_800EAFEC->value = source;
        break;
    }
    func_8008AFB0(D_800EAFEC->name, D_800C3CEC, name);
    D_800EAFEC->data = data;
    D_800EAFEC->kind = kind;
    next = D_800EAFEC->next;
    D_800EAFEC->next = menu->entries;
    menu->entries = D_800EAFEC;
    D_800EAFEC = next;
}
