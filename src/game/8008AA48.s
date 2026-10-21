/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8008AA48
.ent func_8008AA48
func_8008AA48:
    beqz	$a0,L_8008AAC8
    addu	$v0,$a0,$zero
    beqz	$a2,L_8008AAC8
    addiu	$t0,$zero,7
    slt	$at,$t0,$a2
    beqz	$at,L_8008AAB8
    andi	$t0,$a0,0x3
    beqz	$t0,L_8008AA84
    addiu	$t1,$zero,4
    subu	$t0,$t1,$t0
    subu	$a2,$a2,$t0
L_8008AA74:
    sb	$a1,0($a0)
    addiu	$t0,$t0,-1
    bnez	$t0,L_8008AA74
    addi	$a0,$a0,1
L_8008AA84:
    andi	$a1,$a1,0xff
    sll	$t0,$a1,0x8
    or	$a1,$t0,$a1
    sll	$t0,$a1,0x10
    or	$a1,$t0,$a1
    srl	$t0,$a2,0x2
    andi	$a2,$a2,0x3
L_8008AAA0:
    sw	$a1,0($a0)
    addiu	$t0,$t0,-1
    bnez	$t0,L_8008AAA0
    addi	$a0,$a0,4
    beqz	$a2,L_8008AAC8
    nop
L_8008AAB8:
    sb	$a1,0($a0)
    addiu	$a2,$a2,-1
    bnez	$a2,L_8008AAB8
    addi	$a0,$a0,1
L_8008AAC8:
    jr	$ra
    nop
.end func_8008AA48
