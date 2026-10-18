typedef signed int s32;
typedef unsigned int u32;

typedef struct RuntimeHandle {
    s32 index;
    u32 unknown_04;
    void *value;
} RuntimeHandle;

typedef int (*ReleaseCallback)(int message, void *value);

extern unsigned char D_800EDC9C;
extern void func_80083194(RuntimeHandle *handle);

int func_800826A0(RuntimeHandle *handle)
{
    unsigned char *runtime = &D_800EDC9C;
    unsigned char *slot;
    int result = 0;

    if ((u32)handle->index < *(u32 *)(runtime + 8)) {
        slot = runtime + handle->index * 4;
        if (*(RuntimeHandle **)(slot + 0x1C8) == handle) {
            func_80083194(handle);
        }
        result = (*(ReleaseCallback *)(slot + 0x0C))(7, handle->value);
    }
    handle->index = -1;
    handle->value = 0;
    return result;
}
