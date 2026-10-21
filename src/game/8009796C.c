typedef struct {
    unsigned int sector;
    unsigned int size;
    int hash;
} DirEntry;

typedef struct {
    DirEntry *root;
    DirEntry *cur;
    DirEntry *end;
} DirTable;
extern DirTable D_800EF0EC;

DirEntry *func_8009796C(unsigned int sector)
{
    unsigned int after = 0xFFFFFFFF;
    register DirEntry *after_entry asm("$10") = 0;
    unsigned int before = after;
    register DirEntry *before_entry asm("$11") = after_entry;
    unsigned int lowest = after;
    DirEntry *lowest_entry = after_entry;
    DirEntry *e;
    unsigned int dist;

    for (e = D_800EF0EC.root; e < D_800EF0EC.cur; e++) {
        if ((e->size & 0xC0000000) == 0xC0000000) {
            if (e->sector < lowest) {
                lowest = e->sector;
                lowest_entry = e;
            }
            if (e->sector < sector) {
                dist = sector - e->sector;
                if (dist < before) {
                    before = dist;
                    before_entry = e;
                }
            } else {
                dist = e->sector - sector;
                if (dist < after) {
                    after = dist;
                    after_entry = e;
                }
            }
        }
    }
    if (after < 10) {
        e = after_entry;
    } else if (after < 100 && after < before * 2) {
        e = after_entry;
    } else if (before < 100) {
        e = before_entry;
    } else if (after <= 10000 || before <= 10000) {
        e = (before < after) ? before_entry : after_entry;
    } else if (lowest != 0xFFFFFFFF) {
        e = lowest_entry;
    } else {
        e = (before < after) ? before_entry : after_entry;
    }
    if (e == 0) {
        e = D_800EF0EC.cur;
    }
    return e;
}
