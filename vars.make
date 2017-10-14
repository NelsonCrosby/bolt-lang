
TOPDIR := $(shell pwd)
TMAKE := $(TOPDIR)/tools/target.make
mkvars := \
    TOPDIR=$(TOPDIR) \
    TMAKE=$(TMAKE) \
    CFLAGS=$(CFLAGS) \
    CC=$(CC) \
    LEMON=$(LEMON) \
    ZLEXGEN=$(ZLEXGEN) \
    OUTDIR=$(TOPDIR)/build
