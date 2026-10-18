typedef struct { int x, y, z; } Vector;
typedef struct { int x, z; } Offset;
typedef struct Item Item;
struct Item { int pad[7]; Item *next; Vector pos; };
typedef struct { int pad[2]; Item *items; Vector pos; } Pile;
extern Offset D_800A4804[];

void func_80033CEC(Pile *pile, Vector *out) {
    int i;
    Vector cand;
    Item *it;
    unsigned char found;

    for (i = 0; i < 5; i++) {
        cand.x = pile->pos.x + D_800A4804[i].x;
        cand.y = pile->pos.y;
        cand.z = pile->pos.z + D_800A4804[i].z;
        found = 0;
        it = pile->items;
        while (it != 0) {
            if (cand.x == it->pos.x && cand.y == it->pos.y && cand.z == it->pos.z) {
                found = 1;
                it = 0;
            } else {
                it = it->next;
            }
        }
        if (!found) {
            out->x = cand.x;
            out->y = cand.y;
            out->z = cand.z;
            return;
        }
    }
}
