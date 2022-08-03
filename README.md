# GRAM
GRAM is a register operation framework for embedded systems in C.
Aiming for two types of registers, **Memory-based Registers** and **Special Registers**, GRAM provides an unified coding style for C to access registers.
The core of GRAM is implemented in `include/gram.h`, which makes it can be easily integrated to existing projects.

## Supported Register Types
1. **Memory-based Registers** are sually binded to specific addresses and accessed by generic `load` and `store` instructions. E.g.,
   * `AUX_MU_LCR_REG Register` is located at `0x7E21504C` in Raspberry Pi 3 B+.
   * `USART_STAT Register` for USART0 is located at `0x40013800` in GD32VF103.
2. **Special Registers** usually reside in a processor, and accessed by specific instructions. E.g.,
   * `SCTLR_EL3` in `aarch64` is accessed by `mrs` and `msr` instructions.
   * `CP0 Cause` in `mips32` is accessed by `mfc0` and `mtc0` instructions.
   * `CSR MSTATUS` in `rv32` is accessed by `csrr` and `csrw` instructions.

## Example of GRAM
```C
int main(void) {
  REG32_DEMO_T r32;

  RRMW(REG32_DEMO,
    f31_16, 0x32,
    f0_0, 1);

  while (RFLD(REG32_DEMO, f1_1) != 1) {
    ;
  }

  r32.v = RGET(REG32_DEMO);

  RSET(REG32_DEMO, r32.v);

  return 0;
}
```
