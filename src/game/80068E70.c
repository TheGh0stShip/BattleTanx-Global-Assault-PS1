asm(".text\n\t.set noreorder\n\t.globl func_80068E70\nfunc_80068E70:\n\t"
    "lui $2,0x800B\n\tlw $2,-0x2300($2)\n\taddiu $29,$29,-0x20\n\tsw $31,0x1C($29)\n\t"
    "sw $18,0x18($29)\n\tsw $17,0x14($29)\n\t.word 0x1040000F\n\tsw $16,0x10($29)\n\t"
    "addu $18,$2,$0\n\tlw $4,4($18)\n\tnop\n\t.word 0x10800009\n\t"
    "lui $17,0x800B\n\tlw $16,4($4)\n\t.word 0x0C021775\n\tnop\n\t"
    "lw $2,-0x22FC($17)\n\taddu $4,$16,$0\n\taddiu $2,$2,-1\n\t.word 0x1480FFF9\n\t"
    "sw $2,-0x22FC($17)\n\tsw $0,4($18)\n\t.word 0x0C0217D7\n\taddiu $4,$0,-1\n\t"
    "lw $31,0x1C($29)\n\tlw $18,0x18($29)\n\tlw $17,0x14($29)\n\tlw $16,0x10($29)\n\t"
    "jr $31\n\taddiu $29,$29,0x20");
