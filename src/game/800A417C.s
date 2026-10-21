/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_800A417C
.ent func_800A417C
func_800A417C:
    lui	$at,0x800f
    sw	$ra,-428($at)
    jal	func_80094198
    nop
    addiu	$t1,$zero,86
    addiu	$t2,$zero,176
    jalr	$t2
    nop
    lw	$v0,24($v0)
    nop
    lw	$v1,112($v0)
    nop
    andi	$t1,$v1,0xffff
    sll	$t1,$t1,0x10
    lw	$v1,116($v0)
    nop
    andi	$t2,$v1,0xffff
    addu	$v1,$t1,$t2
    addiu	$v0,$v1,40
    lui	$t2,0x800a
    addiu	$t2,$t2,16724
    lui	$t1,0x800a
    addiu	$t1,$t1,16744
L_800A41D8:
    lw	$v1,0($t2)
    nop
    sw	$v1,0($v0)
    addiu	$t2,$t2,4
    bne	$t2,$t1,L_800A41D8
    addiu	$v0,$v0,4
    lui	$at,0x1
    jal	func_800A1910
    sw	$v0,-8196($at)
    lui	$ra,0x800f
    lw	$ra,-428($ra)
    nop
    jr	$ra
    nop
.end func_800A417C
