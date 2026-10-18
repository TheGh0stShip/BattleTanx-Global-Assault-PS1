typedef unsigned char u8;

typedef struct DisplayInterface {
    void *unknown_00[4];
    void (*command)(unsigned int command);
} DisplayInterface;

extern u8 D_800B0C62;
extern void (*D_800B0C5C)(void *state, void *value);
extern DisplayInterface *D_800B0C58;
extern u8 D_800C4BB4;
extern void func_80081E64(void *state, int value, int duration);

void func_8007F9DC(void *value)
{
    register u8 *state asm("$17");
    register void *saved_value asm("$16");
    register DisplayInterface *interface asm("$2");
    register unsigned int command asm("$4");

    asm(
        "lui %0,%%hi(D_800B0C62)\n\t"
        "addiu %0,%0,%%lo(D_800B0C62)"
        : "=r"(state));
    saved_value = value;
    if (*state >= 2) {
        D_800B0C5C(&D_800C4BB4, saved_value);
    }
    if (saved_value == 0) {
        func_80081E64(state + 0x6A, -1, 20);
    }
    asm volatile(
        "lui %1,0x0300\n\t"
        "lui %0,%%hi(D_800B0C58)\n\t"
        "lw %0,%%lo(D_800B0C58)(%0)\n\t"
        "beqz %2,1f\n\t"
        "ori %1,%1,1\n\t"
        "lui %1,0x0300\n"
        "1:"
        : "=r"(interface), "=r"(command)
        : "r"(saved_value));
    interface->command(command);
}
