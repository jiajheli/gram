# GRAM
GRAM is a register operation framework for embedded systems in C.
Aiming for two types of registers, **Memory-based Registers** and **Special Registers**, GRAM provides a unified coding style for C to declare and access registers.
GRAM is implemented in just two header files, `include/gram.h` and `include/gram_<arch>.h`. Which makes GRAM can be easily integrated to existing projects.

## Supported Register Types
1. **Memory-based Register** is usually bound to a specific address and accessed by generic `load` and `store` instructions. E.g.,
   * `AUX_MU_LCR_REG Register` is located at `0x7E21504C` in Raspberry Pi 3 B+.
   * `USART_STAT Register` for USART0 is located at `0x40013800` in GD32VF103.
2. **Special Register** usually resides in a processor and be accessed by specific instructions.
   * `SCTLR_EL3` in `aarch64` (`aa64`) is accessed by `mrs` and `msr` instructions.
   * `CP0 Cause` in `mips32` is accessed by `mfc0` and `mtc0` instructions.
   * `CSR MSTATUS` in `rv32` is accessed by `csrr` and `csrw` instructions.
   * Currently, GRAM supports `aarch64`, `mips32`, and `rv32`.

## Quick Start: Initialize Baud Rate of NS16550-compatible UART
```C
#define UART_BASE 0x01230000

//Declare a 8-bit register named DLL and comprised of just one field. Its offset to UART_BASE is 0x0.
GRAM8(
  DLL, UART_BASE, 0x0,
  RFIELD8(7, 0, divisor);
);

//Declare another 8-bit register named LCR. Its offset to UART_BASE is 0xc. It has 5 register fields.
GRAM8(
  LCR, UART_BASE, 0xc,
  RFIELD8(7, 7, dlab);
  RFIELD8(6, 6, break_en);
  RFIELD8(5, 3, parity_cfg);
  RFIELD8(2, 2, stop_bit);
  RFIELD8(1, 0, data_bit);
);

void ns16550_set_baud(int sys_clk_hz, int baud) {
  int div = sys_clk_hz / 16 / baud;

  RRMW(LCR, dlab, 1); //read out LCR, change its field, dlab, to 1, and then write back to LCR.

  RSET(DLL, div); //write the computed div to DLL.

  RRMW(LCR, dlab, 0); //read out LCR, change its field, dlab, to 0, and then write back to LCR.
}
```

## More Examples
### Declare Memory-based Register
This example is based on GD32VF103's `TIMERx_INTF`.

GD32VF103 has 4 sets of timers. Each set has an identical structure but a different base address. Instead of declaring them one-by-one, GRAM provides `GRAM_DUP(<base reg name>, <new reg name>, <bias to base>)` to duplicate a declared register to different address. Note that `GRAM_DUP()` is memory-based register only.
```C
GRAM16(
  TIMER1_INTF, 0x40000000, 0x10,
  RFIELD16(0, 0, upif);
  RFIELD16(1, 1, ch0if);
  RFIELD16(2, 2, ch1if);
  RFIELD16(3, 3, ch2if);
  RFIELD16(4, 4, ch3if);
  RF_RSV16(5, 5);
  RFIELD16(6, 6, trgif);
  RF_RSV16(8, 7);
  RFIELD16(9, 9, ch0of);
  RFIELD16(10, 10, ch1of);
  RFIELD16(11, 11, ch2of);
  RFIELD16(12, 12, ch3of);
  RF_RSV16(15, 12);
);
GRAM_DUP(TIMER1_INTF, TIMER2_INTF, 0x400);
GRAM_DUP(TIMER1_INTF, TIMER3_INTF, 0x800);
GRAM_DUP(TIMER1_INTF, TIMER4_INTF, 0xc00);
```
Reference: https://www.gd32mcu.com/data/documents/userManual/GD32VF103_User_Manual_Rev1.5.pdf

### Declare Special Register
This example is based on Aarch64's `SCTLR_EL3`.

Declaring special register is similar to memory-based register. Except that an extra `<reg name>_K` element is needed. This is used by the architecture-specific instructions to identify the register. Different architectures might need `<reg name>_K` in different forms. For example, `SCTLR_EL3_K` for `aarch64` is just `sctlr_el3`, `CP0_CAUSE_K` for `mips32` is `"$13,0"`, and `CSR_MSTATUS_K` for `rv32` is `(0x300)`.

