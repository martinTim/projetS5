.global main
.text
main:
    mov r1, #1024
    ldrb r0, [r1]
    swi 0x123456