asm(".text\n\t.set noreorder\n\t.globl func_80081368\nfunc_80081368:\n\t"
    "addiu $29,$29,-0x18\n\tsw $31,0x10($29)\n\taddu $7,$6,$0\n\t"
    ".word 0x0C0204E3\n\taddu $6,$0,$0\n\tlw $31,0x10($29)\n\t"
    "addiu $29,$29,0x18\n\tjr $31\n\tnop");
