asm(".text\n\t.set noreorder\n\t.globl func_8007FA74\nfunc_8007FA74:\n\t"
    "lui $2,0x800B\n\tlbu $2,0xC62($2)\n\taddiu $29,$29,-0x18\n\t"
    "sw $16,0x10($29)\n\taddu $16,$4,$0\n\tsltiu $2,$2,2\n\t"
    ".word 0x14400008\n\tsw $31,0x14($29)\n\tlui $4,0x800C\n\t"
    "addiu $4,$4,0x4BC8\n\tlui $2,0x800B\n\tlw $2,0xC5C($2)\n\tnop\n\t"
    "jalr $2\n\taddu $5,$16,$0\n\tlui $2,0x800B\n\tlw $2,0xC58($2)\n\t"
    "nop\n\tlw $2,0x3C($2)\n\tnop\n\tjalr $2\n\taddu $4,$16,$0\n\t"
    "lw $31,0x14($29)\n\tlw $16,0x10($29)\n\tjr $31\n\taddiu $29,$29,0x18");
