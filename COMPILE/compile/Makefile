########################
### General settings ###
########################
#PREFIX?=/opt/risqv/bin/riscv32-unknown-elf-
PREFIX?=/opt/pulp/bin/riscv32-unknown-elf-
CC=$(PREFIX)gcc
AS=$(CC) -x assembler-with-cpp
OBJCOPY=$(PREFIX)objcopy
OBJSIZE=$(PREFIX)size
PULPINO_REPO=$(shell realpath "utils")
SRECTOSLM=python "$(PULPINO_REPO)/s19toslm.py"

ARCHFLAGS=-march=rv32imfcxpulpv3 -mabi=ilp32
# machine flags: -msmall-data-limit is RISCV-specific, but can't be passed to LD
CFLAGS+=$(ARCHFLAGS) -msmall-data-limit=8
# diagnostics flags
CFLAGS+=-fmessage-length=0
# C options
CFLAGS+=-std=gnu11 -fsigned-char
CFLAGS+=-I"../lib"
CFLAGS+=-I"../src/mupq/common"
# optimization options
CFLAGS+=-fdata-sections -ffunction-sections -O3
# debug options
CFLAGS+=-g0

LDFLAGS+=-T"link.riscv.ld" -nostartfiles -Wl,--gc-sections
LDFLAGS+=-Wl,-Map,"project.map"

########################
###   Library Files  ###
########################
LIBSRCS:=$(wildcard ../lib/*.c)
LIBSRCS_ASM=$(wildcard ../lib/*.S)


########################
###     Includes     ###
########################
INCDIR = -I../src/RISCV_optimized_code


########################
###     Prefixes     ###
########################
# 添加指令例子
# KYBER512PREFIX = ../src/PQClean/crypto_kem/kyber512/clean

#HELLOPREFIX = ../src/hello
HELLOPREFIX = ../src/gpio_test

########################
###      hello       ###
########################
HELLO_C = $(HELLOPREFIX)/gpio.c\

# ########################
# ###     NEWHOPE      ###
# ###    添加指令例子    ###
# ########################
# ### NEWHOPE512 ###
# NEWHOPE512SRCS_C = $(NEWHOPE512PREFIX)/cpapke.c \
#     $(NEWHOPE512PREFIX)/kem.c \
#     $(NEWHOPE512PREFIX)/ntt.c \
#     $(NEWHOPE512PREFIX)/poly.c \
#     $(NEWHOPE512PREFIX)/precomp.c \
#     $(NEWHOPE512PREFIX)/reduce.c \
#     $(NEWHOPE512PREFIX)/verify.c \
#     $(COMMONPREFIX_MUPQ)/fips202.c \
#     $(COMMONPREFIX_MUPQ)/keccakf1600.c \
#     $(RISCVOPTPREFIX)/notrandombytes.c \
#     ../src/bench_targets/newhope512cca/crypto_kem_bench.c


########################
###   Make Targets   ###
########################
.PHONY: all clean

all: gpio_test_bench

########################
###      HELLO       ###
########################
gpio_test_bench: INCDIR += -I../src/gpio_test
gpio_test_bench: gpio_test_bench.elf slm/gpio_test_bench.txt

gpio_test_bench.elf: $(LIBSRCS:.c=.o) $(LIBSRCS_ASM:.S=.o) $(HELLO_C:.c=.o)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	$(OBJSIZE) --format=berkeley $@

slm/gpio_test_bench.txt: gpio_test_bench.srec
	cd slm && $(SRECTOSLM) ../$^; cp spi_stim.txt ../../../TEST/slm_files; cp spi_stim.txt ../../../TEST/slm_files/hello

# ########################
# ###     NEWHOPE      ###
# ###    添加指令例子    ###
# ########################
# ######## NEWHOPE512 TARGET ########
# newhope512_bench: INCDIR += -I../src/PQClean/crypto_kem/newhope512cca/clean
# newhope512_bench: newhope512_bench.elf slm/newhope512_bench.txt

# newhope512_bench.elf: $(LIBSRCS:.c=.o) $(LIBSRCS_ASM:.S=.o) $(NEWHOPE512SRCS_C:.c=.o)
# 	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
# 	$(OBJSIZE) --format=berkeley $@

# slm/newhope512_bench.txt: newhope512_bench.srec
# 	cd slm && $(SRECTOSLM) ../$^; cp spi_stim.txt ../../../TEST/slm_files; cp spi_stim.txt ../../../TEST/slm_files/newhope512cca



########################
###    Resources     ###
########################

%.srec: %.elf
	$(OBJCOPY) -O srec --srec-len=1 $^ $@

%.siz: %.elf
	$(OBJSIZE) --format=berkeley $^ > $@

%.o: %.c
	$(CC) $(CFLAGS) -Wa,-adhlns="$(@:.o=.o.lst)" -MMD -MP -MF"$(@:.o=.d)" -MT $@ -o $@ -c $< $(INCDIR)

%_asm.o: %.S
	$(AS) $(CFLAGS) -Wa,-adhlns="$(@:.o=.o.lst)" -MMD -MP -MF"$(@:.o=.d)" -MT $@ -o $@ -c $<

%.S: %.c
	$(CC) $(CFLAGS) -o $@ -S $< $(INCDIR)

clean:
	rm -rf $(LIBSRCS:.c=.o) $(LIBSRCS_ASM:.S=.o) $(LIBSRCS:.c=.o.lst) $(LIBSRCS:.c=.d) $(LIBSRCS_ASM:.S=.d)
	rm -f $(HELLO_C:.c=.o) $(HELLO_C:.c=.o.lst) $(HELLO_C:.c=.d) $(HELLO_C:.c=.S)
	rm -f *.elf *.srec *.siz *.map
	rm -f slm/flash_stim.slm
	rm -f slm/l2_ram_cut0_hi.slm
	rm -f slm/l2_ram_cut0_lo.slm
	rm -f slm/l2_stim.slm
	rm -f slm/spi_stim.txt
	rm -f slm/tcdm_bank0.slm
