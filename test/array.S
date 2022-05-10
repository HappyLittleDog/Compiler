	.data
	.globl VAR_1
VAR_1:
	.word 0

	.text
	.globl init1d
init1d:
	li t0, 80
	sub sp, sp, t0
	li t0, 76
	add t0, t0, sp
	sw ra, 0(t0)
entry_1:
	li t0, 68
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a0
	li t1, 68
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 60
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a1
	li t1, 60
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 52
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 52
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_2
while_exp_2:
	lw t0, 52(sp)
	lw t0, 0(t0)
	sw t0, 48(sp)
	lw t0, 68(sp)
	lw t0, 0(t0)
	sw t0, 44(sp)
	lw t1, 48(sp)
	lw t2, 44(sp)
	slt t0, t1, t2
	sw t0, 40(sp)
	lw t0, 40(sp)
	bnez t0, while_loop_3
	j while_end_4
while_loop_3:
	lw t0, 52(sp)
	lw t0, 0(t0)
	sw t0, 36(sp)
	lw t0, 60(sp)
	lw t0, 0(t0)
	sw t0, 32(sp)
	lw t0, 36(sp)
	li t1, 4
	mul t1, t1, t0
	li t0, 32
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 28(sp)
	la t0, VAR_1
	lw t0, 0(t0)
	sw t0, 24(sp)
	lw t0, 24(sp)
	lw t1, 28(sp)
	sw t0, 0(t1)
	la t0, VAR_1
	lw t0, 0(t0)
	sw t0, 20(sp)
	li t0, 1
	sw t0, 16(sp)
	lw t1, 20(sp)
	lw t2, 16(sp)
	add t0, t1, t2
	sw t0, 12(sp)
	lw t0, 12(sp)
	la t1, VAR_1
	sw t0, 0(t1)
	lw t0, 52(sp)
	lw t0, 0(t0)
	sw t0, 8(sp)
	li t0, 1
	sw t0, 4(sp)
	lw t1, 8(sp)
	lw t2, 4(sp)
	add t0, t1, t2
	sw t0, 0(sp)
	lw t0, 0(sp)
	li t1, 52
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_2
while_end_4:
	li t0, 76
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 80
	add sp, sp, t0
	ret

	.globl init2d
init2d:
	li t0, 72
	sub sp, sp, t0
	li t0, 68
	add t0, t0, sp
	sw ra, 0(t0)
entry_5:
	li t0, 60
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a0
	li t1, 60
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 52
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a1
	li t1, 52
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 44
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 44
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_6
while_exp_6:
	lw t0, 44(sp)
	lw t0, 0(t0)
	sw t0, 40(sp)
	lw t0, 60(sp)
	lw t0, 0(t0)
	sw t0, 36(sp)
	lw t1, 40(sp)
	lw t2, 36(sp)
	slt t0, t1, t2
	sw t0, 32(sp)
	lw t0, 32(sp)
	bnez t0, while_loop_7
	j while_end_8
while_loop_7:
	li t0, 10
	sw t0, 28(sp)
	lw t0, 44(sp)
	lw t0, 0(t0)
	sw t0, 24(sp)
	lw t0, 52(sp)
	lw t0, 0(t0)
	sw t0, 20(sp)
	lw t0, 24(sp)
	li t1, 40
	mul t1, t1, t0
	li t0, 20
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 16(sp)
	li t0, 0
	li t1, 4
	mul t1, t1, t0
	li t0, 16
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 12(sp)
	lw a0, 28(sp)
	lw a1, 12(sp)
	call init1d
	lw t0, 44(sp)
	lw t0, 0(t0)
	sw t0, 8(sp)
	li t0, 1
	sw t0, 4(sp)
	lw t1, 8(sp)
	lw t2, 4(sp)
	add t0, t1, t2
	sw t0, 0(sp)
	lw t0, 0(sp)
	li t1, 44
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_6
while_end_8:
	li t0, 68
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 72
	add sp, sp, t0
	ret

	.globl init3d
init3d:
	li t0, 72
	sub sp, sp, t0
	li t0, 68
	add t0, t0, sp
	sw ra, 0(t0)
entry_9:
	li t0, 60
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a0
	li t1, 60
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 52
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a1
	li t1, 52
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 44
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 44
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_10
while_exp_10:
	lw t0, 44(sp)
	lw t0, 0(t0)
	sw t0, 40(sp)
	lw t0, 60(sp)
	lw t0, 0(t0)
	sw t0, 36(sp)
	lw t1, 40(sp)
	lw t2, 36(sp)
	slt t0, t1, t2
	sw t0, 32(sp)
	lw t0, 32(sp)
	bnez t0, while_loop_11
	j while_end_12
