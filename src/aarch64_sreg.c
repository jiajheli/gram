#include <stdint.h>
#include <gram.h>

#include <gram_aa64.h>

int main(void) {
	SCTLR_EL3_T sctlr;
	volatile int ip_cnt = 0;

	RRMW(
		SCTLR_EL3,
		c, 1,
		a, 1,
		m, 1);

	sctlr.v = RGET(SCTLR_EL3);
	sctlr.f.i = 0;

	RSET(SCTLR_EL3, sctlr.v);

	return RFLD(SCTLR_EL3, m);
}
