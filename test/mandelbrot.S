	.text
	.globl main
main:
	li t0, 688
	sub sp, sp, t0
	li t0, 684
	add t0, t0, sp
	sw ra, 0(t0)
entry_1:
	li t0, 676
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	call getint
	sw a0, 672(sp)
	lw t0, 672(sp)
	li t1, 676
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 664
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	call getint
	sw a0, 660(sp)
	lw t0, 660(sp)
	li t1, 664
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 652
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	call getint
	sw a0, 648(sp)
	lw t0, 648(sp)
	li t1, 652
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 640
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	call getint
	sw a0, 636(sp)
	lw t0, 636(sp)
	li t1, 640
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 628
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	call getint
	sw a0, 624(sp)
	lw t0, 624(sp)
	li t1, 628
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 616
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	call getint
	sw a0, 612(sp)
	lw t0, 612(sp)
	li t1, 616
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 604
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 616(sp)
	lw t0, 0(t0)
	sw t0, 600(sp)
	lw a0, 600(sp)
	call to_fp
	sw a0, 596(sp)
	lw t0, 640(sp)
	lw t0, 0(t0)
	sw t0, 592(sp)
	lw t0, 652(sp)
	lw t0, 0(t0)
	sw t0, 588(sp)
	lw a0, 592(sp)
	lw a1, 588(sp)
	call fp_sub
	sw a0, 584(sp)
	lw a0, 596(sp)
	lw a1, 584(sp)
	call fp_mul
	sw a0, 580(sp)
	lw t0, 664(sp)
	lw t0, 0(t0)
	sw t0, 576(sp)
	lw t0, 676(sp)
	lw t0, 0(t0)
	sw t0, 572(sp)
	lw a0, 576(sp)
	lw a1, 572(sp)
	call fp_sub
	sw a0, 568(sp)
	lw a0, 580(sp)
	lw a1, 568(sp)
	call fp_div
	sw a0, 564(sp)
	lw a0, 564(sp)
	call to_int
	sw a0, 560(sp)
	lw t0, 560(sp)
	li t1, 604
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 80
	sw t0, 556(sp)
	lw a0, 556(sp)
	call putch
	li t0, 51
	sw t0, 552(sp)
	lw a0, 552(sp)
	call putch
	li t0, 10
	sw t0, 548(sp)
	lw a0, 548(sp)
	call putch
	lw t0, 616(sp)
	lw t0, 0(t0)
	sw t0, 544(sp)
	lw a0, 544(sp)
	call putint
	li t0, 32
	sw t0, 540(sp)
	lw a0, 540(sp)
	call putch
	lw t0, 604(sp)
	lw t0, 0(t0)
	sw t0, 536(sp)
	lw a0, 536(sp)
	call putint
	li t0, 10
	sw t0, 532(sp)
	lw a0, 532(sp)
	call putch
	li t0, 255
	sw t0, 528(sp)
	lw a0, 528(sp)
	call putint
	li t0, 10
	sw t0, 524(sp)
	lw a0, 524(sp)
	call putch
	li t0, 516
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 508
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 500
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 492
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 484
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 476
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 468
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 476
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_2
while_exp_2:
	lw t0, 476(sp)
	lw t0, 0(t0)
	sw t0, 464(sp)
	lw t0, 604(sp)
	lw t0, 0(t0)
	sw t0, 460(sp)
	lw t1, 464(sp)
	lw t2, 460(sp)
	slt t0, t1, t2
	sw t0, 456(sp)
	lw t0, 456(sp)
	bnez t0, while_loop_3
	j while_end_4
while_loop_3:
	lw t0, 640(sp)
	lw t0, 0(t0)
	sw t0, 452(sp)
	lw t0, 476(sp)
	lw t0, 0(t0)
	sw t0, 448(sp)
	lw a0, 448(sp)
	call to_fp
	sw a0, 444(sp)
	lw t0, 640(sp)
	lw t0, 0(t0)
	sw t0, 440(sp)
	lw t0, 652(sp)
	lw t0, 0(t0)
	sw t0, 436(sp)
	lw a0, 440(sp)
	lw a1, 436(sp)
	call fp_sub
	sw a0, 432(sp)
	lw a0, 444(sp)
	lw a1, 432(sp)
	call fp_mul
	sw a0, 428(sp)
	lw t0, 604(sp)
	lw t0, 0(t0)
	sw t0, 424(sp)
	lw a0, 424(sp)
	call to_fp
	sw a0, 420(sp)
	lw a0, 428(sp)
	lw a1, 420(sp)
	call fp_div
	sw a0, 416(sp)
	lw a0, 452(sp)
	lw a1, 416(sp)
	call fp_sub
	sw a0, 412(sp)
	lw t0, 412(sp)
	li t1, 508
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 0
	li t1, 484
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_5
while_end_4:
	li t0, 0
	sw t0, 408(sp)
	lw t0, 408(sp)
	mv a0, t0
	li t0, 684
	add t0, t0, sp
	lw ra, 0(t0)
	li t0, 688
	add sp, sp, t0
	ret
