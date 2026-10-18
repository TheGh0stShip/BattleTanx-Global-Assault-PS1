asm(".text\n\t.set noreorder\n\t.globl func_80094DC8\nfunc_80094DC8:\n\t"
    "addiu $29,$29,-0x18\n\tsw $31,0x10($29)\n\t.word 0x0C027D67\n\tnop\n\t"
    "lui $2,0x800F\n\taddiu $2,$2,-0x0F6C\n\taddiu $3,$0,-1\n\t"
    "sw $0,0($2)\n\tsw $0,4($2)\n\tsw $0,8($2)\n\t.word 0x0C025A10\n\t"
    "sw $3,0x10($2)\n\tlui $5,0x8009\n\taddiu $5,$5,0x6690\n\t"
    ".word 0x0C02512D\n\taddiu $4,$0,7\n\tlw $31,0x10($29)\n\t"
    "addiu $29,$29,0x18\n\tjr $31\n\tnop");
