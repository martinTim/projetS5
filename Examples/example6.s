.global main
.text
main:
    add r0, r0, #5
    mov r0, #20
    mov r1, #1024
    ldr r0, =donnee
    ldr r1, [r0]
    swi 0x123456
.data
donnee:
    .word 0x42
fin:
