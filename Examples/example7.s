.global main
.text

foo:
	bal end

cible1:
    sub r0, r0, #1
    mov pc, lr

cible2:
	add r0, r0, #4
	mov pc, lr
	
main:
    mov r0, #5
etiq1:
    bl cible1

etiq2:
	bl cible2
	bal foo

end:
    swi 0x123456
.data
