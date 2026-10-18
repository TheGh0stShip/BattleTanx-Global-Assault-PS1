asm(".text\n\t.set noreorder\n\t.globl func_800861B8\nfunc_800861B8:\n\t"
    "sltu $8,$4,$5\n\t.word 0x10080005\n\taddi $5,$5,-4\n"
    "sw $6,0($4)\n\tsltu $8,$4,$5\n\t.word 0x1408FFFD\n\taddi $4,$4,4\n"
    "2:\n\tjr $31\n\tnop");
