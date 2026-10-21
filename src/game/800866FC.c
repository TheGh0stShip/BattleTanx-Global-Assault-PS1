typedef struct Module {
    void *init;
    char pad04[8];
    int order;
    void **deps;
} Module;

extern unsigned int D_80086068;
extern Module *func_80086694(void *name);

Module **func_800866FC(Module **p, Module **end) {
    unsigned int align = D_80086068;
    unsigned int mask = -align;
    Module **found = 0;
    void **deps;
    int ok;
    Module *m;

    for (; p < end && found == 0; p = (Module **)(((unsigned int)p + align) & mask)) {
        deps = (*p)->deps;
        ok = 1;
        while (*deps != 0 && ok) {
            m = func_80086694(*deps);
            if (m == 0) {
                __asm__ volatile("break 0");
                for (;;) {
                }
            }
            if (m->order == 0) {
                ok = 0;
            }
            deps++;
        }
        if (ok) {
            found = p;
        }
    }
    return found;
}
