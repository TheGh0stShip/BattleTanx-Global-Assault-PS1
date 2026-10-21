/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8008BDF0
.ent func_8008BDF0
func_8008BDF0:
    addiu	$sp,$sp,-36
    sw	$s0,16($sp)
    sw	$s1,20($sp)
    sw	$s2,24($sp)
    sw	$ra,28($sp)
    addiu	$sp,$sp,-40
    sw	$a0,16($sp)
    sw	$a1,20($sp)
    sw	$a2,24($sp)
    sw	$a3,28($sp)
    sw	$ra,32($sp)
    jal	func_8003BD84
    nop
    add	$s0,$zero,$v0
    jal	func_8003BD94
    nop
    add	$s1,$zero,$v0
    jal	func_8003BDA4
    nop
    add	$s2,$zero,$v0
    lw	$a0,16($sp)
    lw	$a1,20($sp)
    lw	$a2,24($sp)
    lw	$a3,28($sp)
    lw	$ra,32($sp)
    addiu	$sp,$sp,40
    sub	$t0,$a1,$s0
    blez	$t0,L_8008BF60
    mtc2	$s1,$8
    mtc2	$t0,$9
    sll	$t0,$a0,0x4
    andi	$t0,$t0,0xff0
    c2	0x198003d
    srl	$t1,$a0,0x4
    andi	$t1,$t1,0xff0
    srl	$t2,$a0,0xc
    andi	$t2,$t2,0xff0
    mfc2	$t3,$25
    srl	$t5,$s2,0xc
    andi	$t5,$t5,0xff0
    addi	$t4,$t3,-4096
    blez	$t4,L_8008BEA0
    srl	$t4,$s2,0x4
    addiu	$t3,$zero,4096
L_8008BEA0:
    mtc2	$t3,$8
    sll	$t3,$s2,0x4
    andi	$t3,$t3,0xff0
    andi	$t4,$t4,0xff0
    sub	$t0,$t3,$t0
    sub	$t1,$t4,$t1
    sub	$t2,$t5,$t2
    andi	$t3,$t0,0x8000
    beqz	$t3,L_8008BECC
    andi	$t4,$t1,0x8000
    sub	$t0,$zero,$t0
L_8008BECC:
    beqz	$t4,L_8008BED8
    andi	$t5,$t2,0x8000
    sub	$t1,$zero,$t1
L_8008BED8:
    beqz	$t5,L_8008BEE4
    nop
    sub	$t2,$zero,$t2
L_8008BEE4:
    mtc2	$t0,$9
    mtc2	$t1,$10
    mtc2	$t2,$11
    nop
    nop
    c2	0x198003d
    srl	$t8,$a0,0x10
    sll	$t8,$t8,0x10
    andi	$t7,$a0,0xff00
    andi	$t6,$a0,0xff
    mfc2	$t0,$22
    nop
    nop
    srl	$t2,$t0,0x10
    sll	$t2,$t2,0x10
    andi	$t1,$t0,0xff00
    andi	$t0,$t0,0xff
    beqz	$t3,L_8008BF38
    add	$t6,$t6,$t0
    sub	$t6,$t6,$t0
    sub	$t6,$t6,$t0
L_8008BF38:
    beqz	$t4,L_8008BF48
    add	$t7,$t7,$t1
    sub	$t7,$t7,$t1
    sub	$t7,$t7,$t1
L_8008BF48:
    beqz	$t5,L_8008BF58
    add	$t8,$t8,$t2
    sub	$t8,$t8,$t2
    sub	$t8,$t8,$t2
L_8008BF58:
    or	$t6,$t6,$t7
    or	$a0,$t6,$t8
L_8008BF60:
    lw	$s0,16($sp)
    lw	$s1,20($sp)
    lw	$s2,24($sp)
    lw	$ra,28($sp)
    addiu	$sp,$sp,36
    jr	$ra
    sw	$a0,0($a2)
.end func_8008BDF0
