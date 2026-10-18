typedef void (*Callback)(int);
typedef struct {
    char pad[0x14];
    Callback *start;
    Callback *end;
    unsigned int align;
} CallbackList;
extern CallbackList D_80086058;

void func_800869B0(int arg) {
    CallbackList *list = &D_80086058;
    unsigned int align = list->align;
    unsigned int mask = -align;
    Callback *p = (Callback *)((unsigned int)list->start & mask);
    Callback *end = (Callback *)((unsigned int)list->end & mask);

    for (; p < end && *p != 0; p = (Callback *)(((unsigned int)p + align) & mask)) {
        (*p)(arg);
    }
}
