typedef struct {
    unsigned short count;
    int values[4];
    char text[132];
} MessageSlot;

typedef struct {
    char pad0[7];
    unsigned char owner;
} PlayerInfo;

typedef struct {
    short unk0;
    short link;
    int unk4;
    PlayerInfo *info;
    char pad[52];
} PlayerEntry;

typedef struct {
    char pad[44];
    void *layout;
} Panel;

typedef struct {
    int unk0;
    Panel *panel;
} Window;

extern unsigned char D_800D2FEC;
extern short D_800D326C;
extern int D_800C60D0;
extern PlayerEntry *D_800D3258;
extern MessageSlot D_800E4ACC[];
extern signed char D_800A606C;
extern char *D_800AB814;
extern char *D_800AB81C;
extern Window D_800AB868;
extern Window D_800AB8C8;
extern Window D_800AB928;
extern char D_800AB7F4[];
extern char D_800AB804[];
void func_80059550(Window *, int, int);

void func_80063018(unsigned short id, char *str, unsigned short value) {
    MessageSlot *slot;
    char *dst;
    unsigned short len;
    unsigned short i;
    unsigned short count;
    unsigned int layout;
    char **textp;
    Window *win;
    Panel *panel;
    char c;

    if (id >= D_800D2FEC) {
        return;
    }
    if (D_800D326C != -1 && D_800C60D0 != 8) {
        if (D_800D2FEC == 1) {
            return;
        }
        if (D_800D3258[D_800D326C].link != -1) {
            return;
        }
        if (D_800D3258[D_800D326C].info->owner == id) {
            return;
        }
    }
    count = D_800E4ACC[id].count;
    if (count >= 4) {
        return;
    }
    dst = D_800E4ACC[id].text;
    len = 0;
    for (i = 0; i < count; i++) {
        c = *dst;
        if (c != '<' || *++dst != c) {
            c = '<';
        scan:
            if (len < 128) {
                dst++;
                len++;
                if (*dst != c) {
                    goto scan;
                }
            }
        }
        if (len == 128) {
            *dst = 0;
            return;
        }
    }
    if (len != 0) {
        *dst++ = '<';
        len++;
    }
    while (*str != 0 && len < 128) {
        *dst++ = *str++;
        len++;
    }
    *dst++ = '<';
    *dst = 0;
    {
        int scaled = value << 12;
        D_800E4ACC[id].values[D_800E4ACC[id].count] = scaled;
    }
    D_800E4ACC[id].count++;

    switch (id) {
    case 1:
        switch (D_800A606C) {
        case 3:
            layout = 5;
            break;
        case 4:
            layout = 4;
            break;
        case 2:
        default:
            layout = 2;
            break;
        }
        break;
    case 2:
        switch (D_800A606C) {
        case 4:
            layout = 5;
            break;
        case 3:
        default:
            layout = 6;
            break;
        }
        break;
    case 3:
        layout = 6;
        break;
    case 0:
    default:
        switch (D_800A606C) {
        case 2:
        case 3:
            layout = 1;
            break;
        case 4:
            layout = 3;
            break;
        case 1:
            layout = 0;
            break;
        default:
            layout = 0;
            break;
        }
        break;
    }

    if (D_800E4ACC[id].count != 1) {
        return;
    }
    slot = &D_800E4ACC[id];
    switch (layout) {
    case 1:
        textp = &D_800AB814;
        win = &D_800AB8C8;
        break;
    case 2:
        textp = &D_800AB81C;
        win = &D_800AB928;
        break;
    case 0:
        textp = &D_800AB814;
        win = &D_800AB868;
        break;
    default:
        textp = &D_800AB814;
        win = &D_800AB868;
        break;
    }
    *textp = slot->text;
    panel = win->panel;
    switch (id) {
    case 0:
        panel->layout = D_800AB7F4;
        break;
    case 1:
        panel->layout = D_800AB804;
        break;
    }
    func_80059550(win, 0, 1);
}
