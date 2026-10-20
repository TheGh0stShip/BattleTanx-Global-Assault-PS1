typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct GridState {
    u16 x;
    u16 y;
    char pad4[4];
    u16 width;
    u16 stride;
    u16 *cells;
} GridState;

typedef struct GridObject {
    char pad0[8];
    u16 links[4];
    u16 x;
    u16 y;
    char pad14[14];
    s16 inactive;
    char pad24[4];
} GridObject;

extern u16 D_800A435C[];
extern u16 D_800A4364[];
extern u16 D_800A4374;
extern GridState D_800C6290;
extern GridObject D_800C62B0[];

void func_80015CF8(u16 object_index) {
    register u16 index asm("$7") = object_index;
    register u16 saved_index asm("$8") = object_index;
    register GridState *grid_base asm("$9");
    register GridState *grid asm("$6");
    register GridObject *object_cursor asm("$4");
    register s32 slot asm("$5");
    register s32 offset asm("$4");
    s32 row;
    u16 *cell;
    register u16 previous asm("$2");

    {
        register u32 table_index asm("$2") = saved_index & 0xFFFF;
        register u32 byte_offset asm("$3") = ((table_index << 2) + table_index) << 3;
        register GridObject *object_base asm("$2");
        register GridObject *object asm("$5");
        __asm__ volatile ("" : "+r"(byte_offset));
        object_base = D_800C62B0;
        object = (GridObject *)((char *)object_base + byte_offset);
        object_cursor = object;
        grid_base = &D_800C6290;
        grid = grid_base;
        if (object->inactive >= 0x401) {
            register u16 *head asm("$4") = grid->cells;
            register u16 *count_ptr asm("$3") = &D_800A4374;
            register u16 count asm("$2") = *count_ptr;
            count++;
            *count_ptr = count;
            object->links[0] = head[0];
            head[0] = index;
            return;
        }
    }

    slot = 0;
    {
        register u16 *table_base asm("$2");
        register u16 *x_offsets asm("$12");
        register u16 *y_offsets asm("$11");
        register GridObject *loop_object asm("$7");
        register s32 x_delta asm("$10");
        s32 y_delta;
        register u32 x_work asm("$3");
        register u32 origin_x asm("$2");
        register u32 origin_y asm("$4");
        __asm__ volatile ("lui %0,%%hi(D_800A435C)\n\taddiu %1,%0,%%lo(D_800A435C)"
                          : "=r"(table_base), "=r"(x_offsets));
        __asm__ volatile ("lui %0,%%hi(D_800A4364)\n\taddiu %1,%0,%%lo(D_800A4364)"
                          : "=r"(table_base), "=r"(y_offsets));
        __asm__ volatile ("" : "+r"(x_offsets), "+r"(y_offsets));
        loop_object = object_cursor;
        __asm__ volatile ("" : "+r"(object_cursor), "+r"(loop_object));
        x_work = object_cursor->x;
        origin_x = grid_base->x;
        origin_y = grid->y;
        x_work -= origin_x;
        x_work <<= 16;
        x_delta = (s32)x_work >> 16;
        y_delta = (s16)(loop_object->y - origin_y);
        do {
            offset = (slot & 0xFFFF) * 2;
            row = (((y_delta + y_offsets[slot & 0xFFFF]) >> 10)
                 + slot * grid->stride) * grid->width;
            cell = grid->cells + ((row + ((x_delta + x_offsets[slot & 0xFFFF]) >> 10)) & 0xFFFF);
            slot++;
            previous = cell[1];
            __asm__ volatile ("addu %0,%1,%0" : "+r"(offset) : "r"(loop_object));
            *(u16 *)(offset + 8) = previous;
            cell[1] = saved_index;
        } while ((u32)(slot & 0xFFFF) < 4U);
    }
}
