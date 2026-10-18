typedef struct Obj Obj;
typedef struct {
    char pad0[0xC];
    int team;
} Owner;
struct Obj {
    char pad0[0x208];
    Owner *owner;
};
typedef struct {
    char pad0[4];
    short kind;
    short pad6;
    Obj *obj;
} Link;
typedef struct {
    char pad0[0xC];
    int kind;
    char pad10[4];
    Obj *object;
    Link *link;
} Node;
typedef struct {
    char pad0[0xC];
    int team;
} Marker;
extern Node *func_80023870(Node *, int);
extern unsigned short func_80033DD4(Obj *);
extern int func_80047658(Obj *);
extern int func_80051340(Marker *, int, void *, int);

int func_80050B2C(Marker *m) {
    Node *node;
    Node *zone = 0;
    Obj *own = 0;
    Obj *enemy = 0;
    Obj *best_obj = 0;
    unsigned short best = 0;
    void *target;
    int result;

    for (node = func_80023870(0, 8); node != 0; node = func_80023870(node, 8)) {
        switch ((unsigned int)node->kind) {
        case 0: {
            Obj *obj = node->object;
            unsigned short value = func_80033DD4(obj);

            if (value > best) {
                best_obj = obj;
                best = value;
            }
            break;
        }
        case 1:
            zone = node;
            break;
        case 2: {
            Link *link = node->link;

            if (link->kind == 4) {
                Obj *obj = link->obj;

                if (func_80047658(obj) != 0) {
                    if (obj->owner->team != m->team) {
                        enemy = obj;
                    } else if (obj->owner == (Owner *)m) {
                        own = obj;
                    }
                }
            }
            break;
        }
        }
    }
    if (own != 0) {
        target = own;
        result = func_80051340(m, 6, &target, 1);
    } else if (enemy != 0) {
        target = enemy;
        result = func_80051340(m, 3, &target, 1);
    } else if (zone != 0) {
        target = zone;
        result = func_80051340(m, 5, &target, 1);
    } else if (best_obj != 0) {
        target = best_obj;
        result = func_80051340(m, 4, &target, 1);
    } else {
        result = func_80051340(m, 2, 0, 0);
    }
    return result;
}
