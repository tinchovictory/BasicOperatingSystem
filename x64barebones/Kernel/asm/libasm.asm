GLOBAL cpuVendor
GLOBAL testInterruptions

section .text

testInterruptions:
	push rbp
	mov rbp, rsp

	int 80h

	mov rsp, rbp
	pop rbp
	ret


cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid

	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret
