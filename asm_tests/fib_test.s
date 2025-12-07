start:
    addi    x6,  x0, 10        # t3 = n = 5

    addi    x5,  x0, 0        # t0 = f0 = 0
    addi    x31, x0, 1        # f1 = 1

    beq     x6,  x0, done_zero   # if n == 0
    addi    x7,  x0, 1           # t4 = 1
    beq     x6,  x7, done_one    # if n == 1

    addi    x4,  x0, 1        # t2 = i = 1

loop:
    blt     x6,  x4, after_loop   # if n < i → done
    add     x28, x5, x31          # t5 = f0 + f1
    add     x5,  x31, x0          # f0 = f1
    add     x31, x28, x0          # f1 = t5
    addi    x4,  x4, 1            # i++
    blt     x4,  x6, loop         # if i < n → loop

after_loop:
    add     x10, x31, x0          # a0 = f1
    jal     x0, hang

done_zero:
    add     x10, x0, x0           # a0 = 0
    jal     x0, hang

done_one:
    add     x10, x31, x0          # a0 = 1
    jal     x0, hang
hang: