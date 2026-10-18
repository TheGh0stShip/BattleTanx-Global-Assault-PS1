asm(".text\n\t.set noreorder\n\t.globl func_80094480\nfunc_80094480:\n\t"
    "addiu $29,$29,-0x18\n\tlui $2,0x800B\n\tlw $2,0x6B00($2)\n\t"
    "addu $5,$4,$0\n\tsw $31,0x10($29)\n\tlw $2,0x14($2)\n\tnop\n\t"
    "jalr $2\n\taddiu $4,$0,4\n\tlw $31,0x10($29)\n\t"
    "addiu $29,$29,0x18\n\tjr $31\n\tnop");
