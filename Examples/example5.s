.global main
.text
main:
    add r0, r0, #5
    mov r0, #4
    mov r1, #1024
    str r0, [r1]
    ldrb r2, [r1]
    swi 0x123456
