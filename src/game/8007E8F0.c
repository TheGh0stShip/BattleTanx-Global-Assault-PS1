extern unsigned int D_8007E90C;

void func_8007E8F0(void)
{
    asm volatile(
        "lui $24,%%hi(D_8007E90C)\n\t"
        "addiu $24,$24,%%lo(D_8007E90C)\n\t"
        "mfc0 $8,$14\n\t"
        "nop\n\t"
        "sw $8,0($24)"
        :
        :
        : "$8", "$24", "memory"
    );
}
