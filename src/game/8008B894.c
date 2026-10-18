asm(".text\n\t.set noreorder\n\t.set noat\n\t.globl func_8008B894\nfunc_8008B894:\n\t"
    "lui $1,0x800B\n\tsw $31,0x58AC($1)\n\t.word 0x0C02630C\n\tnop\n\t"
    "lui $31,0x800B\n\tlw $31,0x58AC($31)\n\tnop\n\tmfc0 $2,$12\n\t"
    "lui $3,0x4000\n\tor $2,$2,$3\n\tmtc0 $2,$12\n\tnop\n\t"
    "addiu $8,$0,0x155\n\tctc2 $8,$29\n\tnop\n\taddiu $8,$0,0x100\n\t"
    "ctc2 $8,$30\n\tnop\n\taddiu $8,$0,0x3E8\n\tctc2 $8,$26\n\t"
    "nop\n\taddiu $8,$0,-0x1062\n\tctc2 $8,$27\n\tnop\n\t"
    "lui $8,0x140\n\tctc2 $8,$28\n\tnop\n\tctc2 $0,$24\n\t"
    "ctc2 $0,$25\n\tnop\n\tjr $31\n\tnop");
