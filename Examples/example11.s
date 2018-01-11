.global main
.text
saut:
	bic r4, r0
	teq r4, r0
	bcs fin

main:
    mov r0, #0xFF
    mov r1, #0xFFFFFFFF
    mov r2, #0xAA
	cmn r0, r1
	mrs r5, cpsr
	adc r3, r0, r1
	rsbs r4, r2, #0x80000000
	bvs saut
fin:
	swi 0x123456
.data
