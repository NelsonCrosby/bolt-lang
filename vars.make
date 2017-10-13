
TOPDIR := $(shell pwd)
TMAKE := $(TOPDIR)/tools/target.make
mkvars := \
    TOPDIR=$(TOPDIR) \
    TMAKE=$(TMAKE) \
    CC=$(CC) \
    LEMON=$(LEMON) \
    OUTDIR=$(TOPDIR)/build
