typedef unsigned int u32;

extern int func_80082424(u32 *handle, void *source);
extern u32 func_80082854(u32 *handle, void *selector, u32 value);
extern int func_800826A0(u32 *handle);

u32 func_80082AA0(void *source, void *selector)
{
    u32 handle[18];
    u32 result = 0;
    u32 selected;

    if (func_80082424(handle, source) != 0) {
        selected = func_80082854(handle, selector, handle[3]);
        if (selected == handle[3]) {
            result = selected;
        }
        if (func_800826A0(handle) == 0) {
            result = 0;
        }
    }
    return result;
}
