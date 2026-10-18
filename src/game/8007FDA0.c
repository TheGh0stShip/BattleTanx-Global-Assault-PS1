typedef unsigned char u8;
typedef unsigned int u32;

typedef struct DisplayInterface {
    void *unknown_00[11];
    void (*submit)(void *packet, void *value);
} DisplayInterface;

extern u8 D_800B0C62;
extern void (*D_800B0C5C)(void *state, void *packet, void *value);
extern DisplayInterface *D_800B0C58;
extern u8 D_800C4C54;
extern u32 D_800B0D0C;
extern u32 D_800B0D20;

void *func_8007FDA0(void *packet, void *value)
{
    register void *result asm("$2");

    if (D_800B0C62 >= 2) {
        D_800B0C5C(&D_800C4C54, packet, value);
    }

    D_800B0C58->submit(packet, value);

    asm volatile(
        "lui $6,0x00FF\n\t"
        "ori $6,$6,0xFFFF\n\t"
        "addu %0,%1,$zero\n\t"
        "lui $5,%%hi(D_800B0D20)\n\t"
        "addiu $5,$5,%%lo(D_800B0D20)\n\t"
        "lui $3,%%hi(D_800B0D0C)\n\t"
        "addiu $3,$3,%%lo(D_800B0D0C)\n\t"
        "and $3,$3,$6\n\t"
        "lui $4,0x0400\n\t"
        "or $3,$3,$4\n\t"
        "sw $3,0($5)\n\t"
        "and $5,$5,$6\n\t"
        "sw $5,0(%0)"
        : "=r"(result)
        : "r"(packet)
        : "$3", "$4", "$5", "$6", "memory");
    return result;
}
