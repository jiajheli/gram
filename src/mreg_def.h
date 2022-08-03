#ifndef __MREG_DEF_H__
#define __MREG_DEF_H__

#include <stdint.h>

#if (GRAM_MACRO_DEF == 1)
GRAM64(
	REG64_DEMO, 0x10000000, 0x6400,
	RFIELD64(63, 32, f63_32);
	RFIELD64(31, 16, f31_16);
	RFIELD64(15, 8, f15_8);
	RFIELD64(7, 4, f7_4);
	RFIELD64(3, 2, f3_2);
	RFIELD64(1, 1, f1_1);
	RFIELD64(0, 0, f0_0);
	);

GRAM32(
	REG32_DEMO, 0x10000000, 0x3200,
	RFIELD32(31, 16, f31_16);
	RFIELD32(15, 8, f15_8);
	RFIELD32(7, 4, f7_4);
	RFIELD32(3, 2, f3_2);
	RFIELD32(1, 1, f1_1);
	RFIELD32(0, 0, f0_0);
	);

GRAM16(
	REG16_DEMO, 0x10000000, 0x1600,
	RFIELD16(15, 8, f15_8);
	RFIELD16(7, 4, f7_4);
	RFIELD16(3, 2, f3_2);
	RFIELD16(1, 1, f1_1);
	RFIELD16(0, 0, f0_0);
	);

GRAM8(
	REG8_DEMO, 0x10000000, 0x0800,
	RFIELD16(7, 4, f7_4);
	RFIELD16(3, 2, f3_2);
	RFIELD16(1, 1, f1_1);
	RFIELD16(0, 0, f0_0);
	);
#else
typedef union {
	struct {
		reg64_t f63_32:32;
		reg64_t f31_16:16;
		reg64_t f15_8:8;
		reg64_t f7_4:4;
		reg64_t f3_2:2;
		reg64_t f1_1:1;
		reg64_t f0_0:1;
	} f;
	reg64_t v;
} REG64_DEMO_T;
static const addr_t REG64_DEMO_A = (addr_t)(0x10000000 + 0x6400);
static const offset_t REG64_DEMO_O = (0x6400);

typedef union {
	struct {
		reg32_t f31_16:16;
		reg32_t f15_8:8;
		reg32_t f7_4:4;
		reg32_t f3_2:2;
		reg32_t f1_1:1;
		reg32_t f0_0:1;
	} f;
	reg32_t v;
} REG32_DEMO_T;
static const addr_t REG32_DEMO_A = (addr_t)(0x10000000 + 0x3200);
static const offset_t REG32_DEMO_O = (0x3200);

typedef union {
	struct {
		reg16_t f15_8:8;
		reg16_t f7_4:4;
		reg16_t f3_2:2;
		reg16_t f1_1:1;
		reg16_t f0_0:1;
	} f;
	reg16_t v;
} REG16_DEMO_T;
static const addr_t REG16_DEMO_A = (addr_t)(0x10000000 + 0x1600);
static const offset_t REG16_DEMO_O = (0x1600);

typedef union {
	struct {
		reg8_t f7_4:4;
		reg8_t f3_2:2;
		reg8_t f1_1:1;
		reg8_t f0_0:1;
	} f;
	reg8_t v;
} REG8_DEMO_T;
static const addr_t REG8_DEMO_A = (addr_t)(0x10000000 + 0x0800);
static const offset_t REG8_DEMO_O = (0x0800);

#endif

#endif
