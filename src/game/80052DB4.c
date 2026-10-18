typedef struct {
    char pad0[0xC];
    int level;
} Info;
typedef struct {
    char pad0[6];
    unsigned char flags;
    char pad7[5];
    Info *info;
    char pad10[0x58 - 0x10];
    int mode;
    char pad5C[0x84 - 0x5C];
    unsigned char a;
    unsigned char b;
    unsigned char c;
    char pad87[0xBC - 0x87];
    unsigned char d;
} Unit;
extern int func_80022814(Unit *);

void func_80052DB4(Unit *unit) {
    if (func_80022814(unit) != 0) {
        if (unit->flags & 2) {
            if (unit->a == 0 && unit->info->level < 5) {
                unit->mode = 2;
            } else {
                unit->mode = 0;
            }
        } else if (unit->b + unit->c == 0 && unit->d == 0) {
            unit->mode = 2;
        }
    }
}
