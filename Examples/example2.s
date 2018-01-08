.global main
.text
main:
    add r0, r0, #5
    add r0, r0, #5
    mov r0, #0x12
    mov r1, #0x34
    mov r3, #8
    add r0, r1, r0, lsl r3
    mov r1, #0x56
    add r0, r1, r0, lsl r3
    mov r1, #0x78
    add r0, r1, r0, lsl r3
    mov r1, #0x2000
    str r0, [r1]
    ldrb r2, [r1]
    add r1, r1, #3
    ldrb r3, [r1]
    swi 0x123456
