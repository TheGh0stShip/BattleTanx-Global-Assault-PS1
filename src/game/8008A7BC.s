/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8008A7BC
.ent func_8008A7BC
func_8008A7BC:
    beqz	$a0,L_8008A87C
    addu	$v0,$a0,$zero
    beqz	$a1,L_8008A87C
    nop
    beqz	$a2,L_8008A87C
    addiu	$t0,$zero,7
    slt	$at,$t0,$a2
    beqz	$at,L_8008A864
    andi	$t0,$a0,0x3
    beqz	$t0,L_8008A808
    addiu	$t1,$zero,4
    subu	$t0,$t1,$t0
    subu	$a2,$a2,$t0
L_8008A7F0:
    lb	$t1,0($a1)
    addi	$a1,$a1,1
    sb	$t1,0($a0)
    addiu	$t0,$t0,-1
    bnez	$t0,L_8008A7F0
    addi	$a0,$a0,1
L_8008A808:
    srl	$t0,$a2,0x2
    andi	$t1,$a1,0x3
    bnez	$t1,L_8008A840
    andi	$a2,$a2,0x3
L_8008A818:
    lw	$t1,0($a1)
    addi	$a1,$a1,4
    sw	$t1,0($a0)
    addiu	$t0,$t0,-1
    bnez	$t0,L_8008A818
    addi	$a0,$a0,4
    beqz	$a2,L_8008A87C
    nop
    bgez	$zero,L_8008A864
    nop
L_8008A840:
    lwr	$t1,0($a1)
    lwl	$t1,3($a1)
    addi	$a1,$a1,4
    sw	$t1,0($a0)
    addiu	$t0,$t0,-1
    bnez	$t0,L_8008A840
    addi	$a0,$a0,4
    beqz	$a2,L_8008A87C
    nop
L_8008A864:
    lb	$t0,0($a1)
    addi	$a1,$a1,1
    sb	$t0,0($a0)
    addiu	$a2,$a2,-1
    bnez	$a2,L_8008A864
    addi	$a0,$a0,1
L_8008A87C:
    jr	$ra
    nop
.end func_8008A7BC
