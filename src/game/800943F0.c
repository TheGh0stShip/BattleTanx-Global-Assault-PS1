asm(".text\n\t.set noreorder\n\t.globl func_800943F0\nfunc_800943F0:\n\t"
    "lui $2,0x800B\n\tlw $2,0x6B00($2)\n\taddiu $29,$29,-0x18\n\t"
    "sw $31,0x10($29)\n\tlw $2,0x0C($2)\n\tnop\n\tjalr $2\n\tnop\n\t"
    "lw $31,0x10($29)\n\taddiu $29,$29,0x18\n\tjr $31\n\tnop");
