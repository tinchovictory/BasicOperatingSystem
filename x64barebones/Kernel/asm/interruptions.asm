GLOBAL sti
GLOBAL setPicMaster
GLOBAL irq0Handler
GLOBAL irq1Handler
GLOBAL sysCallHandler

EXTERN irqDispatcher
EXTERN systemCall

%include "./asm/macros.m"

section .text

irq0Handler:
	irqHandler 0
irq1Handler:
	irqHandler 1
	


sysCallHandler:
	pushaq

	;recivo parametros en un orden y los oredno en el orden que necesito

	
	call systemCall
	
	popaq
	iretq



sti:
	sti
	ret


	
setPicMaster:
	push rbp
	mov rbp, rsp
	
	mov rax, rdi
	out 21h, al
	
	mov rsp, rbp
	pop rbp
	ret