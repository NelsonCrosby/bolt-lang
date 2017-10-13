
-include conf.make
include defaults.make vars.make

all: boltc
clean: clean-boltc
.PHONY: all clean

boltc: build/boltc/boltc
build/boltc/boltc:
	@echo 'make -C src/boltc'
	@$(MAKE) -C src/boltc $(mkvars)/boltc
clean-boltc:
	@echo 'make -C src/boltc clean'
	@$(MAKE) -C src/boltc $(mkvars)/boltc clean
.PHONY: boltc clean-boltc
