asm(".text\n\t.set noreorder\n\t.globl func_8008AD60\nfunc_8008AD60:\n\t"
    "addiu $29,$29,-0x18\n\t.word 0x04800005\n\tsw $31,0x10($29)\n\t"
    ".word 0x0C022B67\n\tandi $4,$4,0xFFF\n\t.word 0x08022B63\n\tnop\n\t"
    "subu $4,$0,$4\n\t.word 0x0C022B67\n\tandi $4,$4,0xFFF\n\tsubu $2,$0,$2\n\t"
    "lw $31,0x10($29)\n\taddiu $29,$29,0x18\n\tjr $31\n\tnop");
