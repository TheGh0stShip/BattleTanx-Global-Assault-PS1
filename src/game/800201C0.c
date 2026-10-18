asm(".text\n\t.set noreorder\n\t.globl func_800201C0\nfunc_800201C0:\n\t"
    "addiu $29,$29,-0x30\n\taddiu $4,$0,0x10\n\tsw $31,0x28($29)\n\t"
    ".word 0x0C007CCC\n\taddu $5,$29,$4\n\t.word 0x0C007DB5\n\t"
    "addiu $4,$29,0x10\n\taddu $4,$2,$0\n\t.word 0x0C007E36\n\t"
    "addiu $5,$29,0x10\n\tlw $31,0x28($29)\n\tnop\n\tjr $31\n\t"
    "addiu $29,$29,0x30");
