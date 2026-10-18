typedef void (*DisplayNotify)(void *state, void *value);

typedef struct DisplayInterface {
    void *unknown_00[2];
    void (*dispatch)(void *context, void *value, int first, int second);
    void *unknown_0C[3];
    void *context;
} DisplayInterface;

extern unsigned char D_800B0C62;
extern DisplayNotify D_800B0C5C;
extern DisplayInterface *D_800B0C58;
extern unsigned char D_800C4C6C;

void func_8007FEA8(void *value)
{
    if (D_800B0C62 >= 2)
        D_800B0C5C(&D_800C4C6C, value);
    {
        register void *argument asm("$5");
        register int first asm("$6");
        register int second asm("$7");

        asm volatile("addu %0,%1,$zero" : "=r"(argument) : "r"(value));
        asm("addu %0,$zero,$zero" : "=r"(first));
        second = 0;
        D_800B0C58->dispatch(D_800B0C58->context, argument, first, second);
    }
}
