asm(".text\n\t.set noreorder\n\t.globl func_80049790\nfunc_80049790:\n\t"
    "addiu $29,$29,-0x18\n\tsw $16,0x10($29)\n\taddu $16,$4,$0\n\tsw $31,0x14($29)\n\t"
    "lw $6,0($16)\n\tlw $2,8($16)\n\taddu $7,$6,$0\n\tmult $6,$7\n\t"
    "mflo $3\n\tmfhi $4\n\tsrl $3,$3,12\n\tsll $4,$4,20\n\tor $3,$3,$4\n\t"
    "mult $2,$2\n\tmflo $4\n\tmfhi $6\n\tsrl $4,$4,12\n\tsll $6,$6,20\n\t"
    "or $4,$4,$6\n\t.word 0x0C022AFC\n\taddu $4,$3,$4\n\t.word 0x18400007\n\t"
    "addu $2,$0,$0\n\tlw $4,0($16)\n\tlw $5,8($16)\n\t.word 0x0C022B8C\n\t"
    "nop\n\tandi $2,$2,0xFFF\n\tsll $2,$2,4\n\tlw $31,0x14($29)\n\t"
    "lw $16,0x10($29)\n\tjr $31\n\taddiu $29,$29,0x18");