while_loop_11:
	li t0, 10
	sw t0, 28(sp)
	lw t0, 44(sp)
	lw t0, 0(t0)
	sw t0, 24(sp)
	lw t0, 52(sp)
	lw t0, 0(t0)
	sw t0, 20(sp)
	lw t0, 24(sp)
	li t1, 400
	mul t1, t1, t0
	li t0, 20
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 16(sp)
	li t0, 0
	li t1, 40
	mul t1, t1, t0
	li t0, 16
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 12(sp)
	lw a0, 28(sp)
	lw a1, 12(sp)
	call init2d
	lw t0, 44(sp)
	lw t0, 0(t0)
	sw t0, 8(sp)
	li t0, 1
	sw t0, 4(sp)
	lw t1, 8(sp)
	lw t2, 4(sp)
	add t0, t1, t2
	sw t0, 0(sp)
	lw t0, 0(sp)
	li t1, 44
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_10
while_end_12:
	li t0, 68
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 72
	add sp, sp, t0
	ret

	.globl sum1d
sum1d:
	li t0, 88
	sub sp, sp, t0
	li t0, 84
	add t0, t0, sp
	sw ra, 0(t0)
entry_13:
	li t0, 76
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a0
	li t1, 76
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 68
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a1
	li t1, 68
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 60
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 60
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 52
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 52
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_14
while_exp_14:
	lw t0, 60(sp)
	lw t0, 0(t0)
	sw t0, 48(sp)
	lw t0, 76(sp)
	lw t0, 0(t0)
	sw t0, 44(sp)
	lw t1, 48(sp)
	lw t2, 44(sp)
	slt t0, t1, t2
	sw t0, 40(sp)
	lw t0, 40(sp)
	bnez t0, while_loop_15
	j while_end_16
while_loop_15:
	lw t0, 52(sp)
	lw t0, 0(t0)
	sw t0, 36(sp)
	lw t0, 60(sp)
	lw t0, 0(t0)
	sw t0, 32(sp)
	lw t0, 68(sp)
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
	lw t0, 24(sp)
	lw t0, 0(t0)
	sw t0, 20(sp)
	lw t1, 36(sp)
	lw t2, 20(sp)
	add t0, t1, t2
	sw t0, 16(sp)
	lw t0, 16(sp)
	li t1, 52
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 60(sp)
	lw t0, 0(t0)
	sw t0, 12(sp)
	li t0, 1
	sw t0, 8(sp)
	lw t1, 12(sp)
	lw t2, 8(sp)
	add t0, t1, t2
	sw t0, 4(sp)
	lw t0, 4(sp)
	li t1, 60
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_14
while_end_16:
	lw t0, 52(sp)
	lw t0, 0(t0)
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	li t0, 84
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 88
	add sp, sp, t0
	ret

	.globl sum2d
sum2d:
	li t0, 96
	sub sp, sp, t0
	li t0, 92
	add t0, t0, sp
	sw ra, 0(t0)
entry_17:
	li t0, 84
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a0
	li t1, 84
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 76
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a1
	li t1, 76
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 68
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 68
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 60
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 60
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_18
while_exp_18:
	lw t0, 68(sp)
	lw t0, 0(t0)
	sw t0, 56(sp)
	lw t0, 84(sp)
	lw t0, 0(t0)
	sw t0, 52(sp)
	lw t1, 56(sp)
	lw t2, 52(sp)
	slt t0, t1, t2
	sw t0, 48(sp)
	lw t0, 48(sp)
	bnez t0, while_loop_19
	j while_end_20
while_loop_19:
	lw t0, 60(sp)
	lw t0, 0(t0)
	sw t0, 44(sp)
	li t0, 10
	sw t0, 40(sp)
	lw t0, 68(sp)
	lw t0, 0(t0)
	sw t0, 36(sp)
	lw t0, 76(sp)
	lw t0, 0(t0)
	sw t0, 32(sp)
	lw t0, 36(sp)
	li t1, 40
	mul t1, t1, t0
	li t0, 32
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 28(sp)
	li t0, 0
	li t1, 4
	mul t1, t1, t0
	li t0, 28
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 24(sp)
	lw a0, 40(sp)
	lw a1, 24(sp)
	call sum1d
	sw a0, 20(sp)
	lw t1, 44(sp)
	lw t2, 20(sp)
	add t0, t1, t2
	sw t0, 16(sp)
	lw t0, 16(sp)
	li t1, 60
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 68(sp)
	lw t0, 0(t0)
	sw t0, 12(sp)
	li t0, 1
	sw t0, 8(sp)
	lw t1, 12(sp)
	lw t2, 8(sp)
	add t0, t1, t2
	sw t0, 4(sp)
	lw t0, 4(sp)
	li t1, 68
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_18
while_end_20:
	lw t0, 60(sp)
	lw t0, 0(t0)
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	li t0, 92
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 96
	add sp, sp, t0
	ret

	.globl sum3d
sum3d:
	li t0, 96
	sub sp, sp, t0
	li t0, 92
	add t0, t0, sp
	sw ra, 0(t0)
