asm(".text\n\t.set noreorder\n\t.globl func_80094044\nfunc_80094044:\n\t"
    ".word 0x10800019\n\taddu $2,$0,$0\n\t.word 0x10A00017\n\taddu $3,$0,$0\n\t"
    ".word 0x18C00014\n\taddu $7,$4,$0\n1:\n\tlbu $2,0($5)\n\taddiu $5,$5,1\n\t"
    "sb $2,0($4)\n\t.word 0x1440000B\n\taddiu $4,$4,1\n\t.word 0x08025021\n\taddiu $3,$3,1\n3:\n\t"
    "sb $0,0($4)\n\taddiu $4,$4,1\n\taddiu $3,$3,1\n4:\n\tslt $2,$3,$6\n\t"
    ".word 0x1440FFFB\n\taddu $2,$7,$0\n\t.word 0x0802502B\n\tnop\n6:\n\taddiu $3,$3,1\n\t"
    "slt $2,$3,$6\n\t.word 0x1440FFEE\n\tnop\n8:\n\taddu $2,$7,$0\n9:\n\tjr $31\n\tnop");
