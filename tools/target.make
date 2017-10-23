
VENDOR = $(TOPDIR)/vendor

FILE_O = $(FILES:%.c=$(OUTDIR)/%.o)
FILE_D = $(FILE_O:.o=.d) $(LDDEPS:.o=.d)

all: _dirs $(OUTDIR)/$(TARGET)
.PHONY: all _dirs clean

clean:
	@rm -fv $(FILE_O) $(FILE_D) $(OUTDIR)/$(TARGET) $(CLEAN)
	@rmdir -v $(OUTDIR)

_dirs:
	@mkdir -pv $(OUTDIR) $(DIRS:%=$(OUTDIR)/%)

$(OUTDIR)/$(TARGET): $(FILE_O) $(LDDEPS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

_cc = $(CC) -c $(CFLAGS) -MMD -o $@ $<

$(OUTDIR)/%.o: %.c
	$(_cc)

-include $(FILE_D)
 