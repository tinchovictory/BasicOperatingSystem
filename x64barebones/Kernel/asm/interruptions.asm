GLOBAL sti
GLOBAL setPicMaster
GLOBAL irq0Handler
GLOBAL irq1Handler

EXTERN irqDispatcher

%include "./asm/macros.m"

section .text

irq0Handler:
	irqHandler 0
irq1Handler:
	irqHandler 1
	

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