asm(".text\n\t.set noreorder\n\t.globl func_8005F8EC\nfunc_8005F8EC:\n\t"
    "lui $2,0x800B\n\tlhu $2,-0x531A($2)\n\taddiu $29,$29,-0x18\n\t"
    ".word 0x14400007\n\tsw $31,0x10($29)\n\tlui $3,0x800E\n\t"
    "addiu $2,$0,1\n\t.word 0x0C0166A0\n\tsh $2,0x4994($3)\n\t"
    ".word 0x08017E47\n\taddiu $2,$0,1\n\taddu $2,$0,$0\n\t"
    "lw $31,0x10($29)\n\tnop\n\tjr $31\n\taddiu $29,$29,0x18");
