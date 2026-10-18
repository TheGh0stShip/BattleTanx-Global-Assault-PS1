typedef unsigned int u32;

extern int func_800825A4(u32 *handle, void *source);
extern u32 func_80082984(u32 *handle, void *selector, u32 expected);
extern int func_800826A0(u32 *handle);

int func_80082B20(void *source, void *selector, u32 expected)
{
    u32 handle[18];
    int result = 0;

    if (func_800825A4(handle, source) != 0) {
        result = func_80082984(handle, selector, expected) == expected;
        if (func_800826A0(handle) == 0) {
            result = 0;
        }
    }
    return result;
}
