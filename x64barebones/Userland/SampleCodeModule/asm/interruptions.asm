GLOBAL testInterruptions

section .text

testInterruptions:
	push rbp
	mov rbp, rsp

	int 80h

	mov rsp, rbp
	pop rbp
	ret
