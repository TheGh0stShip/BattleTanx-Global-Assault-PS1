asm(".text\n\t.set noreorder\n\t.globl func_8007F740\nfunc_8007F740:\n\t"
    "lui $2,0x800F\n\taddiu $5,$2,-0x3CCC\n\tlw $3,0x10($5)\n\t"
    "lw $2,0x14($5)\n\tnop\n\tmult $3,$2\n\tmflo $2\n\t"
    ".word 0x14800002\n\tnop\n\taddiu $4,$0,1\n\t.word 0x0044001B\n\t"
    ".word 0x14800002\n\tnop\n\t.word 0x0007000D\n\tmflo $2\n\t"
    "sw $4,0x14($5)\n\tsw $0,0xC($5)\n\tjr $31\n\tsw $2,0x10($5)");
