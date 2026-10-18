typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Owner {
    u8 pad_00[8];
    u32 *object;
} Owner;

extern void func_8004E470(u32 *object);
extern void func_8004D9FC(u32 *object);
extern void func_8004A9BC(u32 *object);
extern void func_8004CCE8(u32 *object);
extern void func_8004D1C4(u32 *object);

void func_80048EE4(Owner *owner) {
    u32 *object = owner->object;

    func_8004E470(object);
    func_8004D9FC(object);
    func_8004A9BC(object);
    func_8004CCE8(object);
    func_8004D1C4(object);
}
