asm(".text\n\t.set noreorder\n\t.globl func_800943B0\nfunc_800943B0:\n\t"
    "addiu $29,$29,-0x18\n\taddiu $2,$29,0x1C\n\tsw $4,0x18($29)\n\t"
    "addiu $4,$0,1\n\tsw $31,0x10($29)\n\tsw $5,0x1C($29)\n\t"
    "sw $6,4($2)\n\tsw $7,8($2)\n\tlw $5,0x18($29)\n\t"
    ".word 0x0C02742B\n\taddu $6,$2,$0\n\tlw $31,0x10($29)\n\t"
    "addiu $29,$29,0x18\n\tjr $31\n\tnop");
