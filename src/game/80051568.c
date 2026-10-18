typedef struct Link Link;
typedef struct Obj {
    Link *link;
    char pad4[0x218 - 4];
    int status;
} Obj;
struct Link {
    char pad0[4];
    short kind;
    short pad6;
    Obj *obj;
};
typedef struct {
    char pad0[0x60];
    Link *link;
    unsigned char active;
    char pad65[0x78 - 0x65];
    Obj *holder;
    char pad7C[0x80 - 0x7C];
    Obj *selected;
    char pad84[0xAC - 0x84];
    Link *fallback;
} Unit;
extern void func_80053E14(Obj *);
extern void func_80052A24(Unit *, Link *);

static inline int release_holder(Unit *unit) {
    Link *id = 0;
    Obj *holder = 0;
    Obj *p;
    Link *link;

    if ((p = unit->holder) != 0) {
        holder = p;
        id = holder->link;
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

int func_80051568(Unit *unit) {
    Link *link;

    if (unit->active == 0) {
        return -1;
    }
    if (unit->selected == 0) {
        return -1;
    }
    if (unit->selected->link == unit->link) {
        return release_holder(unit);
    }
    link = unit->link;
    if (link->kind == 4) {
        Obj *o = link->obj;
        o->status &= ~2;
        func_80053E14(o);
    }
    {
        Obj *sel = unit->selected;
        sel->status |= 2;
        func_80052A24(unit, sel->link);
    }
    return 0;
}
