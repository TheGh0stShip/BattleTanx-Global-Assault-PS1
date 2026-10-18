typedef struct {
    char pad0[4];
    unsigned char *ports;
    char pad8[225];
    unsigned char count;
} Pad80094C10;
extern Pad80094C10 *(*D_800B8C88)(void);

int func_80094C10(int a0, int port, int field) {
    Pad80094C10 *pad = D_800B8C88();
    unsigned char *p;

    if (port < 0) {
        return pad->count;
    }
    if (port >= pad->count) {
        return 0;
    }
    p = pad->ports + port * 5;
    switch (field) {
    case 1:
        return p[0];
    case 2:
        return p[1];
    case 3:
        return p[2];
    case 4:
        return p[3];
    case 5:
        return p[4];
    }
    return 0;
}