Luckily, typical users need not such knowledge to operate registers thru GRAM. Only people declaring registers or porting GRAM to other architectures needs to worry about that.
```C
#define SCTLR_EL3_K sctlr_el3
GRAM64(
  SCTLR_EL3, -1, -1,
  RFIELD64(0, 0, m);
  RFIELD64(1, 1, a);
  RFIELD64(2, 2, c);
  RFIELD64(3, 3, sa);
  RF_RSV64(5, 4);
  RFIELD64(6, 6, naa);
  RF_RSV64(10, 7);
  RFIELD64(11, 11, eos);
  RFIELD64(12, 12, i);
  RFIELD64(13, 13, endb);
  RF_RSV64(18, 14);
  RFIELD64(19, 19, wxn);
  RF_RSV64(20, 20);
  RFIELD64(21, 21, iesb);
  RFIELD64(22, 22, eis);
  RF_RSV64(24, 23);
  RFIELD64(25, 25, ee);
  RF_RSV64(26, 26);
  RFIELD64(27, 27, enda);
  RF_RSV64(29, 28);
  RFIELD64(30, 30, enib);
  RFIELD64(31, 31, enia);
  RF_RSV64(35, 32);
  RFIELD64(36, 36, bt);
  RFIELD64(37, 37, itfsb);
  RF_RSV64(39, 38);
  RFIELD64(41, 40, tcf);
  RF_RSV64(42, 42);
  RFIELD64(43, 43, ata);
  RFIELD64(44, 44, dssbs);
  RF_RSV64(63, 45);
);
```
Reference: https://developer.arm.com/documentation/ddi0595/2021-06/AArch64-Registers/SCTLR-EL3--System-Control-Register--EL3-

## Operate Declared Register
```C
SCTLR_EL3_T sctlr_el3;

sctlr_el3.v = RGET(SCTLR_EL3);

sctlr_el3.f.c = 0;
RSET(SCTLR_EL3, sctlr_el3.v)

RRBS(TIMER2_INTF, ioremap(TIMER2_INTF_B, 0x400));
while (1) {
  if (RFLD(TIMER2_INTF, trgif)) {
    RRMW(
      TIMER2_INTF,
      trgif, 0,
      ch0if, 0,
      ch1if, 0,
      ch2if, 0,
      ch3if, 0
    );
    break;
  }
}

sctlr_el3.f.c = 1;
RSET(SCTLR_EL3, sctlr_el3.v)
```
* `<reg name>_T` is a data type for defining a variable. The variable can then be accessed as an integer with `.v`. Or it can be accessed for declared fields with `.f.<field name>`.
* `RGET(<reg name>)` returns the given register as an integer.
* `RSET(<reg name>, <integer>)` writes the integer to the given register.
* `<reg name>_B` is an integer for base address of the register.
* `RRBS(<reg name>, <new base>)` changes the base address of the given register in run-time. Generally, GRAM declares register base and offset addresses statically to get the actual address in compile-time. However, there are cases requiring dynamically address resolution. For example, ioremap() in Linux kernel driver. In these case, `RRBS()` can alter base address of a register.
* `RFLD(<reg name>, <field name>)` returns value of the given register field.
* `RRMW(<reg name>, <field name>, <value>[, <field name>, <value>]*)` does a read-modify-write operation. That is, it reads out value of the given register, modifies the given fields to the given values, and then writes back to the register. Note that multiple <field name> and <value> pairs can be given in a single `RRMW()`.

## Endianness and Field Ordering
In big-endian environment, `RFIELD<bit-width>` should be declared from MSB fields to LSB ones. In little-endian environment, they come in a reversed order. A possible solution in GCC is declaring both orders and guarding them by the compile flag `__BYTE_ORDER__`. For example,
```C
GRAM8(
  LCR, UART_BASE, 0xc,
#if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
  RFIELD8(7, 7, dlab);
  RFIELD8(6, 6, break_en);
  RFIELD8(5, 3, parity_cfg);
  RFIELD8(2, 2, stop_bit);
  RFIELD8(1, 0, data_bit);
#else
  RFIELD8(1, 0, data_bit);
  RFIELD8(2, 2, stop_bit);
  RFIELD8(5, 3, parity_cfg);
  RFIELD8(6, 6, break_en);
  RFIELD8(7, 7, dlab);
#endif
);
```
In any case, it is user's job to declare register fields in correct order. GRAM has no way to check endianness setting.

## Framework Summary
| Syntax | Description |
| - | - |
| GRAM64(), RFIELD64(), RF_RSV64() | Declare a 64-bit register |
| GRAM32(), RFIELD32(), RF_RSV32() | Declare a 32-bit register |
| GRAM16(), RFIELD16(), RF_RSV16() | Declare a 16-bit register |
| GRAM8(), RFIELD8(), RF_RSV8() | Declare a 8-bit register |
| GRAM_DUP() | Duplicate a declared memory-based register with an offset |
| \<reg\>_T | Implicitly created data type of the declared register |
| \<reg\>_B | Implicitly created integer of base address of the declared register |
| \<reg\>_O | Implicitly created integer of offset of the declared register |
| \<reg\>_A | Implicitly created integer of address of the declared register |
| RGET() | Return value of a register |
| RSET() | Write value to a register |
| RFLD() | Returns value of a register field |
| RRMW() | Read-modify-write register field and value pairs of a register |
| RRBS() | Alter base address of a memory-based register in run-time |
