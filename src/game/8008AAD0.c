asm(".text\n\t.set noreorder\n\t.globl func_8008AAD0\nfunc_8008AAD0:\n\t"
    "lw $8,0($4)\n\tlw $9,4($4)\n\tlw $10,8($4)\n\taddu $7,$31,$0\n\t"
    ".word 0x0C022ACC\n\tnop\n\tsw $8,0($5)\n\tsw $9,4($5)\n\t"
    "sw $10,8($5)\n\taddu $31,$7,$0\n\tjr $31\n\tnop");
