typedef unsigned char u8;
typedef unsigned short u16;

typedef struct ObjectRef {
    u8 type;
    u8 pad_01;
    u16 index;
} ObjectRef;

extern void *func_8004A794(u16 index);
extern void func_800493C0(void *source, void *state);

void func_8004A8B0(ObjectRef *object, void *state) {
    if (object->type == 2) {
        object = func_8004A794(object->index);
    }
    func_800493C0((u8 *)object + 0x10, state);
}
