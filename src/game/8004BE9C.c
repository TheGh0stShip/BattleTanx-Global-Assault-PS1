typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Tracker {
    u8 pad_00[0x0E];
    u16 object_handle;
    u16 count;
    u16 epoch;
} Tracker;

typedef struct Tank {
    u8 pad_000[0xF8];
    Tracker tracker;
} Tank;

typedef struct Object {
    u8 pad_00[2];
    u16 handle;
    u8 pad_04[0x1A - 4];
    u16 field_1A;
} Object;

extern void *D_800A5B24;
extern Object *func_8004A794(u16 handle);
extern void func_8004A7C4(u16 handle);

int func_8004BE9C(Tank *tank) {
    Tracker *tracker = &tank->tracker;
    u8 *system = (u8 *)D_800A5B24 + 0x8000;
    u16 amount = *(u16 *)(system + 0x6012) - tracker->epoch;

    if (amount == 0) {
        return 0;
    }

    if (tracker->count >= amount) {
        u16 saved_handle;

        do {
            Object *object = func_8004A794(tracker->object_handle);
            saved_handle = object->handle;
            func_8004A7C4(tracker->object_handle);
            tracker->object_handle = saved_handle;
            object = func_8004A794(saved_handle);
            if (object != 0) {
                object->field_1A = 0;
            }
            tracker->count--;
        } while (tracker->count >= amount);
    }

    return 1;
}
