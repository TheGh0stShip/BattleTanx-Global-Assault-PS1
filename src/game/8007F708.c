asm(".text\n\t.set noreorder\n\t.globl func_8007F708\nfunc_8007F708:\n\t"
    "lui $3,0x800F\n\taddiu $3,$3,-0x3CCC\n\tlw $2,0x14($3)\n\tnop\n\t"
    ".word 0x00A2001B\n\t.word 0x14400002\n\tnop\n\t.word 0x0007000D\n\t"
    "mflo $5\n\tsw $4,8($3)\n\taddiu $2,$0,-4\n\tand $5,$5,$2\n\t"
    "jr $31\n\tsw $5,0x10($3)");
