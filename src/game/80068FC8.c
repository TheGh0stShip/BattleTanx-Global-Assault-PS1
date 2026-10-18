asm(".text\n\t.set noreorder\n\t.globl func_80068FC8\nfunc_80068FC8:\n\t"
    "addiu $29,$29,-0x18\n\tsw $16,0x10($29)\n\taddu $16,$4,$0\n\tlui $3,0x800B\n\t"
    "lw $2,-0x22FC($3)\n\taddiu $4,$0,-1\n\tsw $31,0x14($29)\n\taddiu $2,$2,1\n\t"
    ".word 0x0C0217D7\n\tsw $2,-0x22FC($3)\n\taddiu $4,$0,-1\n\tlui $3,0x800E\n\t"
    "addu $5,$16,$0\n\t.word 0x0C021612\n\tsw $2,0x53F0($3)\n\taddu $3,$2,$0\n\t"
    "ori $2,$0,0xEA5F\n\tsltu $2,$2,$3\n\t.word 0x14400003\n\taddu $2,$3,$0\n\t"
    ".word 0x0801A406\n\tnop\n\tlw $31,0x14($29)\n\tlw $16,0x10($29)\n\t"
    "jr $31\n\taddiu $29,$29,0x18");
