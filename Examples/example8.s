.global main
.text

main:
    mov r0, #1
    mov r1, r0, lsl #30
    adds r0, r1, r0, lsl #30
    mrs r0,CPSR
    

end:
    swi 0x123456
.data
