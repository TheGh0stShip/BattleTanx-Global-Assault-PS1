/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8008BCD4
.ent func_8008BCD4
func_8008BCD4:
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
    blez	$t0,L_8008BDD0
    add	$t4,$zero,$zero
    mtc2	$s1,$8
    mtc2	$t0,$9
    sll	$t0,$a0,0x4
    andi	$t0,$t0,0xff0
    c2	0x198003d
    srl	$t1,$a0,0x4
    andi	$t1,$t1,0xff0
    srl	$t2,$a0,0xc
    andi	$t2,$t2,0xff0
    mtc2	$t0,$9
    mtc2	$t1,$10
    mtc2	$t2,$11
    mfc2	$t3,$25
    addiu	$t1,$zero,4096
    sub	$t1,$t1,$t3
    mtc2	$t1,$8
    sll	$t0,$s2,0x4
    andi	$t0,$t0,0xff0
    c2	0x198003d
    srl	$t1,$s2,0x4
    andi	$t1,$t1,0xff0
    srl	$t2,$s2,0xc
    andi	$t2,$t2,0xff0
    mtc2	$t0,$9
    mtc2	$t1,$10
    mtc2	$t2,$11
    mfc2	$a0,$22
    mtc2	$t3,$8
    nop
    nop
    c2	0x198003d
    mfc2	$t4,$22
    nop
    nop
L_8008BDD0:
    sw	$t4,0($a3)
    lw	$s0,16($sp)
    lw	$s1,20($sp)
    lw	$s2,24($sp)
    lw	$ra,28($sp)
    addiu	$sp,$sp,36
    jr	$ra
    sw	$a0,0($a2)
.end func_8008BCD4
