	.cpu arm7tdmi
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"tmp.c"
	.text
	.comm	board,128,4
	.comm	player_A,6,4
	.comm	player_B,6,4
	.global	key
	.data
	.align	2
	.type	key, %object
	.size	key, 4
key:
	.word	67109168
	.text
	.align	2
	.global	main
	.arch armv4t
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	mov	r3, #67108864
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	ldr	r2, .L3
	strh	r2, [r3]	@ movhi
	bl	play_othello
.L2:
	b	.L2
.L4:
	.align	2
.L3:
	.word	3843
	.size	main, .-main
	.align	2
	.global	play_othello
	.syntax unified
	.arm
	.fpu softvfp
	.type	play_othello, %function
play_othello:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	bl	init_board
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
	.size	play_othello, .-play_othello
	.align	2
	.global	div
	.syntax unified
	.arm
	.fpu softvfp
	.type	div, %function
div:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #20
	mov	r3, r0
	mov	r2, r1
	strh	r3, [fp, #-14]	@ movhi
	mov	r3, r2	@ movhi
	strh	r3, [fp, #-16]	@ movhi
	mov	r3, #0
	strh	r3, [fp, #-6]	@ movhi
	b	.L7
.L8:
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	ldrh	r2, [fp, #-14]	@ movhi
	lsl	r2, r2, #16
	lsr	r2, r2, #16
	sub	r3, r2, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-14]	@ movhi
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #1
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-6]	@ movhi
.L7:
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r2, r3
	bcs	.L8
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	div, .-div
	.align	2
	.global	put_piece
	.syntax unified
	.arm
	.fpu softvfp
	.type	put_piece, %function
put_piece:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	mov	r3, r0
	strh	r3, [fp, #-14]	@ movhi
	mov	r3, r1	@ movhi
	strh	r3, [fp, #-16]	@ movhi
	mov	r3, r2	@ movhi
	strh	r3, [fp, #-18]	@ movhi
	ldrsh	r3, [fp, #-18]
	cmp	r3, #1
	bne	.L11
	mov	r3, #0
	strh	r3, [fp, #-6]	@ movhi
	b	.L12
.L11:
	mvn	r3, #32768
	strh	r3, [fp, #-6]	@ movhi
.L12:
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r0, r3
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r1, r3
	ldr	r2, .L13
	lsl	r3, r0, #3
	add	r3, r3, r1
	lsl	r3, r3, #1
	add	r3, r2, r3
	ldrh	r2, [fp, #-18]	@ movhi
	strh	r2, [r3]	@ movhi
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r1, r3, #16
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, r3
	bl	draw_piece
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L14:
	.align	2
.L13:
	.word	board
	.size	put_piece, .-put_piece
	.align	2
	.global	move_player
	.syntax unified
	.arm
	.fpu softvfp
	.type	move_player, %function
move_player:
	@ Function supports interworking.
	@ args = 4, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	sub	ip, fp, #12
	stm	ip, {r0, r1}
	mov	r1, r2
	mov	r2, r3
	mov	r3, r1	@ movhi
	strh	r3, [fp, #-14]	@ movhi
	mov	r3, r2	@ movhi
	strh	r3, [fp, #-16]	@ movhi
	ldrsh	r3, [fp, #-12]
	mov	r2, r3
	ldrsh	r3, [fp, #-14]
	add	r3, r2, r3
	cmp	r3, #0
	blt	.L17
	ldrsh	r3, [fp, #-12]
	mov	r2, r3
	ldrsh	r3, [fp, #-14]
	add	r3, r2, r3
	cmp	r3, #7
	bgt	.L17
	ldrsh	r3, [fp, #-10]
	mov	r2, r3
	ldrsh	r3, [fp, #-16]
	add	r3, r2, r3
	cmp	r3, #0
	blt	.L17
	ldrsh	r3, [fp, #-10]
	mov	r2, r3
	ldrsh	r3, [fp, #-16]
	add	r3, r2, r3
	cmp	r3, #7
	bgt	.L17
	ldrsh	r3, [fp, #-12]
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrsh	r3, [fp, #-10]
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, #0
	mov	r1, r3
	bl	draw_player
	ldrsh	r3, [fp, #-12]
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-14]
	add	r3, r2, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	lsl	r3, r3, #16
	asr	r3, r3, #16
	strh	r3, [fp, #-12]	@ movhi
	ldrsh	r3, [fp, #-10]
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-16]
	add	r3, r2, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	lsl	r3, r3, #16
	asr	r3, r3, #16
	strh	r3, [fp, #-10]	@ movhi
	ldrsh	r3, [fp, #-12]
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrsh	r3, [fp, #-10]
	lsl	r3, r3, #16
	lsr	r1, r3, #16
	ldrh	r3, [fp, #4]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, r3
	bl	draw_player
.L17:
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
	.size	move_player, .-move_player
	.align	2
	.global	init_board
	.syntax unified
	.arm
	.fpu softvfp
	.type	init_board, %function
init_board:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	ldr	r0, .L23
	bl	draw_window
	mov	r3, #0
	strh	r3, [fp, #-8]	@ movhi
	b	.L19
.L22:
	mov	r3, #0
	strh	r3, [fp, #-6]	@ movhi
	b	.L20
.L21:
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrh	r3, [fp, #-8]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, #992
	mov	r1, r3
	bl	draw_box_bg
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrh	r3, [fp, #-8]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, #0
	mov	r1, r3
	bl	draw_player
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #1
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-6]	@ movhi
.L20:
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r3, #7
	bls	.L21
	ldrh	r3, [fp, #-8]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #1
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-8]	@ movhi
.L19:
	ldrh	r3, [fp, #-8]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r3, #7
	bls	.L22
	bl	init_piece
	bl	init_player
	ldr	r3, .L23+4
	ldrsh	r3, [r3]
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldr	r3, .L23+4
	ldrsh	r3, [r3, #2]
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, #31
	mov	r1, r3
	bl	draw_player
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L24:
	.align	2
.L23:
	.word	25368
	.word	player_A
	.size	init_board, .-init_board
	.align	2
	.global	init_piece
	.syntax unified
	.arm
	.fpu softvfp
	.type	init_piece, %function
init_piece:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	mov	r2, #1
	mov	r1, #3
	mov	r0, #3
	bl	put_piece
	mov	r2, #1
	mov	r1, #4
	mov	r0, #4
	bl	put_piece
	mvn	r2, #0
	mov	r1, #4
	mov	r0, #3
	bl	put_piece
	mvn	r2, #0
	mov	r1, #3
	mov	r0, #4
	bl	put_piece
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
	.size	init_piece, .-init_piece
	.align	2
	.global	init_player
	.syntax unified
	.arm
	.fpu softvfp
	.type	init_player, %function
init_player:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L27
	mov	r2, #1
	strh	r2, [r3, #4]	@ movhi
	ldr	r3, .L27+4
	mvn	r2, #0
	strh	r2, [r3, #4]	@ movhi
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L28:
	.align	2
.L27:
	.word	player_A
	.word	player_B
	.size	init_player, .-init_player
	.align	2
	.global	draw_box_bg
	.syntax unified
	.arm
	.fpu softvfp
	.type	draw_box_bg, %function
draw_box_bg:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r5, fp, lr}
	add	fp, sp, #12
	sub	sp, sp, #24
	mov	r3, r0
	strh	r3, [fp, #-22]	@ movhi
	mov	r3, r1	@ movhi
	strh	r3, [fp, #-24]	@ movhi
	mov	r3, r2	@ movhi
	strh	r3, [fp, #-26]	@ movhi
	mov	r1, #2
	mov	r0, #240
	bl	div
	mov	r3, r0
	mov	r5, r3
	ldrh	r3, [fp, #-22]	@ movhi
	lsl	r3, r3, #16
	lsr	r4, r3, #16
	mov	r1, #2
	mov	r0, #8
	bl	div
	mov	r3, r0
	sub	r3, r4, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	lsl	r3, r3, #4
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r5, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-14]	@ movhi
	mov	r1, #2
	mov	r0, #160
	bl	div
	mov	r3, r0
	mov	r5, r3
	ldrh	r3, [fp, #-24]	@ movhi
	lsl	r3, r3, #16
	lsr	r4, r3, #16
	mov	r1, #2
	mov	r0, #8
	bl	div
	mov	r3, r0
	sub	r3, r4, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	lsl	r3, r3, #4
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r5, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-16]	@ movhi
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #16
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-18]	@ movhi
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #16
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-20]	@ movhi
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrh	r3, [fp, #-18]	@ movhi
	lsl	r3, r3, #16
	lsr	r1, r3, #16
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-20]	@ movhi
	lsl	r3, r3, #16
	lsr	ip, r3, #16
	ldrh	r3, [fp, #-26]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	str	r3, [sp]
	mov	r3, ip
	bl	draw_square
	nop
	sub	sp, fp, #12
	@ sp needed
	pop	{r4, r5, fp, lr}
	bx	lr
	.size	draw_box_bg, .-draw_box_bg
	.align	2
	.global	draw_player
	.syntax unified
	.arm
	.fpu softvfp
	.type	draw_player, %function
draw_player:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r5, fp, lr}
	add	fp, sp, #12
	sub	sp, sp, #16
	mov	r3, r0
	strh	r3, [fp, #-22]	@ movhi
	mov	r3, r1	@ movhi
	strh	r3, [fp, #-24]	@ movhi
	mov	r3, r2	@ movhi
	strh	r3, [fp, #-26]	@ movhi
	mov	r1, #2
	mov	r0, #240
	bl	div
	mov	r3, r0
	mov	r5, r3
	ldrh	r3, [fp, #-22]	@ movhi
	lsl	r3, r3, #16
	lsr	r4, r3, #16
	mov	r1, #2
	mov	r0, #8
	bl	div
	mov	r3, r0
	sub	r3, r4, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	lsl	r3, r3, #4
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r5, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-14]	@ movhi
	mov	r1, #2
	mov	r0, #160
	bl	div
	mov	r3, r0
	mov	r5, r3
	ldrh	r3, [fp, #-24]	@ movhi
	lsl	r3, r3, #16
	lsr	r4, r3, #16
	mov	r1, #2
	mov	r0, #8
	bl	div
	mov	r3, r0
	sub	r3, r4, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	lsl	r3, r3, #4
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r5, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-16]	@ movhi
	mov	r3, #0
	strh	r3, [fp, #-18]	@ movhi
	b	.L31
.L32:
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-18]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r2, r3
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r1, r3, #16
	ldrh	r3, [fp, #-26]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, r3
	bl	draw_point
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-18]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r2, r3
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #16
	lsl	r3, r3, #16
	lsr	r1, r3, #16
	ldrh	r3, [fp, #-26]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, r3
	bl	draw_point
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-18]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r2, r3
	lsl	r3, r3, #16
	lsr	r1, r3, #16
	ldrh	r3, [fp, #-26]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, r3
	bl	draw_point
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #16
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-18]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r2, r3
	lsl	r3, r3, #16
	lsr	r1, r3, #16
	ldrh	r3, [fp, #-26]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, r3
	bl	draw_point
	ldrh	r3, [fp, #-18]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #1
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-18]	@ movhi
.L31:
	ldrh	r3, [fp, #-18]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r3, #16
	bls	.L32
	nop
	nop
	sub	sp, fp, #12
	@ sp needed
	pop	{r4, r5, fp, lr}
	bx	lr
	.size	draw_player, .-draw_player
	.align	2
	.global	draw_piece
	.syntax unified
	.arm
	.fpu softvfp
	.type	draw_piece, %function
draw_piece:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r5, fp, lr}
	add	fp, sp, #12
	sub	sp, sp, #16
	mov	r3, r0
	strh	r3, [fp, #-22]	@ movhi
	mov	r3, r1	@ movhi
	strh	r3, [fp, #-24]	@ movhi
	mov	r3, r2	@ movhi
	strh	r3, [fp, #-26]	@ movhi
	mov	r1, #2
	mov	r0, #240
	bl	div
	mov	r3, r0
	mov	r5, r3
	ldrh	r3, [fp, #-22]	@ movhi
	lsl	r3, r3, #16
	lsr	r4, r3, #16
	mov	r1, #2
	mov	r0, #8
	bl	div
	mov	r3, r0
	sub	r3, r4, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	lsl	r3, r3, #4
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r5, r3
	lsl	r3, r3, #16
	lsr	r4, r3, #16
	mov	r1, #2
	mov	r0, #16
	bl	div
	mov	r3, r0
	add	r3, r4, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-14]	@ movhi
	mov	r1, #2
	mov	r0, #160
	bl	div
	mov	r3, r0
	mov	r5, r3
	ldrh	r3, [fp, #-24]	@ movhi
	lsl	r3, r3, #16
	lsr	r4, r3, #16
	mov	r1, #2
	mov	r0, #8
	bl	div
	mov	r3, r0
	sub	r3, r4, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	lsl	r3, r3, #4
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r5, r3
	lsl	r3, r3, #16
	lsr	r4, r3, #16
	mov	r1, #2
	mov	r0, #16
	bl	div
	mov	r3, r0
	add	r3, r4, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-16]	@ movhi
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r4, r3, #16
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r5, r3, #16
	mov	r1, #2
	mov	r0, #16
	bl	div
	mov	r3, r0
	mov	r2, r3
	ldrh	r3, [fp, #-26]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r1, r5
	mov	r0, r4
	bl	draw_circle
	nop
	sub	sp, fp, #12
	@ sp needed
	pop	{r4, r5, fp, lr}
	bx	lr
	.size	draw_piece, .-draw_piece
	.align	2
	.global	draw_circle
	.syntax unified
	.arm
	.fpu softvfp
	.type	draw_circle, %function
draw_circle:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	mov	ip, r0
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	mov	r3, ip	@ movhi
	strh	r3, [fp, #-22]	@ movhi
	mov	r3, r0	@ movhi
	strh	r3, [fp, #-24]	@ movhi
	mov	r3, r1	@ movhi
	strh	r3, [fp, #-26]	@ movhi
	mov	r3, r2	@ movhi
	strh	r3, [fp, #-28]	@ movhi
	ldrh	r3, [fp, #-22]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-26]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	sub	r3, r2, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-6]	@ movhi
	ldrh	r3, [fp, #-22]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-26]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r2, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-8]	@ movhi
	ldrh	r3, [fp, #-24]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-26]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	sub	r3, r2, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-10]	@ movhi
	ldrh	r3, [fp, #-24]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-26]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r2, r3
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-12]	@ movhi
	ldrh	r3, [fp, #-10]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-16]	@ movhi
	b	.L35
.L39:
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-14]	@ movhi
	b	.L36
.L38:
	ldrh	r3, [fp, #-26]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, r3
	ldrh	r3, [fp, #-26]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mul	r2, r3, r2
	ldrh	r3, [fp, #-22]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r1, r3
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	sub	r3, r1, r3
	ldrh	r1, [fp, #-22]	@ movhi
	lsl	r1, r1, #16
	lsr	r1, r1, #16
	mov	r0, r1
	ldrh	r1, [fp, #-14]	@ movhi
	lsl	r1, r1, #16
	lsr	r1, r1, #16
	sub	r1, r0, r1
	mul	r1, r3, r1
	ldrh	r3, [fp, #-24]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r0, r3
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	sub	r3, r0, r3
	ldrh	r0, [fp, #-24]	@ movhi
	lsl	r0, r0, #16
	lsr	r0, r0, #16
	mov	ip, r0
	ldrh	r0, [fp, #-16]	@ movhi
	lsl	r0, r0, #16
	lsr	r0, r0, #16
	sub	r0, ip, r0
	mul	r3, r0, r3
	add	r3, r1, r3
	cmp	r2, r3
	ble	.L37
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r1, r3, #16
	ldrh	r3, [fp, #-28]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, r3
	bl	draw_point
.L37:
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #1
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-14]	@ movhi
.L36:
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-8]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r2, r3
	bcc	.L38
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #1
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-16]	@ movhi
.L35:
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-12]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r2, r3
	bcc	.L39
	nop
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
	.size	draw_circle, .-draw_circle
	.align	2
	.global	draw_square
	.syntax unified
	.arm
	.fpu softvfp
	.type	draw_square, %function
draw_square:
	@ Function supports interworking.
	@ args = 4, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	mov	ip, r0
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	mov	r3, ip	@ movhi
	strh	r3, [fp, #-14]	@ movhi
	mov	r3, r0	@ movhi
	strh	r3, [fp, #-16]	@ movhi
	mov	r3, r1	@ movhi
	strh	r3, [fp, #-18]	@ movhi
	mov	r3, r2	@ movhi
	strh	r3, [fp, #-20]	@ movhi
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r2, r3
	bcs	.L41
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-10]	@ movhi
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-16]	@ movhi
	ldrh	r3, [fp, #-10]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-14]	@ movhi
.L41:
	ldrh	r3, [fp, #-20]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-18]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r2, r3
	bcs	.L42
	ldrh	r3, [fp, #-20]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-12]	@ movhi
	ldrh	r3, [fp, #-18]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-20]	@ movhi
	ldrh	r3, [fp, #-12]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-18]	@ movhi
.L42:
	ldrh	r3, [fp, #-18]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-8]	@ movhi
	b	.L43
.L46:
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-6]	@ movhi
	b	.L44
.L45:
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrh	r3, [fp, #-8]	@ movhi
	lsl	r3, r3, #16
	lsr	r1, r3, #16
	ldrh	r3, [fp, #4]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, r3
	bl	draw_point
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #1
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-6]	@ movhi
.L44:
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r2, r3
	bcc	.L45
	ldrh	r3, [fp, #-8]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #1
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-8]	@ movhi
.L43:
	ldrh	r3, [fp, #-8]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldrh	r3, [fp, #-20]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r2, r3
	bcc	.L46
	nop
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
	.size	draw_square, .-draw_square
	.align	2
	.global	draw_window
	.syntax unified
	.arm
	.fpu softvfp
	.type	draw_window, %function
draw_window:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	mov	r3, r0
	strh	r3, [fp, #-14]	@ movhi
	mov	r3, #0
	strh	r3, [fp, #-8]	@ movhi
	b	.L48
.L51:
	mov	r3, #0
	strh	r3, [fp, #-6]	@ movhi
	b	.L49
.L50:
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r0, r3, #16
	ldrh	r3, [fp, #-8]	@ movhi
	lsl	r3, r3, #16
	lsr	r1, r3, #16
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, r3
	bl	draw_point
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #1
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-6]	@ movhi
.L49:
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r3, #239
	bls	.L50
	ldrh	r3, [fp, #-8]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #1
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-8]	@ movhi
.L48:
	ldrh	r3, [fp, #-8]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r3, #159
	bls	.L51
	nop
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
	.size	draw_window, .-draw_window
	.align	2
	.global	draw_point
	.syntax unified
	.arm
	.fpu softvfp
	.type	draw_point, %function
draw_point:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #20
	mov	r3, r0
	strh	r3, [fp, #-14]	@ movhi
	mov	r3, r1	@ movhi
	strh	r3, [fp, #-16]	@ movhi
	mov	r3, r2	@ movhi
	strh	r3, [fp, #-18]	@ movhi
	mov	r3, #100663296
	str	r3, [fp, #-8]
	ldrh	r3, [fp, #-14]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r1, r3
	ldrh	r3, [fp, #-16]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	mov	r2, r3
	mov	r3, r2
	lsl	r3, r3, #4
	sub	r3, r3, r2
	lsl	r3, r3, #4
	add	r3, r1, r3
	lsl	r3, r3, #1
	ldr	r2, [fp, #-8]
	add	r3, r2, r3
	str	r3, [fp, #-8]
	ldrh	r3, [fp, #-18]	@ movhi
	lsl	r3, r3, #16
	lsr	r2, r3, #16
	ldr	r3, [fp, #-8]
	strh	r2, [r3]	@ movhi
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	draw_point, .-draw_point
	.align	2
	.global	generate_delay
	.syntax unified
	.arm
	.fpu softvfp
	.type	generate_delay, %function
generate_delay:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	mov	r3, #0
	strh	r3, [fp, #-6]	@ movhi
	b	.L54
.L55:
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	add	r3, r3, #1
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	strh	r3, [fp, #-6]	@ movhi
.L54:
	ldrh	r3, [fp, #-6]	@ movhi
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	ldr	r2, .L56
	cmp	r3, r2
	bls	.L55
	nop
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L57:
	.align	2
.L56:
	.word	4999
	.size	generate_delay, .-generate_delay
	.ident	"GCC: (GNU Tools for Arm Embedded Processors 9-2019-q4-major) 9.2.1 20191025 (release) [ARM/arm-9-branch revision 277599]"
