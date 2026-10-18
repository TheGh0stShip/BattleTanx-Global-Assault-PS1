typedef unsigned char u8;
typedef unsigned short u16;

typedef struct ObjectState {
    u8 pad_00[0xFC];
    u16 pool_index;
} ObjectState;

extern void *func_8004A794(u16 index);

void *func_8004BE20(ObjectState *object) {
    return func_8004A794(object->pool_index);
}
