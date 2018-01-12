.global main
.text
main:
    add r0, r0, #5
    mov r0, #20
    mov r1, #1024
    ldr r0, =donnee
    ldrb r1, [r0]
    ldrh r2, [r0]
    ldr r3, [r0]
    mov r1, #1024
    str r3, [r1]
    strb r3, [r1]
    strh r3, [r1]   
    swi 0x123456
.data
donnee:
    .word 0x12345678
fin:
