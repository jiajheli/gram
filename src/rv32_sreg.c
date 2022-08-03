#include <stdint.h>
#include <gram.h>

#include <gram_rv32.h>

int main(void) {
	CSR_MSTATUS_T mstatus;

	RRMW(
		CSR_MSTATUS,
		mie, 1);

	mstatus.v = RGET(CSR_MSTATUS);
	RSET(CSR_MSTATUS, mstatus.v);

	return RFLD(CSR_MSTATUS, mpp);
}
