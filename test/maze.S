	.data
	.globl VAR_1
VAR_1:
	.zero 120000
	.globl VAR_2
VAR_2:
	.zero 161604
	.globl VAR_3
VAR_3:
	.zero 4

	.text
	.globl rand
rand:
	li t0, 72
	sub sp, sp, t0
	li t0, 68
	add t0, t0, sp
	sw ra, 0(t0)
entry_1:
	la t0, VAR_3
	lw t0, 0(t0)
	sw t0, 64(sp)
	li t0, 214013
	sw t0, 60(sp)
	lw t1, 64(sp)
	lw t2, 60(sp)
	mul t0, t1, t2
	sw t0, 56(sp)
	li t0, 2531011
	sw t0, 52(sp)
	lw t1, 56(sp)
	lw t2, 52(sp)
	add t0, t1, t2
	sw t0, 48(sp)
	li t0, 1073741824
	sw t0, 44(sp)
	lw t1, 48(sp)
	lw t2, 44(sp)
	rem t0, t1, t2
	sw t0, 40(sp)
	lw t0, 40(sp)
	la t1, VAR_3
	sw t0, 0(t1)
	la t0, VAR_3
	lw t0, 0(t0)
	sw t0, 36(sp)
	li t0, 0
	sw t0, 32(sp)
	lw t1, 36(sp)
	lw t2, 32(sp)
	slt t0, t1, t2
	sw t0, 28(sp)
	lw t0, 28(sp)
	bnez t0, then_2
	j end_3
then_2:
	la t0, VAR_3
	lw t0, 0(t0)
	sw t0, 24(sp)
	lw t1, 24(sp)
	addi t0, t1, 0
	neg t0, t0
	sw t0, 20(sp)
	lw t0, 20(sp)
	la t1, VAR_3
	sw t0, 0(t1)
	j end_3
end_3:
	la t0, VAR_3
	lw t0, 0(t0)
	sw t0, 16(sp)
	li t0, 65536
	sw t0, 12(sp)
	lw t1, 16(sp)
	lw t2, 12(sp)
	div t0, t1, t2
	sw t0, 8(sp)
	li t0, 32768
	sw t0, 4(sp)
	lw t1, 8(sp)
	lw t2, 4(sp)
	rem t0, t1, t2
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	li t0, 68
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 72
	add sp, sp, t0
	ret

	.globl get_neighbor
get_neighbor:
	li t0, 336
	sub sp, sp, t0
	li t0, 332
	add t0, t0, sp
	sw ra, 0(t0)
entry_4:
	li t0, 324
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a0
	li t1, 324
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 316
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a1
	li t1, 316
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 308
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a2
	li t1, 308
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 308(sp)
	lw t0, 0(t0)
	sw t0, 304(sp)
	li t0, 0
	sw t0, 300(sp)
	lw t1, 304(sp)
	lw t2, 300(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 296(sp)
	lw t0, 296(sp)
	bnez t0, then_5
	j else_6
then_5:
	li t0, 0
	sw t0, 292(sp)
	lw t0, 324(sp)
	lw t0, 0(t0)
	sw t0, 288(sp)
	lw t0, 292(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 288
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 284(sp)
	lw t0, 284(sp)
	lw t0, 0(t0)
	sw t0, 280(sp)
	li t0, 0
	sw t0, 276(sp)
	lw t1, 280(sp)
	lw t2, 276(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 272(sp)
	lw t0, 272(sp)
	bnez t0, then_8
	j end_9
else_6:
	lw t0, 308(sp)
	lw t0, 0(t0)
	sw t0, 268(sp)
	li t0, 1
	sw t0, 264(sp)
	lw t1, 268(sp)
	lw t2, 264(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 260(sp)
	lw t0, 260(sp)
	bnez t0, then_10
	j else_11
then_8:
	li t0, 0
	sw t0, 256(sp)
	lw t0, 256(sp)
	mv a0, t0
	li t0, 332
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 336
	add sp, sp, t0
	ret
end_9:
	li t0, 0
	sw t0, 252(sp)
	lw t0, 324(sp)
	lw t0, 0(t0)
	sw t0, 248(sp)
	lw t0, 252(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 248
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 244(sp)
	li t0, 0
	sw t0, 240(sp)
	lw t0, 324(sp)
	lw t0, 0(t0)
	sw t0, 236(sp)
	lw t0, 240(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 236
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 232(sp)
	lw t0, 232(sp)
	lw t0, 0(t0)
	sw t0, 228(sp)
	li t0, 1
	sw t0, 224(sp)
	lw t1, 228(sp)
	lw t2, 224(sp)
	sub t0, t1, t2
	sw t0, 220(sp)
	lw t0, 220(sp)
	lw t1, 244(sp)
	sw t0, 0(t1)
	j end_7
then_10:
	li t0, 0
	sw t0, 216(sp)
	lw t0, 324(sp)
	lw t0, 0(t0)
	sw t0, 212(sp)
	lw t0, 216(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 212
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 208(sp)
	lw t0, 208(sp)
	lw t0, 0(t0)
	sw t0, 204(sp)
	li t0, 99
	sw t0, 200(sp)
	lw t1, 204(sp)
	lw t2, 200(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 196(sp)
	lw t0, 196(sp)
	bnez t0, then_13
	j end_14
else_11:
	lw t0, 308(sp)
	lw t0, 0(t0)
	sw t0, 192(sp)
	li t0, 2
	sw t0, 188(sp)
	lw t1, 192(sp)
	lw t2, 188(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 184(sp)
	lw t0, 184(sp)
	bnez t0, then_15
	j else_16
end_7:
	li t0, 1
	sw t0, 180(sp)
	lw t0, 180(sp)
	mv a0, t0
	li t0, 332
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 336
	add sp, sp, t0
	ret
then_13:
	li t0, 0
	sw t0, 176(sp)
	lw t0, 176(sp)
	mv a0, t0
	li t0, 332
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 336
	add sp, sp, t0
	ret
end_14:
	li t0, 0
	sw t0, 172(sp)
	lw t0, 324(sp)
	lw t0, 0(t0)
	sw t0, 168(sp)
	lw t0, 172(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 168
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 164(sp)
	li t0, 0
	sw t0, 160(sp)
	lw t0, 324(sp)
	lw t0, 0(t0)
	sw t0, 156(sp)
	lw t0, 160(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 156
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 152(sp)
	lw t0, 152(sp)
	lw t0, 0(t0)
	sw t0, 148(sp)
	li t0, 1
	sw t0, 144(sp)
	lw t1, 148(sp)
	lw t2, 144(sp)
	add t0, t1, t2
	sw t0, 140(sp)
	lw t0, 140(sp)
	lw t1, 164(sp)
	sw t0, 0(t1)
	j end_12
then_15:
	li t0, 0
	sw t0, 136(sp)
	lw t0, 316(sp)
	lw t0, 0(t0)
	sw t0, 132(sp)
	lw t0, 136(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 132
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 128(sp)
	lw t0, 128(sp)
	lw t0, 0(t0)
	sw t0, 124(sp)
	li t0, 0
	sw t0, 120(sp)
	lw t1, 124(sp)
	lw t2, 120(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 116(sp)
	lw t0, 116(sp)
	bnez t0, then_18
	j end_19
else_16:
	lw t0, 308(sp)
	lw t0, 0(t0)
	sw t0, 112(sp)
	li t0, 3
	sw t0, 108(sp)
	lw t1, 112(sp)
	lw t2, 108(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 104(sp)
	lw t0, 104(sp)
	bnez t0, then_20
	j end_21
end_12:
	j end_7
then_18:
	li t0, 0
	sw t0, 100(sp)
	lw t0, 100(sp)
	mv a0, t0
	li t0, 332
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 336
	add sp, sp, t0
	ret
end_19:
	li t0, 0
	sw t0, 96(sp)
	lw t0, 316(sp)
	lw t0, 0(t0)
	sw t0, 92(sp)
	lw t0, 96(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 92
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 88(sp)
	li t0, 0
	sw t0, 84(sp)
	lw t0, 316(sp)
	lw t0, 0(t0)
	sw t0, 80(sp)
	lw t0, 84(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 80
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 76(sp)
	lw t0, 76(sp)
	lw t0, 0(t0)
	sw t0, 72(sp)
	li t0, 1
	sw t0, 68(sp)
	lw t1, 72(sp)
	lw t2, 68(sp)
	sub t0, t1, t2
	sw t0, 64(sp)
	lw t0, 64(sp)
	lw t1, 88(sp)
	sw t0, 0(t1)
	j end_17
then_20:
	li t0, 0
	sw t0, 60(sp)
	lw t0, 316(sp)
	lw t0, 0(t0)
	sw t0, 56(sp)
	lw t0, 60(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 56
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 52(sp)
	lw t0, 52(sp)
	lw t0, 0(t0)
	sw t0, 48(sp)
	li t0, 99
	sw t0, 44(sp)
	lw t1, 48(sp)
	lw t2, 44(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 40(sp)
	lw t0, 40(sp)
	bnez t0, then_22
	j end_23
end_21:
	j end_17
end_17:
	j end_12
then_22:
	li t0, 0
	sw t0, 36(sp)
	lw t0, 36(sp)
	mv a0, t0
	li t0, 332
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 336
	add sp, sp, t0
	ret
end_23:
	li t0, 0
	sw t0, 32(sp)
	lw t0, 316(sp)
	lw t0, 0(t0)
	sw t0, 28(sp)
	lw t0, 32(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 28
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 24(sp)
	li t0, 0
	sw t0, 20(sp)
	lw t0, 316(sp)
	lw t0, 0(t0)
	sw t0, 16(sp)
	lw t0, 20(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 16
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 12(sp)
	lw t0, 12(sp)
	lw t0, 0(t0)
	sw t0, 8(sp)
	li t0, 1
	sw t0, 4(sp)
	lw t1, 8(sp)
	lw t2, 4(sp)
	add t0, t1, t2
	sw t0, 0(sp)
	lw t0, 0(sp)
	lw t1, 24(sp)
	sw t0, 0(t1)
	j end_21

	.globl remove_wall
remove_wall:
	li t0, 188
	sub sp, sp, t0
	li t0, 184
	add t0, t0, sp
	sw ra, 0(t0)
entry_24:
	li t0, 176
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a0
	li t1, 176
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 168
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a1
	li t1, 168
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 160
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a2
	li t1, 160
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 160(sp)
	lw t0, 0(t0)
	sw t0, 156(sp)
	li t0, 0
	sw t0, 152(sp)
	lw t1, 156(sp)
	lw t2, 152(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 148(sp)
	lw t0, 148(sp)
	bnez t0, then_25
	j else_26
then_25:
	lw t0, 168(sp)
	lw t0, 0(t0)
	sw t0, 144(sp)
	lw t0, 176(sp)
	lw t0, 0(t0)
	sw t0, 140(sp)
	li t0, 1
	sw t0, 136(sp)
	lw t0, 144(sp)
	li t1, 1200
	mul t0, t1, t0
	la t1, VAR_1
	add t0, t1, t0
	sw t0, 132(sp)
	lw t0, 140(sp)
	li t1, 12
	mul t1, t1, t0
	li t0, 132
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 128(sp)
	lw t0, 136(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 128
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 124(sp)
	li t0, 1
	lw t1, 124(sp)
	sw t0, 0(t1)
	j end_27
else_26:
	lw t0, 160(sp)
	lw t0, 0(t0)
	sw t0, 120(sp)
	li t0, 1
	sw t0, 116(sp)
	lw t1, 120(sp)
	lw t2, 116(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 112(sp)
	lw t0, 112(sp)
	bnez t0, then_28
	j else_29
end_27:
	li t0, 184
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 188
	add sp, sp, t0
	ret
then_28:
	lw t0, 168(sp)
	lw t0, 0(t0)
	sw t0, 108(sp)
	lw t0, 176(sp)
	lw t0, 0(t0)
	sw t0, 104(sp)
	li t0, 1
	sw t0, 100(sp)
	lw t1, 104(sp)
	lw t2, 100(sp)
	add t0, t1, t2
	sw t0, 96(sp)
	li t0, 1
	sw t0, 92(sp)
	lw t0, 108(sp)
	li t1, 1200
	mul t0, t1, t0
	la t1, VAR_1
	add t0, t1, t0
	sw t0, 88(sp)
	lw t0, 96(sp)
	li t1, 12
	mul t1, t1, t0
	li t0, 88
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 84(sp)
	lw t0, 92(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 84
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 80(sp)
	li t0, 1
	lw t1, 80(sp)
	sw t0, 0(t1)
	j end_30
else_29:
	lw t0, 160(sp)
	lw t0, 0(t0)
	sw t0, 76(sp)
	li t0, 2
	sw t0, 72(sp)
	lw t1, 76(sp)
	lw t2, 72(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 68(sp)
	lw t0, 68(sp)
	bnez t0, then_31
	j else_32
end_30:
	j end_27
then_31:
	lw t0, 168(sp)
	lw t0, 0(t0)
	sw t0, 64(sp)
	lw t0, 176(sp)
	lw t0, 0(t0)
	sw t0, 60(sp)
	li t0, 2
	sw t0, 56(sp)
	lw t0, 64(sp)
	li t1, 1200
	mul t0, t1, t0
	la t1, VAR_1
	add t0, t1, t0
	sw t0, 52(sp)
	lw t0, 60(sp)
	li t1, 12
	mul t1, t1, t0
	li t0, 52
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 48(sp)
	lw t0, 56(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 48
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 44(sp)
	li t0, 1
	lw t1, 44(sp)
	sw t0, 0(t1)
	j end_33
else_32:
	lw t0, 160(sp)
	lw t0, 0(t0)
	sw t0, 40(sp)
	li t0, 3
	sw t0, 36(sp)
	lw t1, 40(sp)
	lw t2, 36(sp)
	sub t0, t1, t2
	seqz t0, t0
	sw t0, 32(sp)
	lw t0, 32(sp)
	bnez t0, then_34
	j end_35
end_33:
	j end_30
then_34:
	lw t0, 168(sp)
	lw t0, 0(t0)
	sw t0, 28(sp)
	li t0, 1
	sw t0, 24(sp)
	lw t1, 28(sp)
	lw t2, 24(sp)
	add t0, t1, t2
	sw t0, 20(sp)
	lw t0, 176(sp)
	lw t0, 0(t0)
	sw t0, 16(sp)
	li t0, 2
	sw t0, 12(sp)
	lw t0, 20(sp)
	li t1, 1200
	mul t0, t1, t0
	la t1, VAR_1
	add t0, t1, t0
	sw t0, 8(sp)
	lw t0, 16(sp)
	li t1, 12
	mul t1, t1, t0
	li t0, 8
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 4(sp)
	lw t0, 12(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 4
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 0(sp)
	li t0, 1
	lw t1, 0(sp)
	sw t0, 0(t1)
	j end_35
end_35:
	j end_33

	.globl gen_maze
gen_maze:
	li t0, 396
	sub sp, sp, t0
	li t0, 392
	add t0, t0, sp
	sw ra, 0(t0)
entry_36:
	li t0, 384
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a0
	li t1, 384
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 376
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a1
	li t1, 376
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 376(sp)
	lw t0, 0(t0)
	sw t0, 372(sp)
	lw t0, 384(sp)
	lw t0, 0(t0)
	sw t0, 368(sp)
	li t0, 0
	sw t0, 364(sp)
	lw t0, 372(sp)
	li t1, 1200
	mul t0, t1, t0
	la t1, VAR_1
	add t0, t1, t0
	sw t0, 360(sp)
	lw t0, 368(sp)
	li t1, 12
	mul t1, t1, t0
	li t0, 360
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 356(sp)
	lw t0, 364(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 356
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 352(sp)
	li t0, 1
	lw t1, 352(sp)
	sw t0, 0(t1)
	li t0, 332
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	sw t0, 328(sp)
	li t0, 1
	sw t0, 324(sp)
	li t0, 2
	sw t0, 320(sp)
	li t0, 3
	sw t0, 316(sp)
	li t0, 0
	li t1, 4
	mul t1, t1, t0
	li t0, 332
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 312(sp)
	lw t0, 328(sp)
	lw t1, 312(sp)
	sw t0, 0(t1)
	li t0, 1
	li t1, 4
	mul t1, t1, t0
	li t0, 332
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 308(sp)
	lw t0, 324(sp)
	lw t1, 308(sp)
	sw t0, 0(t1)
	li t0, 2
	li t1, 4
	mul t1, t1, t0
	li t0, 332
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 304(sp)
	lw t0, 320(sp)
	lw t1, 304(sp)
	sw t0, 0(t1)
	li t0, 3
	li t1, 4
	mul t1, t1, t0
	li t0, 332
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 300(sp)
	lw t0, 316(sp)
	lw t1, 300(sp)
	sw t0, 0(t1)
	li t0, 292
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 292
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_37
while_exp_37:
	lw t0, 292(sp)
	lw t0, 0(t0)
	sw t0, 288(sp)
	li t0, 4
	sw t0, 284(sp)
	lw t1, 288(sp)
	lw t2, 284(sp)
	slt t0, t1, t2
	sw t0, 280(sp)
	lw t0, 280(sp)
	bnez t0, while_loop_38
	j while_end_39
while_loop_38:
	li t0, 272
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	call rand
	sw a0, 268(sp)
	li t0, 4
	sw t0, 264(sp)
	lw t1, 268(sp)
	lw t2, 264(sp)
	rem t0, t1, t2
	sw t0, 260(sp)
	lw t0, 260(sp)
	li t1, 272
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 252
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 292(sp)
	lw t0, 0(t0)
	sw t0, 248(sp)
	lw t0, 248(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 332
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 244(sp)
	lw t0, 244(sp)
	lw t0, 0(t0)
	sw t0, 240(sp)
	lw t0, 240(sp)
	li t1, 252
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 292(sp)
	lw t0, 0(t0)
	sw t0, 236(sp)
	lw t0, 236(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 332
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 232(sp)
	lw t0, 272(sp)
	lw t0, 0(t0)
	sw t0, 228(sp)
	lw t0, 228(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 332
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 224(sp)
	lw t0, 224(sp)
	lw t0, 0(t0)
	sw t0, 220(sp)
	lw t0, 220(sp)
	lw t1, 232(sp)
	sw t0, 0(t1)
	lw t0, 272(sp)
	lw t0, 0(t0)
	sw t0, 216(sp)
	lw t0, 216(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 332
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 212(sp)
	lw t0, 252(sp)
	lw t0, 0(t0)
	sw t0, 208(sp)
	lw t0, 208(sp)
	lw t1, 212(sp)
	sw t0, 0(t1)
	lw t0, 292(sp)
	lw t0, 0(t0)
	sw t0, 204(sp)
	li t0, 1
	sw t0, 200(sp)
	lw t1, 204(sp)
	lw t2, 200(sp)
	add t0, t1, t2
	sw t0, 196(sp)
	lw t0, 196(sp)
	li t1, 292
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_37
while_end_39:
	li t0, 0
	li t1, 292
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_40
while_exp_40:
	lw t0, 292(sp)
	lw t0, 0(t0)
	sw t0, 192(sp)
	li t0, 4
	sw t0, 188(sp)
	lw t1, 192(sp)
	lw t2, 188(sp)
	slt t0, t1, t2
	sw t0, 184(sp)
	lw t0, 184(sp)
	bnez t0, while_loop_41
	j while_end_42
while_loop_41:
	li t0, 176
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 384(sp)
	lw t0, 0(t0)
	sw t0, 172(sp)
	li t0, 0
	li t1, 4
	mul t1, t1, t0
	li t0, 176
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 168(sp)
	lw t0, 172(sp)
	lw t1, 168(sp)
	sw t0, 0(t1)
	li t0, 160
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 376(sp)
	lw t0, 0(t0)
	sw t0, 156(sp)
	li t0, 0
	li t1, 4
	mul t1, t1, t0
	li t0, 160
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 152(sp)
	lw t0, 156(sp)
	lw t1, 152(sp)
	sw t0, 0(t1)
	li t0, 144
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 4
	mul t1, t1, t0
	li t0, 176
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 140(sp)
	li t0, 0
	li t1, 4
	mul t1, t1, t0
	li t0, 160
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 136(sp)
	lw t0, 292(sp)
	lw t0, 0(t0)
	sw t0, 132(sp)
	lw t0, 132(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 332
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 128(sp)
	lw t0, 128(sp)
	lw t0, 0(t0)
	sw t0, 124(sp)
	lw a0, 140(sp)
	lw a1, 136(sp)
	lw a2, 124(sp)
	call get_neighbor
	sw a0, 120(sp)
	lw t1, 120(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 116(sp)
	lw t0, 116(sp)
	li t1, 144
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 116(sp)
	bnez t0, and_45
	j endand_46
while_end_42:
	li t0, 392
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 396
	add sp, sp, t0
	ret
and_45:
	li t0, 0
	sw t0, 112(sp)
	lw t0, 112(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 160
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 108(sp)
	lw t0, 108(sp)
	lw t0, 0(t0)
	sw t0, 104(sp)
	li t0, 0
	sw t0, 100(sp)
	lw t0, 100(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 176
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 96(sp)
	lw t0, 96(sp)
	lw t0, 0(t0)
	sw t0, 92(sp)
	li t0, 0
	sw t0, 88(sp)
	lw t0, 104(sp)
	li t1, 1200
	mul t0, t1, t0
	la t1, VAR_1
	add t0, t1, t0
	sw t0, 84(sp)
	lw t0, 92(sp)
	li t1, 12
	mul t1, t1, t0
	li t0, 84
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 80(sp)
	lw t0, 88(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 80
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 76(sp)
	lw t0, 76(sp)
	lw t0, 0(t0)
	sw t0, 72(sp)
	lw t1, 72(sp)
	addi t0, t1, 0
	seqz t0, t0
	sw t0, 68(sp)
	lw t1, 68(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 64(sp)
	lw t1, 116(sp)
	lw t2, 64(sp)
	and t0, t1, t2
	sw t0, 60(sp)
	lw t0, 60(sp)
	li t1, 144
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j endand_46
endand_46:
	lw t0, 144(sp)
	lw t0, 0(t0)
	sw t0, 56(sp)
	lw t0, 56(sp)
	bnez t0, then_43
	j end_44
then_43:
	lw t0, 384(sp)
	lw t0, 0(t0)
	sw t0, 52(sp)
	lw t0, 376(sp)
	lw t0, 0(t0)
	sw t0, 48(sp)
	lw t0, 292(sp)
	lw t0, 0(t0)
	sw t0, 44(sp)
	lw t0, 44(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 332
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 40(sp)
	lw t0, 40(sp)
	lw t0, 0(t0)
	sw t0, 36(sp)
	lw a0, 52(sp)
	lw a1, 48(sp)
	lw a2, 36(sp)
	call remove_wall
	li t0, 0
	sw t0, 32(sp)
	lw t0, 32(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 176
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 28(sp)
	lw t0, 28(sp)
	lw t0, 0(t0)
	sw t0, 24(sp)
	li t0, 0
	sw t0, 20(sp)
	lw t0, 20(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 160
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 16(sp)
	lw t0, 16(sp)
	lw t0, 0(t0)
	sw t0, 12(sp)
	lw a0, 24(sp)
	lw a1, 12(sp)
	call gen_maze
	j end_44
end_44:
	lw t0, 292(sp)
	lw t0, 0(t0)
	sw t0, 8(sp)
	li t0, 1
	sw t0, 4(sp)
	lw t1, 8(sp)
	lw t2, 4(sp)
	add t0, t1, t2
	sw t0, 0(sp)
	lw t0, 0(sp)
	li t1, 292
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_40

	.globl render
render:
	li t0, 324
	sub sp, sp, t0
	li t0, 320
	add t0, t0, sp
	sw ra, 0(t0)
entry_47:
	li t0, 312
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 304
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 304
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_48
while_exp_48:
	lw t0, 304(sp)
	lw t0, 0(t0)
	sw t0, 300(sp)
	li t0, 100
	sw t0, 296(sp)
	lw t1, 300(sp)
	lw t2, 296(sp)
	slt t0, t1, t2
	sw t0, 292(sp)
	lw t0, 292(sp)
	bnez t0, while_loop_49
	j while_end_50
while_loop_49:
	li t0, 0
	li t1, 312
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_51
while_end_50:
	li t0, 0
	li t1, 304
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_58
while_exp_51:
	lw t0, 312(sp)
	lw t0, 0(t0)
	sw t0, 288(sp)
	li t0, 100
	sw t0, 284(sp)
	lw t1, 288(sp)
	lw t2, 284(sp)
	slt t0, t1, t2
	sw t0, 280(sp)
	lw t0, 280(sp)
	bnez t0, while_loop_52
	j while_end_53
while_exp_58:
	lw t0, 304(sp)
	lw t0, 0(t0)
	sw t0, 276(sp)
	li t0, 201
	sw t0, 272(sp)
	lw t1, 276(sp)
	lw t2, 272(sp)
	slt t0, t1, t2
	sw t0, 268(sp)
	lw t0, 268(sp)
	bnez t0, while_loop_59
	j while_end_60
while_loop_52:
	lw t0, 304(sp)
	lw t0, 0(t0)
	sw t0, 264(sp)
	lw t0, 312(sp)
	lw t0, 0(t0)
	sw t0, 260(sp)
	li t0, 1
	sw t0, 256(sp)
	lw t0, 264(sp)
	li t1, 1200
	mul t0, t1, t0
	la t1, VAR_1
	add t0, t1, t0
	sw t0, 252(sp)
	lw t0, 260(sp)
	li t1, 12
	mul t1, t1, t0
	li t0, 252
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 248(sp)
	lw t0, 256(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 248
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 244(sp)
	lw t0, 244(sp)
	lw t0, 0(t0)
	sw t0, 240(sp)
	lw t1, 240(sp)
	addi t0, t1, 0
	seqz t0, t0
	sw t0, 236(sp)
	lw t0, 236(sp)
	bnez t0, then_54
	j end_55
while_end_53:
	lw t0, 304(sp)
	lw t0, 0(t0)
	sw t0, 232(sp)
	li t0, 1
	sw t0, 228(sp)
	lw t1, 232(sp)
	lw t2, 228(sp)
	add t0, t1, t2
	sw t0, 224(sp)
	lw t0, 224(sp)
	li t1, 304
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_48
while_loop_59:
	lw t0, 304(sp)
	lw t0, 0(t0)
	sw t0, 220(sp)
	li t0, 200
	sw t0, 216(sp)
	lw t0, 220(sp)
	li t1, 804
	mul t0, t1, t0
	la t1, VAR_2
	add t0, t1, t0
	sw t0, 212(sp)
	lw t0, 216(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 212
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 208(sp)
	li t0, 1
	lw t1, 208(sp)
	sw t0, 0(t1)
	lw t0, 304(sp)
	lw t0, 0(t0)
	sw t0, 204(sp)
	li t0, 1
	sw t0, 200(sp)
	lw t1, 204(sp)
	lw t2, 200(sp)
	add t0, t1, t2
	sw t0, 196(sp)
	lw t0, 196(sp)
	li t1, 304
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_58
while_end_60:
	li t0, 0
	li t1, 312
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_61
then_54:
	lw t0, 304(sp)
	lw t0, 0(t0)
	sw t0, 192(sp)
	li t0, 2
	sw t0, 188(sp)
	lw t1, 192(sp)
	lw t2, 188(sp)
	mul t0, t1, t2
	sw t0, 184(sp)
	li t0, 1
	sw t0, 180(sp)
	lw t1, 184(sp)
	lw t2, 180(sp)
	add t0, t1, t2
	sw t0, 176(sp)
	lw t0, 312(sp)
	lw t0, 0(t0)
	sw t0, 172(sp)
	li t0, 2
	sw t0, 168(sp)
	lw t1, 172(sp)
	lw t2, 168(sp)
	mul t0, t1, t2
	sw t0, 164(sp)
	lw t0, 176(sp)
	li t1, 804
	mul t0, t1, t0
	la t1, VAR_2
	add t0, t1, t0
	sw t0, 160(sp)
	lw t0, 164(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 160
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 156(sp)
	li t0, 1
	lw t1, 156(sp)
	sw t0, 0(t1)
	j end_55
end_55:
	lw t0, 304(sp)
	lw t0, 0(t0)
	sw t0, 152(sp)
	lw t0, 312(sp)
	lw t0, 0(t0)
	sw t0, 148(sp)
	li t0, 2
	sw t0, 144(sp)
	lw t0, 152(sp)
	li t1, 1200
	mul t0, t1, t0
	la t1, VAR_1
	add t0, t1, t0
	sw t0, 140(sp)
	lw t0, 148(sp)
	li t1, 12
	mul t1, t1, t0
	li t0, 140
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 136(sp)
	lw t0, 144(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 136
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 132(sp)
	lw t0, 132(sp)
	lw t0, 0(t0)
	sw t0, 128(sp)
	lw t1, 128(sp)
	addi t0, t1, 0
	seqz t0, t0
	sw t0, 124(sp)
	lw t0, 124(sp)
	bnez t0, then_56
	j end_57
while_exp_61:
	lw t0, 312(sp)
	lw t0, 0(t0)
	sw t0, 120(sp)
	li t0, 201
	sw t0, 116(sp)
	lw t1, 120(sp)
	lw t2, 116(sp)
	slt t0, t1, t2
	sw t0, 112(sp)
	lw t0, 112(sp)
	bnez t0, while_loop_62
	j while_end_63
then_56:
	lw t0, 304(sp)
	lw t0, 0(t0)
	sw t0, 108(sp)
	li t0, 2
	sw t0, 104(sp)
	lw t1, 108(sp)
	lw t2, 104(sp)
	mul t0, t1, t2
	sw t0, 100(sp)
	lw t0, 312(sp)
	lw t0, 0(t0)
	sw t0, 96(sp)
	li t0, 2
	sw t0, 92(sp)
	lw t1, 96(sp)
	lw t2, 92(sp)
	mul t0, t1, t2
	sw t0, 88(sp)
	li t0, 1
	sw t0, 84(sp)
	lw t1, 88(sp)
	lw t2, 84(sp)
	add t0, t1, t2
	sw t0, 80(sp)
	lw t0, 100(sp)
	li t1, 804
	mul t0, t1, t0
	la t1, VAR_2
	add t0, t1, t0
	sw t0, 76(sp)
	lw t0, 80(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 76
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 72(sp)
	li t0, 1
	lw t1, 72(sp)
	sw t0, 0(t1)
	j end_57
end_57:
	lw t0, 304(sp)
	lw t0, 0(t0)
	sw t0, 68(sp)
	li t0, 2
	sw t0, 64(sp)
	lw t1, 68(sp)
	lw t2, 64(sp)
	mul t0, t1, t2
	sw t0, 60(sp)
	lw t0, 312(sp)
	lw t0, 0(t0)
	sw t0, 56(sp)
	li t0, 2
	sw t0, 52(sp)
	lw t1, 56(sp)
	lw t2, 52(sp)
	mul t0, t1, t2
	sw t0, 48(sp)
	lw t0, 60(sp)
	li t1, 804
	mul t0, t1, t0
	la t1, VAR_2
	add t0, t1, t0
	sw t0, 44(sp)
	lw t0, 48(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 44
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 40(sp)
	li t0, 1
	lw t1, 40(sp)
	sw t0, 0(t1)
	lw t0, 312(sp)
	lw t0, 0(t0)
	sw t0, 36(sp)
	li t0, 1
	sw t0, 32(sp)
	lw t1, 36(sp)
	lw t2, 32(sp)
	add t0, t1, t2
	sw t0, 28(sp)
	lw t0, 28(sp)
	li t1, 312
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_51
while_loop_62:
	li t0, 200
	sw t0, 24(sp)
	lw t0, 312(sp)
	lw t0, 0(t0)
	sw t0, 20(sp)
	lw t0, 24(sp)
	li t1, 804
	mul t0, t1, t0
	la t1, VAR_2
	add t0, t1, t0
	sw t0, 16(sp)
	lw t0, 20(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 16
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 12(sp)
	li t0, 1
	lw t1, 12(sp)
	sw t0, 0(t1)
	lw t0, 312(sp)
	lw t0, 0(t0)
	sw t0, 8(sp)
	li t0, 1
	sw t0, 4(sp)
	lw t1, 8(sp)
	lw t2, 4(sp)
	add t0, t1, t2
	sw t0, 0(sp)
	lw t0, 0(sp)
	li t1, 312
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_61
while_end_63:
	li t0, 320
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 324
	add sp, sp, t0
	ret

	.globl main
main:
	li t0, 404
	sub sp, sp, t0
	li t0, 400
	add t0, t0, sp
	sw ra, 0(t0)
entry_64:
	call getint
	sw a0, 396(sp)
	lw t0, 396(sp)
	la t1, VAR_3
	sw t0, 0(t1)
	li t0, 388
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	call getint
	sw a0, 384(sp)
	lw t0, 384(sp)
	li t1, 388
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	call starttime
	call rand
	sw a0, 380(sp)
	li t0, 100
	sw t0, 376(sp)
	lw t1, 380(sp)
	lw t2, 376(sp)
	rem t0, t1, t2
	sw t0, 372(sp)
	call rand
	sw a0, 368(sp)
	li t0, 100
	sw t0, 364(sp)
	lw t1, 368(sp)
	lw t2, 364(sp)
	rem t0, t1, t2
	sw t0, 360(sp)
	lw a0, 372(sp)
	lw a1, 360(sp)
	call gen_maze
	call render
	call stoptime
	call starttime
	li t0, 80
	sw t0, 356(sp)
	lw a0, 356(sp)
	call putch
	li t0, 51
	sw t0, 352(sp)
	lw a0, 352(sp)
	call putch
	li t0, 10
	sw t0, 348(sp)
	lw a0, 348(sp)
	call putch
	li t0, 201
	sw t0, 344(sp)
	lw t0, 388(sp)
	lw t0, 0(t0)
	sw t0, 340(sp)
	lw t1, 344(sp)
	lw t2, 340(sp)
	mul t0, t1, t2
	sw t0, 336(sp)
	lw a0, 336(sp)
	call putint
	li t0, 32
	sw t0, 332(sp)
	lw a0, 332(sp)
	call putch
	li t0, 201
	sw t0, 328(sp)
	lw t0, 388(sp)
	lw t0, 0(t0)
	sw t0, 324(sp)
	lw t1, 328(sp)
	lw t2, 324(sp)
	mul t0, t1, t2
	sw t0, 320(sp)
	lw a0, 320(sp)
	call putint
	li t0, 10
	sw t0, 316(sp)
	lw a0, 316(sp)
	call putch
	li t0, 255
	sw t0, 312(sp)
	lw a0, 312(sp)
	call putint
	li t0, 10
	sw t0, 308(sp)
	lw a0, 308(sp)
	call putch
	li t0, 300
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 300
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_65
while_exp_65:
	lw t0, 300(sp)
	lw t0, 0(t0)
	sw t0, 296(sp)
	li t0, 201
	sw t0, 292(sp)
	lw t0, 388(sp)
	lw t0, 0(t0)
	sw t0, 288(sp)
	lw t1, 292(sp)
	lw t2, 288(sp)
	mul t0, t1, t2
	sw t0, 284(sp)
	lw t1, 296(sp)
	lw t2, 284(sp)
	slt t0, t1, t2
	sw t0, 280(sp)
	lw t0, 280(sp)
	bnez t0, while_loop_66
	j while_end_67
while_loop_66:
	li t0, 272
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 272
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_68
while_end_67:
	call stoptime
	li t0, 0
	sw t0, 268(sp)
	lw t0, 268(sp)
	mv a0, t0
	li t0, 400
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 404
	add sp, sp, t0
	ret
while_exp_68:
	lw t0, 272(sp)
	lw t0, 0(t0)
	sw t0, 264(sp)
	li t0, 201
	sw t0, 260(sp)
	lw t0, 388(sp)
	lw t0, 0(t0)
	sw t0, 256(sp)
	lw t1, 260(sp)
	lw t2, 256(sp)
	mul t0, t1, t2
	sw t0, 252(sp)
	lw t1, 264(sp)
	lw t2, 252(sp)
	slt t0, t1, t2
	sw t0, 248(sp)
	lw t0, 248(sp)
	bnez t0, while_loop_69
	j while_end_70
while_loop_69:
	li t0, 240
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 272(sp)
	lw t0, 0(t0)
	sw t0, 236(sp)
	lw t0, 388(sp)
	lw t0, 0(t0)
	sw t0, 232(sp)
	lw t1, 236(sp)
	lw t2, 232(sp)
	div t0, t1, t2
	sw t0, 228(sp)
	lw t0, 228(sp)
	li t1, 240
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 220
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 300(sp)
	lw t0, 0(t0)
	sw t0, 216(sp)
	lw t0, 388(sp)
	lw t0, 0(t0)
	sw t0, 212(sp)
	lw t1, 216(sp)
	lw t2, 212(sp)
	div t0, t1, t2
	sw t0, 208(sp)
	lw t0, 208(sp)
	li t1, 220
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 200
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 220(sp)
	lw t0, 0(t0)
	sw t0, 196(sp)
	lw t0, 240(sp)
	lw t0, 0(t0)
	sw t0, 192(sp)
	lw t0, 196(sp)
	li t1, 804
	mul t0, t1, t0
	la t1, VAR_2
	add t0, t1, t0
	sw t0, 188(sp)
	lw t0, 192(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 188
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 184(sp)
	lw t0, 184(sp)
	lw t0, 0(t0)
	sw t0, 180(sp)
	li t0, 255
	sw t0, 176(sp)
	lw t1, 180(sp)
	lw t2, 176(sp)
	mul t0, t1, t2
	sw t0, 172(sp)
	lw t0, 272(sp)
	lw t0, 0(t0)
	sw t0, 168(sp)
	lw t1, 172(sp)
	lw t2, 168(sp)
	mul t0, t1, t2
	sw t0, 164(sp)
	li t0, 201
	sw t0, 160(sp)
	lw t0, 388(sp)
	lw t0, 0(t0)
	sw t0, 156(sp)
	lw t1, 160(sp)
	lw t2, 156(sp)
	mul t0, t1, t2
	sw t0, 152(sp)
	lw t1, 164(sp)
	lw t2, 152(sp)
	div t0, t1, t2
	sw t0, 148(sp)
	lw t0, 148(sp)
	li t1, 200
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 140
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 220(sp)
	lw t0, 0(t0)
	sw t0, 136(sp)
	lw t0, 240(sp)
	lw t0, 0(t0)
	sw t0, 132(sp)
	lw t0, 136(sp)
	li t1, 804
	mul t0, t1, t0
	la t1, VAR_2
	add t0, t1, t0
	sw t0, 128(sp)
	lw t0, 132(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 128
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 124(sp)
	lw t0, 124(sp)
	lw t0, 0(t0)
	sw t0, 120(sp)
	li t0, 255
	sw t0, 116(sp)
	lw t1, 120(sp)
	lw t2, 116(sp)
	mul t0, t1, t2
	sw t0, 112(sp)
	lw t0, 300(sp)
	lw t0, 0(t0)
	sw t0, 108(sp)
	lw t1, 112(sp)
	lw t2, 108(sp)
	mul t0, t1, t2
	sw t0, 104(sp)
	li t0, 201
	sw t0, 100(sp)
	lw t0, 388(sp)
	lw t0, 0(t0)
	sw t0, 96(sp)
	lw t1, 100(sp)
	lw t2, 96(sp)
	mul t0, t1, t2
	sw t0, 92(sp)
	lw t1, 104(sp)
	lw t2, 92(sp)
	div t0, t1, t2
	sw t0, 88(sp)
	lw t0, 88(sp)
	li t1, 140
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 80
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 220(sp)
	lw t0, 0(t0)
	sw t0, 76(sp)
	lw t0, 240(sp)
	lw t0, 0(t0)
	sw t0, 72(sp)
	lw t0, 76(sp)
	li t1, 804
	mul t0, t1, t0
	la t1, VAR_2
	add t0, t1, t0
	sw t0, 68(sp)
	lw t0, 72(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 68
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 64(sp)
	lw t0, 64(sp)
	lw t0, 0(t0)
	sw t0, 60(sp)
	li t0, 255
	sw t0, 56(sp)
	lw t1, 60(sp)
	lw t2, 56(sp)
	mul t0, t1, t2
	sw t0, 52(sp)
	lw t0, 52(sp)
	li t1, 80
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 200(sp)
	lw t0, 0(t0)
	sw t0, 48(sp)
	lw a0, 48(sp)
	call putint
	li t0, 32
	sw t0, 44(sp)
	lw a0, 44(sp)
	call putch
	lw t0, 140(sp)
	lw t0, 0(t0)
	sw t0, 40(sp)
	lw a0, 40(sp)
	call putint
	li t0, 32
	sw t0, 36(sp)
	lw a0, 36(sp)
	call putch
	lw t0, 80(sp)
	lw t0, 0(t0)
	sw t0, 32(sp)
	lw a0, 32(sp)
	call putint
	li t0, 32
	sw t0, 28(sp)
	lw a0, 28(sp)
	call putch
	lw t0, 272(sp)
	lw t0, 0(t0)
	sw t0, 24(sp)
	li t0, 1
	sw t0, 20(sp)
	lw t1, 24(sp)
	lw t2, 20(sp)
	add t0, t1, t2
	sw t0, 16(sp)
	lw t0, 16(sp)
	li t1, 272
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_68
while_end_70:
	li t0, 10
	sw t0, 12(sp)
	lw a0, 12(sp)
	call putch
	lw t0, 300(sp)
	lw t0, 0(t0)
	sw t0, 8(sp)
	li t0, 1
	sw t0, 4(sp)
	lw t1, 8(sp)
	lw t2, 4(sp)
	add t0, t1, t2
	sw t0, 0(sp)
	lw t0, 0(sp)
	li t1, 300
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_65

