typedef struct Obj {
    int id;
    char pad4[0x218 - 4];
    int status;
} Obj;
typedef struct {
    char pad0[4];
    short kind;
    short pad6;
    Obj *obj;
} Link;
typedef struct {
    char pad0[0x60];
    Link *link;
    char pad64[0x78 - 0x64];
    Obj *holder;
    char pad7C[0xAC - 0x7C];
    int fallback;
} Unit;
extern void func_80053E14(Obj *);
extern void func_80052A24(Unit *, int);

int func_80052CE4(Unit *unit) {
    int id = 0;
    Obj *holder = 0;
    Obj *p;
    Link *link;

    if ((p = unit->holder) != 0) {
        holder = p;
        id = holder->id;
    } else if (unit->fallback != 0) {
        id = unit->fallback;
    }
    if (id == 0) {
        return -1;
    }
    link = unit->link;
    if (link->kind == 4) {
        Obj *o = link->obj;
        o->status &= ~2;
        func_80053E14(o);
    }
    if (holder != 0) {
        holder->status |= 2;
    }
    func_80052A24(unit, id);
    return 0;
}
