typedef struct {
    unsigned short active;
    char pad2[0x32 - 2];
    unsigned short mode;
    int value;
    char handler[4];
} Voice;
extern Voice D_800B5A78;
extern unsigned short *D_800B6B08;
extern int *D_800B6B0C;
extern void func_8009D788(void *);
extern void func_80094168(void);

Voice *func_8009499C(void) {
    Voice *v = &D_800B5A78;
    Voice *ret;

    __asm__("" : "=r"(v) : "0"(v));

    if (v->active == 0) {
        func_8009D788(v->handler);
        v->active = 1;
        *D_800B6B08 = v->mode;
        *D_800B6B0C = v->value;
        func_80094168();
        ret = v;
    } else {
        ret = 0;
    }
    return ret;
}
