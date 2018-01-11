.global main
.text

main:
    mov r0, #500
	ldr r15,[r0]
	ldrb r13,[r0]
	mov r0, #1
    

end:
    swi 0x123456
.data