while_exp_5:
	lw t0, 484(sp)
	lw t0, 0(t0)
	sw t0, 404(sp)
	lw t0, 616(sp)
	lw t0, 0(t0)
	sw t0, 400(sp)
	lw t1, 404(sp)
	lw t2, 400(sp)
	slt t0, t1, t2
	sw t0, 396(sp)
	lw t0, 396(sp)
	bnez t0, while_loop_6
	j while_end_7
while_loop_6:
	li t0, 388
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 388
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 380
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 380
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 372
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 372
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 364
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	li t0, 0
	li t1, 364
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 676(sp)
	lw t0, 0(t0)
	sw t0, 360(sp)
	lw t0, 484(sp)
	lw t0, 0(t0)
	sw t0, 356(sp)
	lw a0, 356(sp)
	call to_fp
	sw a0, 352(sp)
	lw t0, 664(sp)
	lw t0, 0(t0)
	sw t0, 348(sp)
	lw t0, 676(sp)
	lw t0, 0(t0)
	sw t0, 344(sp)
	lw a0, 348(sp)
	lw a1, 344(sp)
	call fp_sub
	sw a0, 340(sp)
	lw a0, 352(sp)
	lw a1, 340(sp)
	call fp_mul
	sw a0, 336(sp)
	lw t0, 616(sp)
	lw t0, 0(t0)
	sw t0, 332(sp)
	lw a0, 332(sp)
	call to_fp
	sw a0, 328(sp)
	lw a0, 336(sp)
	lw a1, 328(sp)
	call fp_div
	sw a0, 324(sp)
	lw a0, 360(sp)
	lw a1, 324(sp)
	call fp_add
	sw a0, 320(sp)
	lw t0, 320(sp)
	li t1, 516
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 1
	li t1, 468
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_8
while_end_7:
	li t0, 10
	sw t0, 316(sp)
	lw a0, 316(sp)
	call putch
	lw t0, 476(sp)
	lw t0, 0(t0)
	sw t0, 312(sp)
	li t0, 1
	sw t0, 308(sp)
	lw t1, 312(sp)
	lw t2, 308(sp)
	add t0, t1, t2
	sw t0, 304(sp)
	lw t0, 304(sp)
	li t1, 476
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_2
while_exp_8:
	li t0, 296
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 468(sp)
	lw t0, 0(t0)
	sw t0, 292(sp)
	lw t0, 628(sp)
	lw t0, 0(t0)
	sw t0, 288(sp)
	lw t1, 292(sp)
	lw t2, 288(sp)
	slt t0, t1, t2
	sw t0, 284(sp)
	lw t1, 284(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 280(sp)
	lw t0, 280(sp)
	li t1, 296
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 280(sp)
	bnez t0, and_11
	j endand_12
and_11:
	lw t0, 372(sp)
	lw t0, 0(t0)
	sw t0, 276(sp)
	lw t0, 364(sp)
	lw t0, 0(t0)
	sw t0, 272(sp)
	lw a0, 276(sp)
	lw a1, 272(sp)
	call fp_add
	sw a0, 268(sp)
	li t0, 4
	sw t0, 264(sp)
	lw a0, 264(sp)
	call to_fp
	sw a0, 260(sp)
	lw a0, 268(sp)
	lw a1, 260(sp)
	call fp_lt
	sw a0, 256(sp)
	lw t1, 256(sp)
	addi t0, t1, 0
	snez t0, t0
	sw t0, 252(sp)
	lw t1, 280(sp)
	lw t2, 252(sp)
	and t0, t1, t2
	sw t0, 248(sp)
	lw t0, 248(sp)
	li t1, 296
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j endand_12
endand_12:
	lw t0, 296(sp)
	lw t0, 0(t0)
	sw t0, 244(sp)
	lw t0, 244(sp)
	bnez t0, while_loop_9
	j while_end_10
while_loop_9:
	li t0, 2
	sw t0, 240(sp)
	lw a0, 240(sp)
	call to_fp
	sw a0, 236(sp)
	lw t0, 388(sp)
	lw t0, 0(t0)
	sw t0, 232(sp)
	lw a0, 236(sp)
	lw a1, 232(sp)
	call fp_mul
	sw a0, 228(sp)
	lw t0, 380(sp)
	lw t0, 0(t0)
	sw t0, 224(sp)
	lw a0, 228(sp)
	lw a1, 224(sp)
	call fp_mul
	sw a0, 220(sp)
	lw t0, 508(sp)
	lw t0, 0(t0)
	sw t0, 216(sp)
	lw a0, 220(sp)
	lw a1, 216(sp)
	call fp_add
	sw a0, 212(sp)
	lw t0, 212(sp)
	li t1, 380
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 372(sp)
	lw t0, 0(t0)
	sw t0, 208(sp)
	lw t0, 364(sp)
	lw t0, 0(t0)
	sw t0, 204(sp)
	lw a0, 208(sp)
	lw a1, 204(sp)
	call fp_sub
	sw a0, 200(sp)
	lw t0, 516(sp)
	lw t0, 0(t0)
	sw t0, 196(sp)
	lw a0, 200(sp)
	lw a1, 196(sp)
	call fp_add
	sw a0, 192(sp)
	lw t0, 192(sp)
	li t1, 388
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 388(sp)
	lw t0, 0(t0)
	sw t0, 188(sp)
	lw t0, 388(sp)
	lw t0, 0(t0)
	sw t0, 184(sp)
	lw a0, 188(sp)
	lw a1, 184(sp)
	call fp_mul
	sw a0, 180(sp)
	lw t0, 180(sp)
	li t1, 372
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 380(sp)
	lw t0, 0(t0)
	sw t0, 176(sp)
	lw t0, 380(sp)
	lw t0, 0(t0)
	sw t0, 172(sp)
	lw a0, 176(sp)
	lw a1, 172(sp)
	call fp_mul
	sw a0, 168(sp)
	lw t0, 168(sp)
	li t1, 364
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 468(sp)
	lw t0, 0(t0)
	sw t0, 164(sp)
	li t0, 1
	sw t0, 160(sp)
	lw t1, 164(sp)
	lw t2, 160(sp)
	add t0, t1, t2
	sw t0, 156(sp)
	lw t0, 156(sp)
	li t1, 468
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_8
while_end_10:
	lw t0, 468(sp)
	lw t0, 0(t0)
	sw t0, 152(sp)
	lw t0, 628(sp)
	lw t0, 0(t0)
	sw t0, 148(sp)
	lw t1, 152(sp)
	lw t2, 148(sp)
	slt t0, t1, t2
	seqz t0, t0
	sw t0, 144(sp)
	lw t0, 144(sp)
	bnez t0, then_13
	j else_14
then_13:
	li t0, 0
	sw t0, 140(sp)
	lw a0, 140(sp)
	call putint
	li t0, 32
	sw t0, 136(sp)
	lw a0, 136(sp)
	call putch
	li t0, 0
	sw t0, 132(sp)
	lw a0, 132(sp)
	call putint
	li t0, 32
	sw t0, 128(sp)
	lw a0, 128(sp)
	call putch
	li t0, 0
	sw t0, 124(sp)
	lw a0, 124(sp)
	call putint
	li t0, 32
	sw t0, 120(sp)
	lw a0, 120(sp)
	call putch
	j end_15
else_14:
	li t0, 112
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 468(sp)
	lw t0, 0(t0)
	sw t0, 108(sp)
	li t0, 128
	sw t0, 104(sp)
	lw t1, 108(sp)
	lw t2, 104(sp)
	mul t0, t1, t2
	sw t0, 100(sp)
	lw t0, 628(sp)
	lw t0, 0(t0)
	sw t0, 96(sp)
	lw t1, 100(sp)
	lw t2, 96(sp)
	div t0, t1, t2
	sw t0, 92(sp)
	lw t0, 92(sp)
	li t1, 112
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 84
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 468(sp)
	lw t0, 0(t0)
	sw t0, 80(sp)
	li t0, 192
	sw t0, 76(sp)
	lw t1, 80(sp)
	lw t2, 76(sp)
	mul t0, t1, t2
	sw t0, 72(sp)
	lw t0, 628(sp)
	lw t0, 0(t0)
	sw t0, 68(sp)
	lw t1, 72(sp)
	lw t2, 68(sp)
	div t0, t1, t2
	sw t0, 64(sp)
	lw t0, 64(sp)
	li t1, 84
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	li t0, 56
	add t0, sp, t0
	addi t1, t0, 4
	sw t1, 0(t0)
	lw t0, 468(sp)
	lw t0, 0(t0)
	sw t0, 52(sp)
	li t0, 255
	sw t0, 48(sp)
	lw t1, 52(sp)
	lw t2, 48(sp)
	mul t0, t1, t2
	sw t0, 44(sp)
	lw t0, 628(sp)
	lw t0, 0(t0)
	sw t0, 40(sp)
	lw t1, 44(sp)
	lw t2, 40(sp)
	div t0, t1, t2
	sw t0, 36(sp)
	lw t0, 36(sp)
	li t1, 56
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	lw t0, 112(sp)
	lw t0, 0(t0)
	sw t0, 32(sp)
	lw a0, 32(sp)
	call putint
	li t0, 32
	sw t0, 28(sp)
	lw a0, 28(sp)
	call putch
	lw t0, 84(sp)
	lw t0, 0(t0)
	sw t0, 24(sp)
	lw a0, 24(sp)
	call putint
	li t0, 32
	sw t0, 20(sp)
	lw a0, 20(sp)
	call putch
	lw t0, 56(sp)
	lw t0, 0(t0)
	sw t0, 16(sp)
	lw a0, 16(sp)
	call putint
	li t0, 32
	sw t0, 12(sp)
	lw a0, 12(sp)
	call putch
	j end_15
end_15:
	lw t0, 484(sp)
	lw t0, 0(t0)
	sw t0, 8(sp)
	li t0, 1
	sw t0, 4(sp)
	lw t1, 8(sp)
	lw t2, 4(sp)
	add t0, t1, t2
	sw t0, 0(sp)
	lw t0, 0(sp)
	li t1, 484
	add t1, t1, sp
	lw t1, 0(t1)
	sw t0, 0(t1)
	j while_exp_5

