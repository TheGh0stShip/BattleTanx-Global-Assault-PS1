typedef unsigned short u16;
typedef unsigned int u32;

typedef struct GridObject {
    char pad0[8];
    u16 links[4];
    char pad10[24];
} GridObject;

extern GridObject D_800C62B0[];

int func_80015C2C(int target_index, u16 *head, int slot) {
    register int current asm("$3") = *head;
    register u32 sentinel asm("$7") = 0xFFFF;
    u32 target;
    register u32 current_index asm("$2");
    u32 link_offset;
    register GridObject *object asm("$2");
    register u16 next asm("$3");
    register u32 next_index asm("$5");

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
        u32 fixed_offset;
        register u32 end_index asm("$9");
        base_temp = (GridObject *)0x800C0000;
        __asm__ volatile ("" : "+r"(base_temp));
        object_base = (GridObject *)((char *)base_temp + 0x62B0);
        fixed_offset = (slot & 0xFFFF) * 2;
        end_index = 0xFFFF;
        {
        register char *current_link asm("$6");
        register u32 scaled_index asm("$2");
        register u16 found_next asm("$3");
        register u32 loop_index asm("$3");
        __asm__ volatile ("andi %0,%1,0xffff" : "=r"(loop_index) : "r"(current));
        do {
            object = (GridObject *)(loop_index * 0x28 + (u32)object_base);
            current_link = (char *)object + fixed_offset;
            next = *(u16 *)(current_link + 8);
            __asm__ volatile ("" : "+r"(next));
            next_index = next & 0xFFFF;
            if (next_index == target) {
                register char *next_link asm("$2");
                scaled_index = next_index << 2;
                next_link = (char *)(((scaled_index + next_index) << 3) +
                                     (u32)object_base) + fixed_offset;
                found_next = *(u16 *)(next_link + 8);
                *(u16 *)(current_link + 8) = found_next;
                return 1;
            }
            __asm__ volatile ("" : "+r"(next));
            loop_index = next & 0xFFFF;
        } while (next_index != end_index);
        }
    }
    return 0;
}
