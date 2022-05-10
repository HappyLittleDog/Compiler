	.text
	.globl main
main:
	addi sp, sp, -8
	sw ra, 4(sp)
entry_1:
	call getint
	sw a0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	lw ra, 4(sp)
	addi sp, sp, 8
	ret

