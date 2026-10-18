asm(".text\n\t.set noreorder\n\t.globl func_8007EF30\nfunc_8007EF30:\n\t"
    "lui $2,0x800F\n\taddiu $3,$2,-0x3E00\n\tlw $2,0x108($3)\n\tnop\n\t"
    "xori $2,$2,2\n\t.word 0x10800003\n\tsltiu $5,$2,1\n\t.word 0x0801FBD6\n\t"
    "addiu $2,$0,2\n\taddiu $2,$0,1\n\tsw $2,0x108($3)\n\tjr $31\n\taddu $2,$5,$0");
