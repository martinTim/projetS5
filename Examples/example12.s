.global main
.text

main:
    mov r0, #0xFFFFFFFF
    add r1,r1,r0
	



fin:
	swi 0x123456
.data
