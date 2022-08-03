#ifndef __AA64_SREG_H__
#define __AA64_SREG_H__ 1

#ifdef arch_sreg_read
#	undef arch_sreg_read
#endif

#ifdef arch_sreg_write
#	undef arch_sreg_write
#endif

#define __ASM_STR(_str) #_str

#define arch_sreg_read(_name) ({ \
			register reg64_t __v; \
			__asm__ __volatile__ ("mrs %0, " __ASM_STR(_name) :"=r"(__v)::); \
			__v; \
		})

#define arch_sreg_write(_name, val) do { \
		__asm__ __volatile__ ("msr " __ASM_STR(_name) ", %0" ::"r"(val)); \
	} while(0)

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

#endif
