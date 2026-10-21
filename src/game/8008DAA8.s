/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8008DAA8
.ent func_8008DAA8
func_8008DAA8:
    lw	$t0,0($a0)
    lw	$t1,4($a0)
    lw	$t2,8($a0)
    bgez	$t0,L_8008DAD4
    nop
    negu	$t0,$t0
    sra	$t3,$t0,0xf
    negu	$t3,$t3
    andi	$t0,$t0,0x7fff
    b	L_8008DADC
    negu	$t0,$t0
L_8008DAD4:
    sra	$t3,$t0,0xf
    andi	$t0,$t0,0x7fff
L_8008DADC:
    bgez	$t1,L_8008DAFC
    nop
    negu	$t1,$t1
    sra	$t4,$t1,0xf
    negu	$t4,$t4
    andi	$t1,$t1,0x7fff
    b	L_8008DB04
    negu	$t1,$t1
L_8008DAFC:
    sra	$t4,$t1,0xf
    andi	$t1,$t1,0x7fff
L_8008DB04:
    bgez	$t2,L_8008DB24
    nop
    negu	$t2,$t2
    sra	$t5,$t2,0xf
    negu	$t5,$t5
    andi	$t2,$t2,0x7fff
    b	L_8008DB2C
    negu	$t2,$t2
L_8008DB24:
    sra	$t5,$t2,0xf
    andi	$t2,$t2,0x7fff
L_8008DB2C:
    mtc2	$t3,$9
    mtc2	$t4,$10
    mtc2	$t5,$11
    nop
    c2	0x41e012
    mfc2	$t3,$25
    mfc2	$t4,$26
    mfc2	$t5,$27
    mtc2	$t0,$9
    mtc2	$t1,$10
    mtc2	$t2,$11
    nop
    c2	0x49e012
    bgez	$t3,L_8008DB78
    nop
    negu	$t3,$t3
    sll	$t3,$t3,0x3
    b	L_8008DB7C
    negu	$t3,$t3
L_8008DB78:
    sll	$t3,$t3,0x3
L_8008DB7C:
    bgez	$t4,L_8008DB94
    nop
    negu	$t4,$t4
    sll	$t4,$t4,0x3
    b	L_8008DB98
    negu	$t4,$t4
L_8008DB94:
    sll	$t4,$t4,0x3
L_8008DB98:
    bgez	$t5,L_8008DBB0
    nop
    negu	$t5,$t5
    sll	$t5,$t5,0x3
    b	L_8008DBB4
    negu	$t5,$t5
L_8008DBB0:
    sll	$t5,$t5,0x3
L_8008DBB4:
    mfc2	$t0,$25
    mfc2	$t1,$26
    mfc2	$t2,$27
    addu	$t0,$t0,$t3
    addu	$t1,$t1,$t4
    addu	$t2,$t2,$t5
    sw	$t0,0($a1)
    sw	$t1,4($a1)
    sw	$t2,8($a1)
    jr	$ra
    addu	$v0,$a1,$zero
    nop
    nop
.end func_8008DAA8
