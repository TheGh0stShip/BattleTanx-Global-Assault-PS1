asm(".text\n\t.set noreorder\n\t.globl func_8007F980\nfunc_8007F980:\n\t"
    "addiu $29,$29,-0x18\n\tlui $3,0x800B\n\taddiu $3,$3,0xC62\n\t"
    "sw $31,0x14($29)\n\tsw $16,0x10($29)\n\tlbu $16,0($3)\n\t"
    "sb $4,0($3)\n\tandi $4,$4,0xFF\n\t.word 0x1080000A\n\taddu $2,$16,$0\n\t"
    "lui $2,0x800B\n\tlw $2,0xC5C($2)\n\tlbu $5,0($3)\n\t"
    "lbu $6,-2($3)\n\tlbu $7,1($3)\n\tlui $4,0x800C\n\tjalr $2\n\t"
    "addiu $4,$4,0x4B58\n\taddu $2,$16,$0\n\tlw $31,0x14($29)\n\t"
    "lw $16,0x10($29)\n\tjr $31\n\taddiu $29,$29,0x18");
