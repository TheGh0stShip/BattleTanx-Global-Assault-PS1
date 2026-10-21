/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8008A974
.ent func_8008A974
func_8008A974:
    beqz	$a0,L_8008AA38
    addu	$v0,$zero,$zero
    beqz	$a2,L_8008AA38
    andi	$a1,$a1,0xff
    addiu	$t0,$zero,7
    slt	$at,$t0,$a2
    beqz	$at,L_8008AA20
    andi	$t0,$a0,0x3
    beqz	$t0,L_8008A9BC
    addiu	$t1,$zero,4
    subu	$t0,$t1,$t0
    subu	$a2,$a2,$t0
L_8008A9A4:
    lbu	$t1,0($a0)
    nop
    beq	$t1,$a1,L_8008AA40
    addiu	$t0,$t0,-1
    bnez	$t0,L_8008A9A4
    addi	$a0,$a0,1
L_8008A9BC:
    addu	$t2,$a1,$zero
    addiu	$t1,$zero,255
    srl	$t0,$a2,0x2
    andi	$a2,$a2,0x3
L_8008A9CC:
    lw	$t3,0($a0)
    nop
    and	$t4,$t3,$t1
    beq	$t4,$t2,L_8008AA40
    srl	$t3,$t3,0x8
    addi	$a0,$a0,1
    and	$t4,$t3,$t1
    beq	$t4,$t2,L_8008AA40
    srl	$t3,$t3,0x8
    addi	$a0,$a0,1
    and	$t4,$t3,$t1
    beq	$t4,$t2,L_8008AA40
    srl	$t3,$t3,0x8
    addi	$a0,$a0,1
    and	$t4,$t3,$t1
    beq	$t4,$t2,L_8008AA40
    addiu	$t0,$t0,-1
    bnez	$t0,L_8008A9CC
    addi	$a0,$a0,1
    beqz	$a2,L_8008AA38
    nop
L_8008AA20:
    lbu	$t1,0($a0)
    nop
    beq	$t1,$a1,L_8008AA40
    addiu	$a2,$a2,-1
    bnez	$a2,L_8008AA20
    addi	$a0,$a0,1
L_8008AA38:
    jr	$ra
    nop
L_8008AA40:
    jr	$ra
    addu	$v0,$a0,$zero
.end func_8008A974
