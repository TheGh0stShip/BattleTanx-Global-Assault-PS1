/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_80098C30
.ent func_80098C30
func_80098C30:
    lui	$at,0x800f
    sw	$ra,-3820($at)
    jal	func_80094198
    nop
    addiu	$t1,$zero,86
    addiu	$t2,$zero,176
    jalr	$t2
    nop
    lw	$v0,24($v0)
    nop
    addiu	$v0,$v0,40
    addu	$t7,$v0,$zero
    lui	$t2,0x800a
    addiu	$t2,$t2,-29476
    lui	$t1,0x800a
    addiu	$t1,$t1,-29452
L_80098C70:
    lw	$v1,0($t2)
    lw	$t3,0($v0)
    addiu	$t2,$t2,4
    bne	$v1,$t3,L_80098CB8
    addiu	$v0,$v0,4
    bne	$t2,$t1,L_80098C70
    nop
    addu	$v0,$t7,$zero
    lui	$t2,0x800a
    addiu	$t2,$t2,-29452
    lui	$t1,0x800a
    addiu	$t1,$t1,-29428
L_80098CA0:
    lw	$v1,0($t2)
    nop
    sw	$v1,0($v0)
    addiu	$t2,$t2,4
    bne	$t2,$t1,L_80098CA0
    addiu	$v0,$v0,4
L_80098CB8:
    jal	func_800A1910
    nop
    jal	func_80094168
    nop
    lui	$ra,0x800f
    lw	$ra,-3820($ra)
    nop
    jr	$ra
    nop
    sw	$at,4($k0)
    sw	$v0,8($k0)
    sw	$v1,12($k0)
    sw	$ra,124($k0)
    mfc0	$v1,$14
    nop
    sw	$at,4($k0)
    sw	$v0,8($k0)
    mfc0	$v0,$13
    sw	$v1,12($k0)
    mfc0	$v1,$14
    sw	$ra,124($k0)
.end func_80098C30
