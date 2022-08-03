#include <stdint.h>
#include <gram.h>

#include <gram_mips32.h>

int main(void) {
	CP0_CAUSE_T cause;
	volatile int ip_cnt = 0;

	RRMW(
		CP0_CAUSE,
		dc, 1);

	cause.v = RGET(CP0_CAUSE);

	do {
		ip_cnt += (cause.f.ip7_2 & 1);
	} while (cause.f.ip7_2 = (cause.f.ip7_2 >> 1));

	cause.f.dc = 0;

	RSET(CP0_CAUSE, cause.v);

	return RFLD(CP0_CAUSE, exccode);
}
