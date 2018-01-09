.global main
.text
main:
    ldr r0, =limite
    ldr r1, [r0]
    add r0, r0, #3
    ldr r2, [r0]
    swi 0x123456
.data
limite:
    .word 0x12345678
