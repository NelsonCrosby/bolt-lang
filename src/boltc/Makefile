
TARGET = boltc
DIRS =
FILES = main.c parser.c

LDDEPS += $(OUTDIR)/mpc.o
CLEAN += $(LDDEPS)

include $(TMAKE)

$(OUTDIR)/mpc.o: $(VENDOR)/mpc/mpc.c
	$(_cc)
