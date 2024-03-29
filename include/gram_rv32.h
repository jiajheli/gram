#ifndef __RV32_SREG_H__
#define __RV32_SREG_H__ 1

#ifdef arch_sreg_read
#	undef arch_sreg_read
#endif

#ifdef arch_sreg_write
#	undef arch_sreg_write
#endif

#define __ASM_STR(_str) #_str

#define arch_sreg_read(_csr) ({ \
			register reg32_t __v; \
			__asm__ __volatile__ ("csrr %0, " __ASM_STR(_csr) :"=r"(__v)::"memory"); \
			__v; \
		})

#define arch_sreg_write(_csr, val) do { \
		__asm__ __volatile__ ("csrw " __ASM_STR(_csr) ", %0" ::"rK"(val):"memory"); \
	} while(0)

#define CSR_FFLAGS_K (0x1)
#define CSR_FRM_K (0x2)
#define CSR_FCSR_K (0x3)
#define CSR_SSTATUS_K (0x100)
#define CSR_SIE_K (0x104)
#define CSR_STVEC_K (0x105)
#define CSR_SCOUNTEREN_K (0x106)
#define CSR_SENVCFG_K (0x10a)
#define CSR_SSCRATCH_K (0x140)
#define CSR_SEPC_K (0x141)
#define CSR_SCAUSE_K (0x142)
#define CSR_STVAL_K (0x143)
#define CSR_SIP_K (0x144)
#define CSR_SATP_K (0x180)
#define CSR_VSSTATUS_K (0x200)
#define CSR_VSIE_K (0x204)
#define CSR_VSTVEC_K (0x205)
#define CSR_VSSCRATCH_K (0x240)
#define CSR_VSEPC_K (0x241)
#define CSR_VSCAUSE_K (0x242)
#define CSR_VSTVAL_K (0x243)
#define CSR_VSIP_K (0x244)
#define CSR_VSATP_K (0x280)

#define CSR_MSTATUS_K (0x300)
GRAM32(
	CSR_MSTATUS, -1, -1,
	RF_RSV32(0, 0);
	RFIELD32(1, 1, sie);
	RF_RSV32(2, 2);
	RFIELD32(3, 3, mie);
	RF_RSV32(4, 4);
	RFIELD32(5, 5, spie);
	RFIELD32(6, 6, ube);
	RFIELD32(7, 7, mpie);
	RFIELD32(8, 8, spp);
	RFIELD32(10, 9, vs);
	RFIELD32(12, 11, mpp);
	RFIELD32(14, 13, fs);
	RFIELD32(16, 15, xs);
	RFIELD32(17, 17, mprv);
	RFIELD32(18, 18, sum);
	RFIELD32(19, 19, mxr);
	RFIELD32(20, 20, tvm);
	RFIELD32(21, 21, tw);
	RFIELD32(22, 22, tsr);
	RF_RSV32(30, 23);
	RFIELD32(31, 31, sd);
	);

#define CSR_MISA_K (0x301)
#define CSR_MEDELEG_K (0x302)
#define CSR_MIDELEG_K (0x303)
#define CSR_MIE_K (0x304)
GRAM32(
	CSR_MIE, -1, -1,
	RF_RSV32(0, 0);
	RFIELD32(1, 1, ssie);
	RF_RSV32(2, 2);
	RFIELD32(3, 3, msie);
	RF_RSV32(4, 4);
	RFIELD32(5, 5, stie);
	RF_RSV32(6, 6);
	RFIELD32(7, 7, mtie);
	RF_RSV32(8, 8);
	RFIELD32(9, 9, seie);
	RF_RSV32(10, 10);
	RFIELD32(11, 11, meie);
	RF_RSV32(31, 12);
	);
#define CSR_MTVEC_K (0x305)
GRAM32(
	CSR_MTVEC, -1, -1,
	RFIELD32(1, 0, mode);
	RFIELD32(31, 2, base);
	);
