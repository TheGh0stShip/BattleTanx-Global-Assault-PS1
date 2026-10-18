typedef struct {
    char pad0[0xC];
    int team;
} Owner;
typedef struct {
    char pad0[0x208];
    Owner *owner;
    char pad20C[0x218 - 0x20C];
    int status;
    char pad21C[0x598 - 0x21C];
} Tank;
typedef struct {
    int count;
    Tank *tanks[16];
} TankList;
extern Tank D_800DE33C[];

void func_80049EC8(TankList *list, int mask, int team, int friends, int enemies) {
    unsigned short count = 0;
    unsigned short i;
    int bit;
    Tank *tank;

    for (i = 0, bit = 1; i < 16; i++, bit <<= 1) {
        if (bit & mask) {
            tank = &D_800DE33C[i];
            if (tank->status & 1) {
                if (tank->owner->team == team) {
                    if (friends) {
                        list->tanks[count] = tank;
                        count++;
                    }
                } else if (enemies) {
                    list->tanks[count] = tank;
                    count++;
                }
            }
        }
    }
    list->count = count;
}
