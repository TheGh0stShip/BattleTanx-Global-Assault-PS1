typedef unsigned int u32;

extern volatile u32 *D_800B8BA4;
extern volatile u32 *D_800B8B80;
extern volatile u32 *D_800B8B78;
extern volatile u32 *D_800B8B7C;
extern void func_8009C88C(void *source, u32 value);

void func_8009C76C(void *source, u32 value)
{
    register void *saved_source asm("$17") = source;
    register u32 packed asm("$16") = value;

    func_8009C88C(saved_source, packed);
    asm volatile(
        "lui $3,%%hi(D_800B8BA4)\n\t"
        "lw $3,%%lo(D_800B8BA4)($3)\n\t"
        "nop\n\t"
        "lw $2,0($3)\n\t"
        "srl %1,%1,5\n\t"
        "ori $2,$2,0x88\n\t"
        "sw $2,0($3)\n\t"
        "lui $2,%%hi(D_800B8B80)\n\t"
        "lw $2,%%lo(D_800B8B80)($2)\n\t"
        "sll %1,%1,16\n\t"
        "sw $zero,0($2)\n\t"
        "lui $2,%%hi(D_800B8B78)\n\t"
        "lw $2,%%lo(D_800B8B78)($2)\n\t"
        "ori %1,%1,0x20\n\t"
        "sw %0,0($2)\n\t"
        "lui $2,%%hi(D_800B8B7C)\n\t"
        "lw $2,%%lo(D_800B8B7C)($2)\n\t"
        "lui $3,0x0100\n\t"
        "sw %1,0($2)\n\t"
        "lui $2,%%hi(D_800B8B80)\n\t"
        "lw $2,%%lo(D_800B8B80)($2)\n\t"
        "ori $3,$3,0x0200\n\t"
        "sw $3,0($2)"
        : "+r"(saved_source), "+r"(packed)
        :
        : "$2", "$3", "memory");
}
