#ifndef __MIPS32_SREG_H__
#define __MIPS32_SREG_H__ 1

#ifdef arch_sreg_read
#	undef arch_sreg_read
#endif

#ifdef arch_sreg_write
#	undef arch_sreg_write
#endif

#define arch_sreg_read(_double_quoted_key) ({ \
			register reg32_t __v; \
			__asm__ __volatile__ ("mfc0 %0, " _double_quoted_key :"=r"(__v)); \
			__v; \
		})

#define arch_sreg_write(_double_quoted_key, val) do { \
		__asm__ __volatile__ ("mtc0 %0, " _double_quoted_key::"r"(val)); \
	} while(0)

#define CP0_CAUSE_K "$13,0"
GRAM32(
	CP0_CAUSE, -1, -1,
	RFIELD32(31, 31, bd);
	RFIELD32(30, 30, ti);
	RFIELD32(29, 28, ce);
	RFIELD32(27, 27, dc);
	RFIELD32(26, 26, pci);
	RF_RSV32(25, 24);
	RFIELD32(23, 23, iv);
	RFIELD32(22, 22, wp);
	RFIELD32(21, 21, fdci);
	RF_RSV32(20, 16);
	RFIELD32(15, 10, ip7_2);
	RFIELD32(9, 8, ip1_0);
	RF_RSV32(7, 7);
	RFIELD32(6, 2, exccode);
	RF_RSV32(1, 0);
	);

#endif
