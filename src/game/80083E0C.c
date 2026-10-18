typedef struct {
    unsigned short pad0[2];
    unsigned short enabled;
    unsigned short expired;
    unsigned char pad8[0x1A];
    signed char dx, dy;
    short x, y;
    unsigned char pad28[0x64];
} Bank;

typedef struct {
    unsigned char pad[0xA4];
    short min_x;
    short max_x;
    short min_y;
    short max_y;
    short scale_x;
    short scale_y;
} BankLimits;

extern Bank D_800EE028[];
extern BankLimits D_800EDF78;

void func_80083E0C(int bank, signed char dx_in, signed char dy_in)
{
    int dx = dx_in;
    int dy = dy_in;
    int sx = D_800EDF78.scale_x;
    int sy = D_800EDF78.scale_y;
    int rx = sx - 1;
    int ry = sy - 1;

    if (dx < 0) {
        rx = -rx;
    }
    if (dy < 0) {
        ry = -ry;
    }
    dx = (dx + rx) / sx;
    dy = (dy + ry) / sy;
    D_800EE028[bank].dx = dx;
    dx += D_800EE028[bank].x;
    D_800EE028[bank].dy = dy;
    dy += D_800EE028[bank].y;
    if (dx < D_800EDF78.min_x) {
        dx = D_800EDF78.min_x;
    } else if (dx > D_800EDF78.max_x) {
        dx = D_800EDF78.max_x;
    }
    if (dy < D_800EDF78.min_y) {
        dy = D_800EDF78.min_y;
    } else if (dy > D_800EDF78.max_y) {
        dy = D_800EDF78.max_y;
    }
    D_800EE028[bank].x = dx;
    D_800EE028[bank].y = dy;
}
