.global main
.text
decr:
    subs r0, r0, #1
    add r1,r1,#1
    mov pc, lr

main:
    mov r0, #5
loop:
    bl decr
    bne loop
    mvn r0,#0
end:
    swi 0x123456
.data
