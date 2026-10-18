asm(".text\n\t.set noreorder\n\t.globl func_80094D9C\nfunc_80094D9C:\n\t"
    "addiu $29,$29,-0x18\n\tsw $31,0x10($29)\n\tlui $1,0x800F\n\t"
    "sw $0,-0x0F70($1)\n\tlui $1,0x800F\n\t.word 0x0C025A04\n\t"
    "sw $0,-0x0F2C($1)\n\tlw $31,0x10($29)\n\taddiu $29,$29,0x18\n\t"
    "jr $31\n\tnop");
