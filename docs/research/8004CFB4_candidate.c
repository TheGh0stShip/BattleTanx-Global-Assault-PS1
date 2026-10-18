typedef unsigned char u8;
typedef unsigned short u16;

typedef struct PathObject {
    u8 pad_000[0xFC];
    u16 path_node;
    u8 pad_0FE[0x148 - 0xFE];
    u16 target_node;
} PathObject;

extern void *func_8004BE20(PathObject *object);

void *func_8004CFB4(PathObject *object) {
    register unsigned int result = 0;

    if (object->target_node == object->path_node) {
        void *value = func_8004BE20(object);

        if (value != 0) {
            result = (unsigned int)((u8 *)value + 4);
        }
    }
    return (void *)result;
}
