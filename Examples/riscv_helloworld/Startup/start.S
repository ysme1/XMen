.extern main

.global _start
.text
_start:

    call main
    
loop:
    wfi
    j loop
    