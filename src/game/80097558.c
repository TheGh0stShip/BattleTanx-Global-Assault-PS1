asm(".text\n\t.set noreorder\n\t.globl func_80097558\nfunc_80097558:\n\t"
    "addiu $29,$29,-0x18\n\tsw $31,0x10($29)\n\taddu $5,$4,$0\n\t"
    ".word 0x0C025114\n\taddiu $4,$0,3\n\tlw $31,0x10($29)\n\t"
    "addiu $29,$29,0x18\n\tjr $31\n\tnop");
