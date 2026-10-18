typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Tracker {
    u8 pad_00[0x14];
    u16 handle;
} Tracker;

typedef struct Tank {
    u8 pad_000[0xF8];
    Tracker tracker;
} Tank;

typedef struct Object {
    u8 pad_00[0x10];
    u16 handle;
} Object;

extern Object *func_8004A794(u16);

u16 func_8004C0F8(Tank *tank, Object **output) {
    Tracker *tracker = &tank->tracker;
    u16 handle = tracker->handle;
    Object *object;
    if (handle == 0) return 0;
    object = func_8004A794(handle);
    tracker->handle = object->handle;
    object->handle = 0;
    if (output != 0) *output = object;
    return handle;
}
