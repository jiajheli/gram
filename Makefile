$(info CROSS_COMPILE from CLI: $(CROSS_COMPILE))
CC := $(CROSS_COMPILE)gcc
OD := $(CROSS_COMPILE)objdump

$(info CFLAGS from CLI: $(CFLAGS))

ifeq ("$(MACRO_DEF)","0")
DEC_TYPE := raw
else
MACRO_DEF := 1
DEC_TYPE := macro
endif

MNAME := mmio_reg.$(DEC_TYPE)

# get reg. type from GCC's built-in define
ifneq ($(shell echo | $(CC) -dM -E - | grep __riscv),)
ARCH_TYPE := rv32
else ifneq ($(shell echo | $(CC) -dM -E - | grep __aarch64__),)
ARCH_TYPE := aarch64
else ifneq ($(shell echo | $(CC) -dM -E - | grep __mips__),)
ARCH_TYPE := mips32
else
ARCH_TYPE :=
endif

FINAL_CFLAGS := -Iinclude -Iinclude/arch -DGRAM_MACRO_DEF=$(MACRO_DEF) $(CFLAGS)
$(info FINAL_CFLAGS: $(FINAL_CFLAGS))

ifneq ("$(ARCH_TYPE)","")
ONAME := $(ARCH_TYPE).$(DEC_TYPE)
all: $(ONAME).dump
endif

all: $(MNAME).dump

$(MNAME).out: src/mmio_reg.c
	$(CC) $(FINAL_CFLAGS) $^ -o $@

rv32.raw.out rv32.macro.out: src/rv32_sreg.c
	$(CC) $(FINAL_CFLAGS) $^ -o $@

mips32.raw.out mips32.macro.out: src/mips32_sreg.c
	$(CC) $(FINAL_CFLAGS) $^ -o $@

aarch64.raw.out aarch64.macro.out: src/aarch64_sreg.c
	$(CC) $(FINAL_CFLAGS) $^ -o $@

src/mmio_reg.c: include/gram.h src/mreg_def.h

src/rv32_sreg.c: include/gram.h include/gram_rv32.h

src/mips32_sreg.c: include/gram.h include/gram_mips32.h

src/aarch64_sreg.c: include/gram.h include/gram_aa64.h

%.dump: %.out
	$(OD) -Dlxt $^ > $@

clean:
	rm -f *.out *.dump
