
TOPDIR := $(shell pwd)
TMAKE := $(TOPDIR)/tools/target.make
mkvars := \
    TOPDIR=$(TOPDIR) \
    TMAKE=$(TMAKE) \
    CFLAGS=$(CFLAGS) \
    CC=$(CC) \
    LEMON=$(LEMON) \
    OUTDIR=$(TOPDIR)/build
