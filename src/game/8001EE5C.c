asm(".text\n\t.set noreorder\n\t.globl func_8001EE5C\nfunc_8001EE5C:\n\t"
    "addiu $29,$29,-8\n\taddiu $5,$0,0x20\n\tlw $6,0($4)\n\tnop\n\t"
    "mtc2 $6,$30\n\tnop\n\tnop\n\tswc2 $31,0($29)\n\tlw $3,0($29)\n\tnop\n\t"
    "slt $2,$3,$5\n\t.word 0x10400002\n\tnop\n\taddu $5,$3,$0\n\tlw $4,4($4)\n\t"
    "nop\n\tmtc2 $4,$30\n\tnop\n\tnop\n\taddiu $2,$29,4\n\tswc2 $31,0($2)\n\t"
    "lw $3,4($29)\n\tnop\n\tslt $2,$3,$5\n\t.word 0x10400002\n\tnop\n\t"
    "addu $5,$3,$0\n\taddiu $3,$0,0x12\n\tsubu $3,$3,$5\n\t.word 0x1C600002\n\t"
    "addu $2,$3,$0\n\taddu $2,$0,$0\n\tjr $31\n\taddiu $29,$29,8");
