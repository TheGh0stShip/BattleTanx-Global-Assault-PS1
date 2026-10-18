asm(".text\n\t.set noreorder\n\t.globl func_8006AD84\nfunc_8006AD84:\n\t"
    "addiu $29,$29,-0x18\n\t.word 0x10800008\n\tsw $31,0x10($29)\n\t"
    ".word 0x0C024F57\n\tnop\n\tlui $6,0x8007\n\taddu $4,$2,$0\n\t"
    "addu $5,$0,$0\n\t.word 0x0C024EDF\n\taddiu $6,$6,-0x527C\n\t"
    "lw $31,0x10($29)\n\tnop\n\tjr $31\n\taddiu $29,$29,0x18");