#define CSR_MCOUNTEREN_K (0x306)
#define CSR_MENVCFG_K (0x30a)
#define CSR_MSTATUSH_K (0x310)
#define CSR_MENVCFGH_K (0x31a)
#define CSR_MCOUNTINHIBIT_K (0x320)
#define CSR_MHPMEVENT3_K (0x323)
#define CSR_MHPMEVENT4_K (0x324)
#define CSR_MHPMEVENT5_K (0x325)
#define CSR_MHPMEVENT6_K (0x326)
#define CSR_MHPMEVENT7_K (0x327)
#define CSR_MHPMEVENT8_K (0x328)
#define CSR_MHPMEVENT9_K (0x329)
#define CSR_MHPMEVENT10_K (0x32a)
#define CSR_MHPMEVENT11_K (0x32b)
#define CSR_MHPMEVENT12_K (0x32c)
#define CSR_MHPMEVENT13_K (0x32d)
#define CSR_MHPMEVENT14_K (0x32e)
#define CSR_MHPMEVENT15_K (0x32f)
#define CSR_MHPMEVENT16_K (0x330)
#define CSR_MHPMEVENT17_K (0x331)
#define CSR_MHPMEVENT18_K (0x332)
#define CSR_MHPMEVENT19_K (0x333)
#define CSR_MHPMEVENT20_K (0x334)
#define CSR_MHPMEVENT21_K (0x335)
#define CSR_MHPMEVENT22_K (0x336)
#define CSR_MHPMEVENT23_K (0x337)
#define CSR_MHPMEVENT24_K (0x338)
#define CSR_MHPMEVENT25_K (0x339)
#define CSR_MHPMEVENT26_K (0x33a)
#define CSR_MHPMEVENT27_K (0x33b)
#define CSR_MHPMEVENT28_K (0x33c)
#define CSR_MHPMEVENT29_K (0x33d)
#define CSR_MHPMEVENT30_K (0x33e)
#define CSR_MHPMEVENT31_K (0x33f)
#define CSR_MSCRATCH_K (0x340)
#define CSR_MEPC_K (0x341)
GRAM32(
	CSR_MEPC, -1, -1,
	RFIELD32(31, 0, mepc);
	);
#define CSR_MCAUSE_K (0x342)
GRAM32(
	CSR_MCAUSE, -1, -1,
	RFIELD32(30, 0, exce_code);
	RFIELD32(31, 31, interrupt);
	);
#define CSR_MTVAL_K (0x343)
#define CSR_MIP_K (0x344)
GRAM32(
	CSR_MIP, -1, -1,
	RF_RSV32(0, 0);
	RFIELD32(1, 1, ssip);
	RF_RSV32(2, 2);
	RFIELD32(3, 3, msip);
	RF_RSV32(4, 4);
	RFIELD32(5, 5, stip);
	RF_RSV32(6, 6);
	RFIELD32(7, 7, mtip);
	RF_RSV32(8, 8);
	RFIELD32(9, 9, seip);
	RF_RSV32(10, 10);
	RFIELD32(11, 11, meip);
	RF_RSV32(31, 12);
	);
