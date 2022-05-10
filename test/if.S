	.text
	.globl main
main:
	addi sp, sp, -188
entry_1:
	li t0, 1
	sw t0, 184(sp)
	li t0, 0
	sw t0, 180(sp)
	li t0, 4
	sw t0, 176(sp)
	li t0, 5
	sw t0, 172(sp)
	lw t0, 184(sp)
	sw t0, 168(sp)
	li t0, 1
	sw t0, 164(sp)
	lw t1, 168(sp)
	lw t2, 164(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 160(sp)
	lw t0, 184(sp)
	sw t0, 156(sp)
	li t0, 2
	sw t0, 152(sp)
	lw t1, 156(sp)
	lw t2, 152(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 148(sp)
	lw t1, 160(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 144(sp)
	lw t1, 148(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 140(sp)
	lw t1, 144(sp)
	lw t2, 140(sp)
	or t0, t1, t2
	sw t0, 136(sp)
	lw t0, 136(sp)
	bnez t0, then_2
	j end_3
then_2:
	j end_3
end_3:
	lw t0, 180(sp)
	sw t0, 132(sp)
	li t0, 0
	sw t0, 128(sp)
	lw t1, 132(sp)
	lw t2, 128(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 124(sp)
	lw t0, 180(sp)
	sw t0, 120(sp)
	li t0, 1
	sw t0, 116(sp)
	lw t1, 120(sp)
	lw t2, 116(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 112(sp)
	lw t1, 124(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 108(sp)
	lw t1, 112(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 104(sp)
	lw t1, 108(sp)
	lw t2, 104(sp)
	or t0, t1, t2
	sw t0, 100(sp)
	lw t0, 100(sp)
	bnez t0, then_4
	j else_5
then_4:
	lw t0, 172(sp)
	sw t0, 96(sp)
	li t0, 1
	sw t0, 92(sp)
	lw t1, 96(sp)
	lw t2, 92(sp)
	add t0, t1, t2
	sw t0, 88(sp)
	lw t0, 88(sp)
	sw t0, 172(sp)
	j end_6
else_5:
	j end_6
end_6:
	lw t0, 184(sp)
	sw t0, 84(sp)
	lw t0, 180(sp)
	sw t0, 80(sp)
	lw t1, 84(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 76(sp)
	lw t1, 80(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 72(sp)
	lw t1, 76(sp)
	lw t2, 72(sp)
	and t0, t1, t2
	sw t0, 68(sp)
	lw t0, 176(sp)
	sw t0, 64(sp)
	lw t0, 172(sp)
	sw t0, 60(sp)
	lw t1, 64(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 56(sp)
	lw t1, 60(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 52(sp)
	lw t1, 56(sp)
	lw t2, 52(sp)
	and t0, t1, t2
	sw t0, 48(sp)
	lw t1, 68(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 44(sp)
	lw t1, 48(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 40(sp)
	lw t1, 44(sp)
	lw t2, 40(sp)
	or t0, t1, t2
	sw t0, 36(sp)
	lw t0, 36(sp)
	bnez t0, then_7
	j end_8
then_7:
	lw t0, 172(sp)
	sw t0, 32(sp)
	li t0, 1
	sw t0, 28(sp)
	lw t1, 32(sp)
	lw t2, 28(sp)
	add t0, t1, t2
	sw t0, 24(sp)
	lw t0, 24(sp)
	sw t0, 172(sp)
	j end_8
end_8:
	lw t0, 172(sp)
	sw t0, 20(sp)
	lw t0, 176(sp)
	sw t0, 16(sp)
	lw t1, 16(sp)
	addi t0, t1, 0
	seqz t0, t0
	sw t0, 12(sp)
	lw t1, 20(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 8(sp)
	lw t1, 12(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 4(sp)
	lw t1, 8(sp)
	lw t2, 4(sp)
	or t0, t1, t2
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	addi sp, sp, 188
	ret
