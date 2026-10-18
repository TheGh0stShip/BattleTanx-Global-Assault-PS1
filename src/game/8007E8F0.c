asm(".text\n\t.set noreorder\n\t.globl func_8007E8F0\nfunc_8007E8F0:\n\t"
    "lui $24,%hi(D_8007E90C)\n\taddiu $24,$24,%lo(D_8007E90C)\n\t"
    "mfc0 $8,$14\n\tnop\n\tsw $8,0($24)\n\tjr $31\n\tnop");
