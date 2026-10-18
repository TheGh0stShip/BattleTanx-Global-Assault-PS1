typedef struct {
    char pad0[0xC];
    int team;
} Owner;
typedef struct {
    char pad0[0xA8];
    unsigned int bits;
    unsigned int enemy_mask;
    unsigned int friend_mask;
    char padB4[0x208 - 0xB4];
    Owner *owner;
} Tank;
typedef struct {
    unsigned int count;
    Tank *tanks[16];
} TankList;
extern void func_80049EC8(TankList *, unsigned int, int, int, int);

void func_80049D38(Tank *tank) {
    TankList list;
    unsigned int clear = ~tank->bits;
    int team = tank->owner->team;
    unsigned short i;

    func_80049EC8(&list, tank->friend_mask, team, 1, 0);
    for (i = 0; i < list.count; i++) {
        list.tanks[i]->friend_mask &= clear;
    }
    func_80049EC8(&list, tank->enemy_mask, team, 0, 1);
    for (i = 0; i < list.count; i++) {
        list.tanks[i]->enemy_mask &= clear;
    }
    tank->friend_mask = 0;
    tank->enemy_mask = 0;
}