#define CSR_MTINST_K (0x34a)
#define CSR_MTVAL2_K (0x34b)
#define CSR_PMPCFG0_K (0x3a0)
#define CSR_PMPCFG1_K (0x3a1)
#define CSR_PMPCFG2_K (0x3a2)
#define CSR_PMPCFG3_K (0x3a3)
#define CSR_PMPCFG4_K (0x3a4)
#define CSR_PMPCFG5_K (0x3a5)
#define CSR_PMPCFG6_K (0x3a6)
#define CSR_PMPCFG7_K (0x3a7)
#define CSR_PMPCFG8_K (0x3a8)
#define CSR_PMPCFG9_K (0x3a9)
#define CSR_PMPCFG10_K (0x3aa)
#define CSR_PMPCFG11_K (0x3ab)
#define CSR_PMPCFG12_K (0x3ac)
#define CSR_PMPCFG13_K (0x3ad)
#define CSR_PMPCFG14_K (0x3ae)
#define CSR_PMPCFG15_K (0x3af)
#define CSR_PMPADDR0_K (0x3b0)
#define CSR_PMPADDR1_K (0x3b1)
#define CSR_PMPADDR2_K (0x3b2)
#define CSR_PMPADDR3_K (0x3b3)
#define CSR_PMPADDR4_K (0x3b4)
#define CSR_PMPADDR5_K (0x3b5)
#define CSR_PMPADDR6_K (0x3b6)
#define CSR_PMPADDR7_K (0x3b7)
#define CSR_PMPADDR8_K (0x3b8)
#define CSR_PMPADDR9_K (0x3b9)
#define CSR_PMPADDR10_K (0x3ba)
#define CSR_PMPADDR11_K (0x3bb)
#define CSR_PMPADDR12_K (0x3bc)
#define CSR_PMPADDR13_K (0x3bd)
#define CSR_PMPADDR14_K (0x3be)
#define CSR_PMPADDR15_K (0x3bf)
#define CSR_PMPADDR16_K (0x3c0)
#define CSR_PMPADDR17_K (0x3c1)
#define CSR_PMPADDR18_K (0x3c2)
#define CSR_PMPADDR19_K (0x3c3)
#define CSR_PMPADDR20_K (0x3c4)
#define CSR_PMPADDR21_K (0x3c5)
#define CSR_PMPADDR22_K (0x3c6)
#define CSR_PMPADDR23_K (0x3c7)
#define CSR_PMPADDR24_K (0x3c8)
#define CSR_PMPADDR25_K (0x3c9)
#define CSR_PMPADDR26_K (0x3ca)
#define CSR_PMPADDR27_K (0x3cb)
#define CSR_PMPADDR28_K (0x3cc)
#define CSR_PMPADDR29_K (0x3cd)
#define CSR_PMPADDR30_K (0x3ce)
#define CSR_PMPADDR31_K (0x3cf)
#define CSR_PMPADDR32_K (0x3d0)
#define CSR_PMPADDR33_K (0x3d1)
#define CSR_PMPADDR34_K (0x3d2)
#define CSR_PMPADDR35_K (0x3d3)
#define CSR_PMPADDR36_K (0x3d4)
#define CSR_PMPADDR37_K (0x3d5)
#define CSR_PMPADDR38_K (0x3d6)
#define CSR_PMPADDR39_K (0x3d7)
#define CSR_PMPADDR40_K (0x3d8)
#define CSR_PMPADDR41_K (0x3d9)
#define CSR_PMPADDR42_K (0x3da)
#define CSR_PMPADDR43_K (0x3db)
#define CSR_PMPADDR44_K (0x3dc)
#define CSR_PMPADDR45_K (0x3dd)
#define CSR_PMPADDR46_K (0x3de)
#define CSR_PMPADDR47_K (0x3df)
#define CSR_PMPADDR48_K (0x3e0)
#define CSR_PMPADDR49_K (0x3e1)
#define CSR_PMPADDR50_K (0x3e2)
#define CSR_PMPADDR51_K (0x3e3)
#define CSR_PMPADDR52_K (0x3e4)
#define CSR_PMPADDR53_K (0x3e5)
#define CSR_PMPADDR54_K (0x3e6)
#define CSR_PMPADDR55_K (0x3e7)
#define CSR_PMPADDR56_K (0x3e8)
#define CSR_PMPADDR57_K (0x3e9)
#define CSR_PMPADDR58_K (0x3ea)
#define CSR_PMPADDR59_K (0x3eb)
#define CSR_PMPADDR60_K (0x3ec)
#define CSR_PMPADDR61_K (0x3ed)
#define CSR_PMPADDR62_K (0x3ee)
#define CSR_PMPADDR63_K (0x3ef)
#define CSR_SCONTEXT_K (0x5a8)
#define CSR_HSTATUS_K (0x600)
#define CSR_HEDELEG_K (0x602)
#define CSR_HIDELEG_K (0x603)
#define CSR_HIE_K (0x604)
#define CSR_HTIMEDELTA_K (0x605)
#define CSR_HCOUNTEREN_K (0x606)
#define CSR_HGEIE_K (0x607)
#define CSR_HENVCFG_K (0x60a)
#define CSR_HTIMEDELTAH_K (0x615)
#define CSR_HENVCFGH_K (0x61a)
#define CSR_HTVAL_K (0x643)
#define CSR_HIP_K (0x644)
#define CSR_HVIP_K (0x645)
#define CSR_HTINST_K (0x64a)
#define CSR_HGATP_K (0x680)
#define CSR_HCONTEXT_K (0x6a8)
#define CSR_MSECCFG_K (0x747)
#define CSR_MSECCFGH_K (0x757)
#define CSR_TSELECT_K (0x7a0)
#define CSR_TDATA1_K (0x7a1)
#define CSR_TDATA2_K (0x7a2)
#define CSR_TDATA3_K (0x7a3)
#define CSR_MCONTEXT_K (0x7a8)
#define CSR_DCSR_K (0x7b0)
#define CSR_DPC_K (0x7b1)
#define CSR_DSCRATCH0_K (0x7b2)
#define CSR_DSCRATCH1_K (0x7b3)
#define CSR_MCYCLE_K (0xb00)
#define CSR_MINSTRET_K (0xb02)
#define CSR_MHPMCOUNTER3_K (0xb03)
#define CSR_MHPMCOUNTER4_K (0xb04)
#define CSR_MHPMCOUNTER5_K (0xb05)
#define CSR_MHPMCOUNTER6_K (0xb06)
#define CSR_MHPMCOUNTER7_K (0xb07)
#define CSR_MHPMCOUNTER8_K (0xb08)
#define CSR_MHPMCOUNTER9_K (0xb09)
#define CSR_MHPMCOUNTER10_K (0xb0a)
#define CSR_MHPMCOUNTER11_K (0xb0b)
#define CSR_MHPMCOUNTER12_K (0xb0c)
#define CSR_MHPMCOUNTER13_K (0xb0d)
#define CSR_MHPMCOUNTER14_K (0xb0e)
#define CSR_MHPMCOUNTER15_K (0xb0f)
#define CSR_MHPMCOUNTER16_K (0xb10)
#define CSR_MHPMCOUNTER17_K (0xb11)
#define CSR_MHPMCOUNTER18_K (0xb12)
#define CSR_MHPMCOUNTER19_K (0xb13)
#define CSR_MHPMCOUNTER20_K (0xb14)
#define CSR_MHPMCOUNTER21_K (0xb15)
#define CSR_MHPMCOUNTER22_K (0xb16)
#define CSR_MHPMCOUNTER23_K (0xb17)
#define CSR_MHPMCOUNTER24_K (0xb18)
#define CSR_MHPMCOUNTER25_K (0xb19)
#define CSR_MHPMCOUNTER26_K (0xb1a)
#define CSR_MHPMCOUNTER27_K (0xb1b)
#define CSR_MHPMCOUNTER28_K (0xb1c)
#define CSR_MHPMCOUNTER29_K (0xb1d)
#define CSR_MHPMCOUNTER30_K (0xb1e)
#define CSR_MHPMCOUNTER31_K (0xb1f)
#define CSR_MCYCLEH_K (0xb80)
#define CSR_MINSTRETH_K (0xb82)
#define CSR_MHPMCOUNTER3H_K (0xb83)
#define CSR_MHPMCOUNTER4H_K (0xb84)
#define CSR_MHPMCOUNTER5H_K (0xb85)
#define CSR_MHPMCOUNTER6H_K (0xb86)
#define CSR_MHPMCOUNTER7H_K (0xb87)
#define CSR_MHPMCOUNTER8H_K (0xb88)
#define CSR_MHPMCOUNTER9H_K (0xb89)
#define CSR_MHPMCOUNTER10H_K (0xb8a)
#define CSR_MHPMCOUNTER11H_K (0xb8b)
#define CSR_MHPMCOUNTER12H_K (0xb8c)
#define CSR_MHPMCOUNTER13H_K (0xb8d)
#define CSR_MHPMCOUNTER14H_K (0xb8e)
#define CSR_MHPMCOUNTER15H_K (0xb8f)
#define CSR_MHPMCOUNTER16H_K (0xb90)
#define CSR_MHPMCOUNTER17H_K (0xb91)
#define CSR_MHPMCOUNTER18H_K (0xb92)
#define CSR_MHPMCOUNTER19H_K (0xb93)
#define CSR_MHPMCOUNTER20H_K (0xb94)
#define CSR_MHPMCOUNTER21H_K (0xb95)
#define CSR_MHPMCOUNTER22H_K (0xb96)
#define CSR_MHPMCOUNTER23H_K (0xb97)
#define CSR_MHPMCOUNTER24H_K (0xb98)
#define CSR_MHPMCOUNTER25H_K (0xb99)
#define CSR_MHPMCOUNTER26H_K (0xb9a)
#define CSR_MHPMCOUNTER27H_K (0xb9b)
#define CSR_MHPMCOUNTER28H_K (0xb9c)
#define CSR_MHPMCOUNTER29H_K (0xb9d)
#define CSR_MHPMCOUNTER30H_K (0xb9e)
#define CSR_MHPMCOUNTER31H_K (0xb9f)
#define CSR_CYCLE_K (0xc00)
#define CSR_TIME_K (0xc01)
#define CSR_INSTRET_K (0xc02)
#define CSR_HPMCOUNTER3_K (0xc03)
#define CSR_HPMCOUNTER4_K (0xc04)
#define CSR_HPMCOUNTER5_K (0xc05)
#define CSR_HPMCOUNTER6_K (0xc06)
#define CSR_HPMCOUNTER7_K (0xc07)
#define CSR_HPMCOUNTER8_K (0xc08)
#define CSR_HPMCOUNTER9_K (0xc09)
#define CSR_HPMCOUNTER10_K (0xc0a)
#define CSR_HPMCOUNTER11_K (0xc0b)
#define CSR_HPMCOUNTER12_K (0xc0c)
#define CSR_HPMCOUNTER13_K (0xc0d)
#define CSR_HPMCOUNTER14_K (0xc0e)
#define CSR_HPMCOUNTER15_K (0xc0f)
#define CSR_HPMCOUNTER16_K (0xc10)
#define CSR_HPMCOUNTER17_K (0xc11)
#define CSR_HPMCOUNTER18_K (0xc12)
#define CSR_HPMCOUNTER19_K (0xc13)
#define CSR_HPMCOUNTER20_K (0xc14)
#define CSR_HPMCOUNTER21_K (0xc15)
#define CSR_HPMCOUNTER22_K (0xc16)
#define CSR_HPMCOUNTER23_K (0xc17)
#define CSR_HPMCOUNTER24_K (0xc18)
#define CSR_HPMCOUNTER25_K (0xc19)
#define CSR_HPMCOUNTER26_K (0xc1a)
#define CSR_HPMCOUNTER27_K (0xc1b)
#define CSR_HPMCOUNTER28_K (0xc1c)
#define CSR_HPMCOUNTER29_K (0xc1d)
#define CSR_HPMCOUNTER30_K (0xc1e)
#define CSR_HPMCOUNTER31_K (0xc1f)
#define CSR_CYCLEH_K (0xc80)
#define CSR_TIMEH_K (0xc81)
#define CSR_INSTRETH_K (0xc82)
#define CSR_HPMCOUNTER3H_K (0xc83)
#define CSR_HPMCOUNTER4H_K (0xc84)
#define CSR_HPMCOUNTER5H_K (0xc85)
#define CSR_HPMCOUNTER6H_K (0xc86)
#define CSR_HPMCOUNTER7H_K (0xc87)
#define CSR_HPMCOUNTER8H_K (0xc88)
#define CSR_HPMCOUNTER9H_K (0xc89)
#define CSR_HPMCOUNTER10H_K (0xc8a)
#define CSR_HPMCOUNTER11H_K (0xc8b)
#define CSR_HPMCOUNTER12H_K (0xc8c)
#define CSR_HPMCOUNTER13H_K (0xc8d)
#define CSR_HPMCOUNTER14H_K (0xc8e)
#define CSR_HPMCOUNTER15H_K (0xc8f)
#define CSR_HPMCOUNTER16H_K (0xc90)
#define CSR_HPMCOUNTER17H_K (0xc91)
#define CSR_HPMCOUNTER18H_K (0xc92)
#define CSR_HPMCOUNTER19H_K (0xc93)
#define CSR_HPMCOUNTER20H_K (0xc94)
#define CSR_HPMCOUNTER21H_K (0xc95)
#define CSR_HPMCOUNTER22H_K (0xc96)
#define CSR_HPMCOUNTER23H_K (0xc97)
#define CSR_HPMCOUNTER24H_K (0xc98)
#define CSR_HPMCOUNTER25H_K (0xc99)
#define CSR_HPMCOUNTER26H_K (0xc9a)
#define CSR_HPMCOUNTER27H_K (0xc9b)
#define CSR_HPMCOUNTER28H_K (0xc9c)
#define CSR_HPMCOUNTER29H_K (0xc9d)
#define CSR_HPMCOUNTER30H_K (0xc9e)
#define CSR_HPMCOUNTER31H_K (0xc9f)
#define CSR_HGEIP_K (0xe12)
#define CSR_MVENDORID_K (0xf11)
#define CSR_MARCHID_K (0xf12)
#define CSR_MIMPID_K (0xf13)
#define CSR_MHARTID_K (0xf14)
#define CSR_MCONFIGPTR_K (0xf15)

#endif
