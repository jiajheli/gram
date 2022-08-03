#include <stdint.h>
#include <gram.h>

#include "mreg_def.h"

int main(void) {
	REG64_DEMO_T r64;
	REG32_DEMO_T r32;
	REG16_DEMO_T r16;
	REG8_DEMO_T r8;

	RRMW(
		REG64_DEMO,
		f63_32, 0x64,
		f0_0, 1);
	RRMW(
		REG32_DEMO,
		f31_16, 0x32,
		f0_0, 1);
	RRMW(
		REG16_DEMO,
		f15_8, 0x16,
		f0_0, 1);
	RRMW(
		REG8_DEMO,
		f7_4, 0x8,
		f0_0, 1);

	while (RFLD(REG64_DEMO, f1_1) != 1) {
		;
	}
	while (RFLD(REG32_DEMO, f1_1) != 1) {
		;
	}
	while (RFLD(REG16_DEMO, f1_1) != 1) {
		;
	}
	while (RFLD(REG8_DEMO, f1_1) != 1) {
		;
	}

	r64.v = RGET(REG64_DEMO);
	r32.v = RGET(REG32_DEMO);
	r16.v = RGET(REG16_DEMO);
	r8.v = RGET(REG8_DEMO);

	RSET(REG64_DEMO, r64.v);
	RSET(REG32_DEMO, r32.v);
	RSET(REG16_DEMO, r16.v);
	RSET(REG8_DEMO, r8.v);

	return 0;
}
