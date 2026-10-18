typedef unsigned int u32;

typedef struct {
    char pad000[0x78];
    void *slots[3];
} Context;

typedef struct {
    char pad000[4];
    void *current;
    char pad008[0x98];
    u32 slot_index;
    char pad0A4[0x174];
    u32 flags;
} Participant;

void *func_80052F38(Context *context, Participant *participant) {
    void *current;
    u32 slot_index;

    if (participant == 0 || !(participant->flags & 1)) {
        current = context->slots[0];
        slot_index = 0;
    } else {
        slot_index = participant->slot_index;
        current = participant->current;
    }

    while (current == 0 && slot_index < 2) {
        slot_index++;
        current = context->slots[slot_index];
    }
    return current;
}
