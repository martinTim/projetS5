.global main
.text

main:
	mov r0, #0x00000010
    mov r1, #0xFFFFFFFF
    mov r2, #0xFFFFFF0F
    cmp r0, #0x00000011
    bcc main
    tst r2,r0
    adds r0,r0,r0
    sbc r3,r0,r0 
    rscs r4, r2, r1
fin:
	swi 0x123456
.data
