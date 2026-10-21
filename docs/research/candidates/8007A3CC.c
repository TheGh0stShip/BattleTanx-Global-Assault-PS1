typedef signed int s32;
typedef signed char s8;
typedef unsigned char u8;

typedef struct AnimationEntry {
    s32 position;
    s32 speed;
    s8 *destination;
    u8 base;
    s8 period;
    u8 reverse;
    u8 unused0F;
} AnimationEntry;

extern s32 D_800C60D0;

void func_8007A3CC(AnimationEntry *entry) {
    s32 index;
    s32 position;
    s32 modulus;

    index = 0;
    if (D_800C60D0 != 7) {
        do {
            if (entry->destination != 0) {
                position = entry->position;
                if (entry->speed != 0) {
                    if (entry->reverse != 0) {
                        position -= entry->speed;
                    } else {
                        position += entry->speed;
                    }
                    modulus = (s32)entry->period << 12;
                    if ((position * (s32)entry->period) < 0) {
                        position += modulus;
                        modulus = (s32)entry->period << 12;
                    }
                    position %= modulus;
                    entry->position = position;
                    *entry->destination = (s8)(entry->base + (position >> 12));
                }
            }
            index++;
            entry++;
        } while (index < 5);
    }
}
