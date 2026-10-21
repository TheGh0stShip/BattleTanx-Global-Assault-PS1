/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8008ABF0
.ent func_8008ABF0
func_8008ABF0:
    mtc2	$a0,$30
    nop
    nop
    mfc2	$v0,$31
    addiu	$at,$zero,32
    beq	$v0,$at,L_8008AC7C
    nop
    andi	$t0,$v0,0x1
    addiu	$at,$zero,-2
    and	$t2,$v0,$at
    addiu	$t1,$zero,19
    sub	$t1,$t1,$t2
    sra	$t1,$t1,0x1
    addi	$t3,$t2,-24
    bltz	$t3,L_8008AC38
    nop
    sllv	$t4,$a0,$t3
    b	L_8008AC44
L_8008AC38:
    addiu	$t3,$zero,24
    sub	$t3,$t3,$t2
    srav	$t4,$a0,$t3
L_8008AC44:
    addi	$t4,$t4,-64
    sll	$t4,$t4,0x1
    lui	$t5,0x800b
    addu	$t5,$t5,$t4
    lh	$t5,27960($t5)
    nop
    bltz	$t1,L_8008AC70
    nop
    sllv	$v0,$t5,$t1
    jr	$ra
    nop
L_8008AC70:
    sub	$t1,$zero,$t1
    jr	$ra
    srlv	$v0,$t5,$t1
L_8008AC7C:
    jr	$ra
    addiu	$v0,$zero,0
.end func_8008ABF0
