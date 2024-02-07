print:
    mov bx, 0
.loop:ORG 0x7c00
BITS 16

start: 
    mov si, message
    call print
    jmp $
 
print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call print_charORG 0x7c00
BITS 16
 
start: 
    mov si, message
    call print
    jmp $

print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db 'Hello World!', 0

times 510- ($ - $$) db 0
dw 0xAA55

    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db 'Hello World!', 0

times 510- ($ - $$) db 0
dw 0xAA55

    lodsb
    cmp al, 0
    je .done
    call print_charORG 0x7c00
BITS 16

start: 
    mov si, message
    call print
    jmp $

print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db 'Hello World!', 0

times 510- ($ - $$) db 0
dw 0xAA55

    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db 'Hello World!', 0

times 510- ($ - $$) db 0
dw 0xAA55
ORG 0x7c00
BITS 16

start: 
    mov si, message
    call print
    jmp $

print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db 'Hello World!', 0

times 510- ($ - $$) db 0
dw 0xAA55
ORG 0x7c00
BITS 16

start: 
    mov si, message
    call print
    jmp $

print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    retORG 0x7c00
BITS 16

start: 
    mov si, message
    call print
    jmp $

print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db 'Hello World!', 0

times 510- ($ - $$) db 0
dw 0xAA55


message: db 'Hello World!', 0

times 510- ($ - $$) db 0
dw 0xAA55
ORG 0x7c00ORG 0x7c00
BITS 16

start: 
    mov si, message
    call print
    jmp $

print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db 'Hello World!', 0

times 510- ($ - $$) db 0
dw 0xAA55

BITS 16

start: 
    mov si, message
    call print
    jmp $

print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db 'Hello World!', 0

times 510- ($ - $$) db 0
dw 0xAA55
