.data 0x0
    AAA:    .word   0x3F9409, -6:6
    BBB:    .word   0x123  :  3
            .half   0x456, 3:7
            .byte   -9, 10, 11, 12
    XXX:    .word   0x1, 0x999
    YYY:    .word   123
    ZZZ:    .word   0
            .word   16
.text 0x0
start:
    nop
main:
    # minsys-1
    add     $1, $2, $3
    addu    $1, $2, $3
    sub     $1, $2, $3
    subu    $1, $2, $3
    and     $1, $2, $3
    or      $1, $2, $3
    xor     $1, $2, $3
    nor     $1, $2, $3
    slt     $1, $2, $3
    sltu    $1, $2, $3
    sll     $1, $2, 10
    srl     $1, $2, 10
    sra     $1, $2, 10
    sllv    $1, $2, $3
    srlv    $1, $2, $3
    srav    $1, $2, $3
    jr      $31
    addi    $1, $2, 0x10
    addiu   $1, $2, -10
    andi    $1, $2, 10
    ori     $1, $2, 0x10
    xori    $1, $2, 10
    lui     $1, 10
    lw      $1, 10($2)
    sw      $1, AAA($2)
    beq     $1, $2, 10
    beq     $1, $2, start
    bne     $1, $2, 10
    bne     $1, $2, start
    slti    $1, $2, 10
    sltiu   $1, $2, 10
    j       100
    j       start
    jal     100
    jal     start

    # minisys-1A
    mult    $2, $3
    multu   $2, $3
    div     $2, $3
    divu    $2, $3
    mfhi    $1
    mflo    $1
    mthi    $1
    mtlo    $1
    mfc0    $3, $1, 0
    mtc0    $3, $1, 0
    jalr    $31, $3
    break
    syscall
    eret
    lb      $1, 10($2)
    lbu     $1, 10($2)
    lh      $1, 10($2)
    lhu     $1, 10($2)
    sb      $1, 10($2)
    sh      $1, 10($2)
    bgez    $1, 10
    bgtz    $1, 10
    blez    $1, 10
    bltz    $1, 10
    bgezal  $1, 10
    bltzal  $1, 10

    # 宏指令
    mov     $1, AAA($0)
    lw      $1, AAA($0)
    mov     AAA($0), $1
    sw      $1, AAA($0)
    push    $1
    pop     $1
