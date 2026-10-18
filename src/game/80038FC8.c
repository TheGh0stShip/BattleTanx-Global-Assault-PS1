typedef unsigned char u8;

typedef struct ObjectState {
    u8 pad_00[0x2C];
    short mode;
} ObjectState;

extern void func_80037E64(ObjectState *object);
extern void func_80038584(ObjectState *object);

void func_80038FC8(ObjectState *object) {
    ObjectState *current = object;

    if (object->mode == 1) {
        func_80037E64(object);
    } else if (object->mode == 0) {
        func_80038584(current);
    }
}
