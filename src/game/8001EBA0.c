typedef struct Cell {
    int flags;
    void *owner;
    unsigned short next[4];
    char pad10[0x24 - 0x10];
    unsigned short angle;
    char pad26[0x28 - 0x26];
} Cell;
typedef struct Hit {
    void *owner;
    unsigned short id;
    char pad06[0x24 - 6];
} Hit;
typedef struct Pos2 {
    int x;
    int z;
} Pos2;
typedef struct Contact {
    char pad00[0x5D];
    unsigned char stuck;
} Contact;
typedef struct Tank {
    char pad00[8];
    int x;
    int y;
    int z;
    char pad14[0x2C - 0x14];
    unsigned short angle;
    char pad2E[0x34 - 0x2E];
    Contact contact;
    char pad92[0x2B8 - 0x92];
    unsigned short grid_id;
} Tank;
extern Cell D_800C62B0[];
extern unsigned short D_800C628C;
void func_80015F64(unsigned short, short, short);
unsigned short func_80017AAC(unsigned short, int, Hit *, int, int);
void func_8001AD5C(unsigned short, unsigned short, Contact *);
void func_8001C4D0(Contact *, unsigned short, Pos2 *, Pos2 *, Hit *, unsigned int, int *, Pos2 *, int *, int);
void func_8003FB68(Tank *, int, int, int);

static inline int to_int(int v) {
    return v >= 0 ? v >> 12 : -(-v >> 12);
}

void func_8001EBA0(Tank *tank) {
    register Contact *contact asm("$18") = &tank->contact;
    register unsigned short iter asm("$17") = 0;
    Pos2 moved;
    Pos2 from;
    Pos2 normal;
    Hit hits[8];
    int depth;
    int extra;
    unsigned short count;
    unsigned short gid;
    register unsigned int n asm("$19");
    unsigned char j;
    unsigned char found;

    if (tank->grid_id == 0xFFFF) {
        return;
    }
    do {
        short gx = to_int(tank->x) >> 2;
        int gz = (short)(to_int(tank->z) >> 2);

        {
            unsigned short id = tank->grid_id;
            unsigned short angle = tank->angle;

            if (id != 0xFFFF) {
                D_800C62B0[id].angle = angle;
                func_80015F64(id, gx, gz);
            }
        }
        moved.x = from.x = tank->x;
        moved.z = from.z = tank->z;
        gid = *(volatile unsigned short *)&tank->grid_id;
        D_800C628C = 1;
        count = func_80017AAC(gid, 0xE45C0F, hits, 0, 0);
        if (count == 0) {
            contact->stuck = 0;
            return;
        }
        n = count;
        __asm__("" : "=r"(n) : "0"(n));
        if (iter == 0) {
            found = 0;
            for (j = 0; j < count; j++) {
                if (D_800C62B0[hits[j].id].flags != 8) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                return;
            }
        }
        if (iter == 0) {
            func_8001AD5C(hits[0].id, tank->angle, contact);
        }
        func_8001C4D0(contact, tank->grid_id, &moved, &from, hits, n, &depth, &normal, &extra, -1);
        tank->x = moved.x;
        tank->z = moved.z;
        iter++;
    } while (iter < 11);
    contact->stuck++;
    if (contact->stuck >= 11) {
        func_8003FB68(tank, 30000, 0, 1);
    }
}
