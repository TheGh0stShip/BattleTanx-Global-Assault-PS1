typedef void (*DisplayNotify)(void *state, void *value);

typedef struct DisplayInterface {
    void *unknown[15];
    void (*apply)(void *value);
} DisplayInterface;

extern unsigned char D_800B0C62;
extern DisplayNotify D_800B0C5C;
extern DisplayInterface *D_800B0C58;
extern unsigned char D_800C4BC8;

void func_8007FA74(void *value)
{
    if (D_800B0C62 >= 2)
        D_800B0C5C(&D_800C4BC8, value);
    D_800B0C58->apply(value);
}
