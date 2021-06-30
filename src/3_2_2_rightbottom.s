.arm
.text

  mov     r1,     #0x04000000
  ldr     r2,     =0x0F03
  strh    r2,      [ r1 ]

  ldr     r3,     =0x06012BF2
  ldr     r4,     =0x7FFF
  strh    r4,     [ r3 ]
  strh    r4,     [ r3, #4 ]
  strh    r4,     [ r3, #8 ]
  strh    r4,     [ r3, #12]

hogehoge2:
  b hogehoge2
