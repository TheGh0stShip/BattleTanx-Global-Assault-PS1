typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;

extern u8 *func_8004A794(u16 id);

void func_8004C058(u8 *list, u16 id) {
    u8 *node = func_8004A794(id);
    u16 *link = (u16 *)(list + 0x10C);
    s32 value = *(s32 *)(node + 8);

    while (*link != 0) {
        u8 *current = func_8004A794(*link);
        if (value < *(s32 *)(current + 8)) {
            break;
        }
        link = (u16 *)(current + 0x10);
        if (*link == 0) {
            break;
        }
    }

    *(u16 *)(node + 0x10) = *link;
    *link = id;
}
