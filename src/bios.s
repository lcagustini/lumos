.text
.align 2
.thumb_func
.type div, %function
div:
    swi 0x6
    mov pc, lr
