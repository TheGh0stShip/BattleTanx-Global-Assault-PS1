typedef unsigned short u16;
typedef unsigned int u32;

typedef struct GridObject {
    char pad0[8];
    u16 links[4];
    char pad10[24];
} GridObject;

extern GridObject D_800C62B0[];
extern char D_800C0000;

int func_80015C2C(int target_index, u16 *head, int slot) {
    register int current asm("$3") = *head;
    register u32 sentinel asm("$7") = 0xFFFF;
    u32 target;
    register u32 current_index asm("$2");
    u32 link_offset;
    GridObject *object;
    u16 next;
    u32 next_index;

    __asm__ volatile ("" : "+r"(current));
    current_index = current & 0xFFFF;
    if (current_index == sentinel) {
        return 0;
    }
    target = target_index & 0xFFFF;
    if (current_index == target) {
        register u32 direct_object asm("$3");
        register char *object_base asm("$2");
        __asm__ volatile ("" : "+r"(current_index));
        direct_object = current_index << 2;
        direct_object += current_index;
        direct_object <<= 3;
        object_base = (char *)D_800C62B0;
        direct_object += (u32)object_base;
        direct_object += (slot & 0xFFFF) * 2;
        *head = *(u16 *)(direct_object + 8);
        return 1;
    }
    if (current_index != sentinel) {
        register GridObject *base_temp asm("$2");
        register GridObject *object_base asm("$8");
        register u32 fixed_offset asm("$7");
        register u32 end_index asm("$9");
        base_temp = (GridObject *)&D_800C0000;
        __asm__ volatile ("" : "+r"(base_temp));
        object_base = (GridObject *)((char *)base_temp + 0x62B0);
        fixed_offset = (slot & 0xFFFF) * 2;
        end_index = 0xFFFF;
        {
        register char *current_link asm("$6");
        register u32 found_index asm("$5");
        register u32 scaled_index asm("$2");
        register u16 found_next asm("$3");
        register u32 loop_index asm("$3");
        __asm__ volatile ("andi %0,%1,0xffff" : "=r"(loop_index) : "r"(current));
        do {
            object = (GridObject *)((char *)object_base + loop_index * 0x28);
            current_link = (char *)object + fixed_offset;
            next = *(u16 *)(current_link + 8);
            next_index = next & 0xFFFF;
            if (next_index == target) {
                char *next_link;
                found_index = next_index;
                scaled_index = found_index << 2;
                next_link = (char *)object_base + ((scaled_index + found_index) << 3) + fixed_offset;
                found_next = *(u16 *)(next_link + 8);
                *(u16 *)(current_link + 8) = found_next;
                return 1;
            }
            loop_index = next & 0xFFFF;
        } while (next_index != end_index);
        }
    }
    return 0;
}
