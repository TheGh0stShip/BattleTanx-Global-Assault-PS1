/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8008AB30
.ent func_8008AB30
func_8008AB30:
    mtc2	$t0,$9
    mtc2	$t1,$10
    mtc2	$t2,$11
    nop
    c2	0xa00428
    mfc2	$t3,$25
    mfc2	$t4,$26
    mfc2	$t5,$27
    add	$t3,$t3,$t4
    add	$v0,$t3,$t5
    mtc2	$v0,$30
    nop
    nop
    mfc2	$v1,$31
    addiu	$at,$zero,-2
    and	$v1,$v1,$at
    addiu	$t6,$zero,31
    sub	$t6,$t6,$v1
    sra	$t6,$t6,0x1
    addi	$t3,$v1,-24
    bltz	$t3,L_8008AB90
    nop
    b	L_8008AB9C
    sllv	$t4,$v0,$t3
L_8008AB90:
    addiu	$t3,$zero,24
    sub	$t3,$t3,$v1
    srav	$t4,$v0,$t3
L_8008AB9C:
    addi	$t4,$t4,-64
    sll	$t4,$t4,0x1
    lui	$t5,0x800b
    addu	$t5,$t5,$t4
    lh	$t5,20224($t5)
    nop
    mtc2	$t5,$8
    mtc2	$t0,$9
    mtc2	$t1,$10
    mtc2	$t2,$11
    nop
    nop
    c2	0x190003d
    mfc2	$t0,$25
    mfc2	$t1,$26
    mfc2	$t2,$27
    srav	$t0,$t0,$t6
    srav	$t1,$t1,$t6
    srav	$t2,$t2,$t6
    jr	$ra
    nop
.end func_8008AB30
