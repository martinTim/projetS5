.global main
.text
main:
    mov r0, #0xAB
    mov r1, r0, ror #1
    mov r2, r1, asr #10
    eor r3, r2, r1
    orr r4, r0, r1
    and r5, r3, r4
    mov r6, r5, lsl #8
    mov r7, r4, lsr #4
    swi 0x123456
