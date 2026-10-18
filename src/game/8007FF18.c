typedef void (*DisplayNotify)(void *state, void *value);

typedef struct DisplayInterface {
    void *unknown_00[2];
    void (*dispatch)(void *context, void *value, int first, int second);
    void *unknown_0C[3];
    void *context;
} DisplayInterface;

extern unsigned char D_800B0C62[];
extern DisplayNotify D_800B0C5C;
extern DisplayInterface *D_800B0C58;
extern unsigned char D_800C4C80;
extern void func_80080638(void *data, void *packet);
extern void func_8008A7BC(void *destination, const void *source,
                          unsigned int size);

void *func_8007FF18(void *argument)
{
    register unsigned char *state asm("$18") = D_800B0C62;
    unsigned char *packet = argument;
    unsigned char *data;

    asm("" : "+r"(state));
    if (state[0] >= 2)
        D_800B0C5C(&D_800C4C80, packet);
    data = packet + 28;
    func_80080638(data, packet);
    {
        register unsigned int mask asm("$4") = 0x00FFFFFF;
        register void *dispatch_data asm("$5") = data;
        register int size asm("$6") = 64;
        register DisplayInterface *interface asm("$3");
        unsigned int flags = *(volatile unsigned int *)data;

        asm(
            "lui %0,%%hi(D_800B0C58)\n\t"
            "lw %0,%%lo(D_800B0C58)(%0)"
            : "=r"(interface)
            : "r"(flags)
        );
        flags |= mask;
        *(unsigned int *)data = flags;
        interface->dispatch(interface->context, dispatch_data, size, 0);
    }
    func_8008A7BC(state + 14, packet, 92);
    return packet;
}
