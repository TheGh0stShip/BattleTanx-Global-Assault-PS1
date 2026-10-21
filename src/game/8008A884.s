/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8008A884
.ent func_8008A884
func_8008A884:
    sltu	$at,$a1,$a0
    beqz	$at,func_8008A7BC
    add	$t0,$a1,$a2
    sltu	$at,$a0,$t0
    beqz	$at,func_8008A7BC
    nop
    beqz	$a0,L_8008A96C
    addu	$v0,$a0,$zero
    beqz	$a1,L_8008A96C
    nop
    beqz	$a2,L_8008A96C
    addu	$a0,$a0,$a2
    addu	$a1,$a1,$a2
    addiu	$t0,$zero,7
    slt	$at,$t0,$a2
    beqz	$at,L_8008A950
    andi	$t0,$a0,0x3
    beqz	$t0,L_8008A8EC
    subu	$a2,$a2,$t0
L_8008A8D0:
    addiu	$a1,$a1,-1
    lb	$t1,0($a1)
    addiu	$a0,$a0,-1
    sb	$t1,0($a0)
    addiu	$t0,$t0,-1
    bnez	$t0,L_8008A8D0
    nop
L_8008A8EC:
    srl	$t0,$a2,0x2
    andi	$t1,$a1,0x3
    bnez	$t1,L_8008A928
    andi	$a2,$a2,0x3
L_8008A8FC:
    addiu	$a1,$a1,-4
    lw	$t1,0($a1)
    addiu	$a0,$a0,-4
    sw	$t1,0($a0)
    addiu	$t0,$t0,-1
    bnez	$t0,L_8008A8FC
    nop
    beqz	$a2,L_8008A96C
    nop
    bgez	$zero,L_8008A950
    nop
L_8008A928:
    addiu	$a1,$a1,-4
    lwr	$t1,0($a1)
    lwl	$t1,3($a1)
    addiu	$a0,$a0,-4
    sw	$t1,0($a0)
    addiu	$t0,$t0,-1
    bnez	$t0,L_8008A928
    nop
    beqz	$a2,L_8008A96C
    nop
L_8008A950:
    addiu	$a1,$a1,-1
    lb	$t0,0($a1)
    addiu	$a0,$a0,-1
    sb	$t0,0($a0)
    addiu	$a2,$a2,-1
    bnez	$a2,L_8008A950
    nop
L_8008A96C:
    jr	$ra
    nop
.end func_8008A884