entry_21:
	li t0, 84
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a0
	li t1, 84
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 76
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	mv t0, a1
	li t1, 76
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 68
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 68
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 60
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 60
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_22
while_exp_22:
	lw t0, 68(sp)
	lw t0, 0(t0)
	sw t0, 56(sp)
	lw t0, 84(sp)
	lw t0, 0(t0)
	sw t0, 52(sp)
	lw t1, 56(sp)
	lw t2, 52(sp)
	slt t0, t1, t2
	sw t0, 48(sp)
	lw t0, 48(sp)
	bnez t0, while_loop_23
	j while_end_24
while_loop_23:
	lw t0, 60(sp)
	lw t0, 0(t0)
	sw t0, 44(sp)
	li t0, 10
	sw t0, 40(sp)
	lw t0, 68(sp)
	lw t0, 0(t0)
	sw t0, 36(sp)
	lw t0, 76(sp)
	lw t0, 0(t0)
	sw t0, 32(sp)
	lw t0, 36(sp)
	li t1, 400
	mul t1, t1, t0
	li t0, 32
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 28(sp)
	li t0, 0
	li t1, 40
	mul t1, t1, t0
	li t0, 28
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 24(sp)
	lw a0, 40(sp)
	lw a1, 24(sp)
	call sum2d
	sw a0, 20(sp)
	lw t1, 44(sp)
	lw t2, 20(sp)
	add t0, t1, t2
	sw t0, 16(sp)
	lw t0, 16(sp)
	li t1, 60
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 68(sp)
	lw t0, 0(t0)
	sw t0, 12(sp)
	li t0, 1
	sw t0, 8(sp)
	lw t1, 12(sp)
	lw t2, 8(sp)
	add t0, t1, t2
	sw t0, 4(sp)
	lw t0, 4(sp)
	li t1, 68
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_22
while_end_24:
	lw t0, 60(sp)
	lw t0, 0(t0)
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	li t0, 92
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 96
	add sp, sp, t0
	ret

	.globl main
main:
	li t0, 4112
	sub sp, sp, t0
	li t0, 4108
	add t0, t0, sp
	sw ra, 0(t0)
entry_25:
	li t0, 104
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 10
	sw t0, 100(sp)
	li t0, 0
	li t1, 400
	mul t1, t1, t0
	li t0, 104
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 96(sp)
	lw a0, 100(sp)
	lw a1, 96(sp)
	call init3d
	li t0, 88
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 10
	sw t0, 84(sp)
	li t0, 0
	li t1, 400
	mul t1, t1, t0
	li t0, 104
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 80(sp)
	lw a0, 84(sp)
	lw a1, 80(sp)
	call sum3d
	sw a0, 76(sp)
	lw t0, 76(sp)
	li t1, 88
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 88(sp)
	lw t0, 0(t0)
	sw t0, 72(sp)
	li t0, 10
	sw t0, 68(sp)
	li t0, 1
	sw t0, 64(sp)
	lw t0, 64(sp)
	li t1, 400
	mul t1, t1, t0
	li t0, 104
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 60(sp)
	li t0, 0
	li t1, 40
	mul t1, t1, t0
	li t0, 60
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 56(sp)
	lw a0, 68(sp)
	lw a1, 56(sp)
	call sum2d
	sw a0, 52(sp)
	lw t1, 72(sp)
	lw t2, 52(sp)
	add t0, t1, t2
	sw t0, 48(sp)
	lw t0, 48(sp)
	li t1, 88
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 88(sp)
	lw t0, 0(t0)
	sw t0, 44(sp)
	li t0, 10
	sw t0, 40(sp)
	li t0, 2
	sw t0, 36(sp)
	li t0, 3
	sw t0, 32(sp)
	lw t0, 36(sp)
	li t1, 400
	mul t1, t1, t0
	li t0, 104
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 28(sp)
	lw t0, 32(sp)
	li t1, 40
	mul t1, t1, t0
	li t0, 28
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 24(sp)
	li t0, 0
	li t1, 4
	mul t1, t1, t0
	li t0, 24
	add t0, t0, sp
	lw t0, 0(t0)
	add t0, t0, t1
	sw t0, 20(sp)
	lw a0, 40(sp)
	lw a1, 20(sp)
	call sum1d
	sw a0, 16(sp)
	lw t1, 44(sp)
	lw t2, 16(sp)
	add t0, t1, t2
	sw t0, 12(sp)
	lw t0, 12(sp)
	li t1, 88
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 88(sp)
	lw t0, 0(t0)
	sw t0, 8(sp)
	lw a0, 8(sp)
	call putint
	li t0, 10
	sw t0, 4(sp)
	lw a0, 4(sp)
	call putch
	lw t0, 88(sp)
	lw t0, 0(t0)
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	li t0, 4108
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 4112
	add sp, sp, t0
	ret

