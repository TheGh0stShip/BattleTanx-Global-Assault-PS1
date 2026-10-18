asm(".text\n\t.set noreorder\n\t.globl func_8008AB00\nfunc_8008AB00:\n\t"
    "lh $8,0($4)\n\tlh $9,2($4)\n\tlh $10,4($4)\n\taddu $7,$31,$0\n\t"
    ".word 0x0C022ACC\n\tnop\n\tsh $8,0($5)\n\tsh $9,2($5)\n\t"
    "sh $10,4($5)\n\taddu $31,$7,$0\n\tjr $31\n\tnop");
