
-include conf.make
include defaults.make vars.make

all: boltc
clean: clean-boltc
.PHONY: all clean

boltc:
	@echo 'make -C src/boltc'
	@$(MAKE) -C src/boltc $(mkvars)
clean-boltc:
	@echo 'make -C src/boltc clean'
	@$(MAKE) -C src/boltc $(mkvars) clean
.PHONY: boltc clean-boltc
