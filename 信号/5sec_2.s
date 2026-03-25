	.file	"5sec_2.c"
	.text
	.type	sig_handler, @function
sig_handler:
.LFB52:
	.cfi_startproc
	movl	$0, loop(%rip)
	ret
	.cfi_endproc
.LFE52:
	.size	sig_handler, .-sig_handler
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%ld"
	.text
	.globl	main
	.type	main, @function
main:
.LFB53:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	leaq	sig_handler(%rip), %rsi
	movl	$14, %edi
	call	signal@PLT
	movl	$5, %edi
	call	alarm@PLT
	cmpl	$0, loop(%rip)
	je	.L3
.L4:
	jmp	.L4
.L3:
	movl	$0, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$0, %edi
	call	exit@PLT
	.cfi_endproc
.LFE53:
	.size	main, .-main
	.data
	.align 4
	.type	loop, @object
	.size	loop, 4
loop:
	.long	1
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
