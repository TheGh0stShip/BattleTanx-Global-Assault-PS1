/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_800A4210
.ent func_800A4210
func_800A4210:
    lui	$at,0x800f
    sw	$ra,-428($at)
    jal	func_80094198
    nop
    addiu	$t1,$zero,87
    addiu	$t2,$zero,176
    jalr	$t2
    nop
    lw	$v0,364($v0)
    nop
    lw	$v1,2504($v0)
    lui	$t2,0x800a
    addiu	$t2,$t2,16744
    lui	$t1,0x800a
    addiu	$t1,$t1,16764
L_800A424C:
    lw	$t0,0($t2)
    nop
    sw	$t0,2504($v0)
    addiu	$t2,$t2,4
    bne	$t2,$t1,L_800A424C
    addiu	$v0,$v0,4
    jal	func_800A1910
    nop
    lui	$ra,0x800f
    lw	$ra,-428($ra)
    nop
    jr	$ra
    nop
.end func_800A4210
