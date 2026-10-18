typedef struct ResourceObject {
    unsigned char unused[0x14C];
    unsigned short handle;
} ResourceObject;

extern void func_8001B094(unsigned int handle);

void func_8004D134(ResourceObject *object) {
    unsigned int invalid = 0xFFFF;

    if (object->handle != invalid) {
        func_8001B094(object->handle);
        object->handle = invalid;
    }
}
