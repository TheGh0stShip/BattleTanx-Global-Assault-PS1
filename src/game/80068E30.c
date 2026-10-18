asm(".text\n\t.set noreorder\n\t.globl func_80068E30\nfunc_80068E30:\n\t"
    "addiu $29,$29,-0x18\n\tsw $31,0x14($29)\n\t.word 0x0C01A39C\n\tsw $16,0x10($29)\n\t"
    "lui $16,0x800B\n\t.word 0x0C0217D7\n\taddiu $4,$0,-1\n\tlui $3,0x800B\n\t"
    "sw $2,-0x22F4($16)\n\tlui $2,0x800B\n\tlw $31,0x14($29)\n\tlw $16,0x10($29)\n\t"
    "addiu $2,$2,-0x2308\n\tsw $2,-0x2300($3)\n\tjr $31\n\taddiu $29,$29,0x18");
