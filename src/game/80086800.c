typedef struct Module {
    void (*init)(void);
    char pad04[8];
    int order;
    void **deps;
} Module;

typedef struct ModuleInfo {
    char pad00[8];
    unsigned int start;
    unsigned int end;
    unsigned int align;
} ModuleInfo;

extern ModuleInfo D_80086058;
extern void func_800864C4(void);
extern Module **func_800866FC(Module **p, Module **end);

void func_80086800(void) {
    ModuleInfo *info;
    unsigned int align;
    unsigned int mask;
    Module **p;
    Module **end;
    Module **m;
    Module *tmp;
    void (*init)(void);
    int order;

    func_800864C4();
    info = &D_80086058;
    align = info->align;
    mask = -align;
    p = (Module **)(info->start & mask);
    end = (Module **)(info->end & mask);
    order = 1;
    while (p < end) {
        m = func_800866FC(p, end);
        if (m == 0) {
            __asm__ volatile("break 0");
            for (;;) {
            }
        }
        if (m != p) {
            tmp = *p;
            *p = *m;
            *m = tmp;
        }
        {
            Module *mod = *p;
            mod->order = order;
            init = mod->init;
        }
        order++;
        if (init != 0) {
            init();
        }
        p = (Module **)(((unsigned int)p + align) & mask);
    }
}
