typedef unsigned int u32;

extern volatile u32 *D_800B8BA4;
extern volatile u32 *D_800B8B6C;
extern volatile u32 *D_800B8B70;
extern volatile u32 *D_800B8B9C;
extern volatile u32 *D_800B8B74;
extern void func_8009C7F8(void *source, u32 value);

void func_8009C6DC(void *source, u32 value)
{
    register void *saved_source asm("$17") = source;
    register u32 packed asm("$16") = value;

    func_8009C7F8(saved_source, packed);
    asm volatile(
        "lui $3,%%hi(D_800B8BA4)\n\t"
        "lw $3,%%lo(D_800B8BA4)($3)\n\t"
        "srl %1,%1,5\n\t"
        "lw $2,0($3)\n\t"
        "sll %1,%1,16\n\t"
        "ori $2,$2,0x88\n\t"
        "sw $2,0($3)\n\t"
        "lui $3,%%hi(D_800B8B6C)\n\t"
        "lw $3,%%lo(D_800B8B6C)($3)\n\t"
        "addiu $2,%0,4\n\t"
        "sw $2,0($3)\n\t"
        "lui $2,%%hi(D_800B8B70)\n\t"
        "lw $2,%%lo(D_800B8B70)($2)\n\t"
        "ori %1,%1,0x20\n\t"
        "sw %1,0($2)\n\t"
        "lui $3,%%hi(D_800B8B9C)\n\t"
        "lw $3,%%lo(D_800B8B9C)($3)\n\t"
        "lw $2,0(%0)\n\t"
        "lui $4,0x0100\n\t"
        "sw $2,0($3)\n\t"
        "lui $2,%%hi(D_800B8B74)\n\t"
        "lw $2,%%lo(D_800B8B74)($2)\n\t"
        "ori $4,$4,0x0201\n\t"
        "sw $4,0($2)"
        : "+r"(saved_source), "+r"(packed)
        :
        : "$2", "$3", "$4", "memory");
}
