typedef struct {
    int x;
    int y;
    int z;
} Vector;
typedef struct {
    int x;
    int z;
    unsigned short id;
    char padA[2];
} Spot;
typedef struct {
    char pad0[0x18];
    int a18;
    int a1C;
    char pad20;
    unsigned char color;
} Team;
typedef struct {
    int slots[5];
    unsigned char color;
} Info;
typedef struct {
    unsigned char flags;
    unsigned char index;
    char pad2[2];
    Team *team;
    int a8;
    int aC;
    int value;
    int stats[7];
    Spot *spots;
    unsigned char kind;
    char pad35[3];
    int mode;
    int a3C;
    int pair[2];
} Desc;
typedef struct {
    int x;
    int pad4;
    int z;
    unsigned short id;
    unsigned char index;
    char padF;
    int a10;
    int a14;
    int a18;
    int a1C;
    int a20;
    int pair[2];
    int a2C;
} Event;
typedef struct {
    unsigned short h0;
    unsigned short h2;
    unsigned short h4;
    unsigned char flags;
    unsigned char index;
    int mask;
    Team *team;
    char pad10[0x54 - 0x10];
    int value;
    char pad58[4];
    void *slot;
    int a60;
    unsigned char a64;
    char pad65[0x70 - 0x65];
    int a70;
    short a74;
    char pad76[2];
    int *a78;
    int *a7C;
    char pad80[4];
    unsigned char a84[3];
    char pad87;
    int stats[7];
    unsigned char color;
    char padA5[3];
    Spot *spots;
    int aAC;
    int aB0;
    int pair[2];
    unsigned char aBC;
    unsigned char kind;
    unsigned char order[16];
    unsigned char aCE;
} Player;
typedef struct {
    char data[156];
} Slot;
extern Slot D_800D3038[];
extern unsigned char D_800D2FED;
extern int D_800A6070;
extern Info *func_80053338(int);
extern int func_80052784(Player *, int *, void *);
extern void func_8008A7BC(void *, void *, int);
extern void func_8008AA48(void *, int, int);
extern void func_8003EEF8(Event *);
extern int func_80022814(void);
extern void func_80034CD4(Vector *, unsigned short, unsigned char, int, int, int, int, int, int, int, int, int);
extern int func_8006C2D4(Player *);
extern void func_80014DB4(void *);
extern void func_800149B8(void *, int, int);
extern void func_80053260(Player *);

static inline void set_pair(Event *event, Player *player) {
    event->pair[0] = player->pair[0];
    event->pair[1] = player->pair[1];
}

void func_800516B8(Player *player, Desc *desc) {
    Event event;
    int list[16];
    char extra[16];
    Vector pos;
    Vector tmp;
    Info *info;
    Team *team;
    int count;
    int i;
    unsigned short mask;
    int value;
    int offset;

    info = func_80053338(desc->value);
    player->h0 = 0;
    player->h4 = 76;
    player->h2 = 0;
    player->flags = desc->flags;
    player->index = desc->index;
    player->team = desc->team;
    player->a70 = 0;
    player->a74 = 0;
    player->team->a1C = desc->aC;
    player->team->a18 = desc->a8;
    player->spots = desc->spots;
    {
        int n;

        for (n = 0; n < 16;) {
            player->order[n] = n + 1;
            n++;
            player->aCE = 2;
        }
    }
    player->value = desc->value;
    player->aB0 = desc->a3C;
    count = func_80052784(player, list, extra);
    {
        int n;

        for (n = 0; n < count; n++) {
            player->mask |= 1 << list[n];
        }
    }
    player->aAC = 0;
    player->kind = desc->kind;
    player->aBC = 0;
    func_8008A7BC(player->pair, desc->pair, 8);
    {
        int n;

        for (n = 0; n < 7; n++) {
            player->stats[n] = desc->stats[n];
        }
    }
    func_8008AA48(&player->a78, 0, 12);
    func_8008AA48(player->a84, 0, 3);
    switch (desc->mode) {
    case 2:
        event.x = player->spots[1].x;
        event.pad4 = 0;
        event.z = player->spots[1].z;
        event.id = player->spots[1].id;
        event.index = player->index;
        event.a10 = 2;
        event.a14 = 2;
        event.a18 = 23;
        event.a1C = player->aB0;
        event.a20 = 0;
        event.a2C = 0;
        set_pair(&event, player);
        func_8003EEF8(&event);
    case 0:
    case 5:
        event.x = player->spots[0].x;
        event.pad4 = 0;
        event.z = player->spots[0].z;
        event.id = player->spots[0].id;
        event.index = player->index;
        event.a10 = info->slots[0];
        event.a14 = 0;
        event.a18 = 4;
        event.a1C = player->aB0;
        event.a20 = 2;
        set_pair(&event, player);
        event.a2C = 0;
        func_8003EEF8(&event);
        break;
    case 1:
    case 4:
        if (func_80022814() != 0 && player->index == 1) {
            break;
        }
        event.x = player->spots[1].x;
        event.pad4 = 0;
        event.z = player->spots[1].z;
        event.id = player->spots[1].id;
        event.index = player->index;
        event.a10 = 2;
        event.a14 = 2;
        event.a18 = 23;
        event.a1C = player->aB0;
        event.a20 = 0;
        set_pair(&event, player);
        event.a2C = 0;
        func_8003EEF8(&event);
        break;
    case 3:
        break;
    }
    if ((func_80022814() == 0 && !(player->flags & 2)) || desc->mode == 5 || desc->mode == 6) {
        mask = 0;
        for (i = 0; i < 5; i++) {
            mask |= 1 << info->slots[i];
        }
        for (i = 0; i < 5; i++) {
            tmp.x = (&player->spots[i])->x;
            tmp.y = 0;
            tmp.z = (&player->spots[i])->z;
            pos = tmp;
            func_80034CD4(&pos, (&player->spots[i])->id, player->index, 0xFFFF,
                          mask, 0, 0, 6, 0, 0, 0, 0);
        }
        if (desc->mode == 6) {
            switch (D_800D2FED) {
            case 2:
                player->kind = 5;
                break;
            case 3:
                player->kind = 4;
                break;
            case 4:
                player->kind = 3;
                break;
            }
        } else {
            if (desc->mode == 5) {
                player->kind = 4;
            } else {
                player->kind = 1;
            }
        }
    }
    if (player->flags & 2) {
        if ((unsigned int)(desc->mode - 3) < 2) {
            value = func_8006C2D4(player);
        } else if (player->a78 != 0) {
            value = *player->a78;
        } else if (player->a7C != 0) {
            value = *player->a7C;
        } else {
            if (D_800A6070 != 10) {
                return;
            }
            value = 0;
        }
        player->slot = &D_800D3038[player->index];
        func_80014DB4(player->slot);
        func_800149B8(player->slot, value, 0);
        player->a60 = value;
        player->a64 = 1;
        func_80053260(player);
    }
    if (func_80022814() != 0) {
        player->color = info->color;
    } else {
        player->color = player->team->color;
    }
}
