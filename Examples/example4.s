.global main
.text
main:
    mov r0, #0xFF000
    mov r4, #1
    ldr r1, =donnee
    ldr r2, =fin
    ldmia r1!, {r6, r7}
    stmia r1, {r6,r7}

    swi 0x123456
.data
donnee:
    .word 0x11223344
    .word 0x55667788
fin:
