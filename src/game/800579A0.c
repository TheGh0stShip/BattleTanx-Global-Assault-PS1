typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    char pad000[0x1E6];
    u16 width;
    u16 height;
    u16 depth;
} Resource;

typedef struct {
    u16 width;
    u16 height;
    u16 depth;
    u16 pad006;
    Resource *resource;
    u32 payload;
} RuntimeSlot;

extern RuntimeSlot D_800E46C0[];

Resource *func_8003DCAC(int);

void func_800579A0(u16 slot_index, int resource_index, u32 payload) {
    RuntimeSlot *slots;
    RuntimeSlot *slot;
    Resource *resource;

    resource = func_8003DCAC(resource_index);
    slots = D_800E46C0;
    slot = &slots[slot_index];
    slot->width = resource->width;
    slot->height = resource->height;
    slot->depth = resource->depth;
    slot->resource = resource;
    slot->payload = payload;
}
