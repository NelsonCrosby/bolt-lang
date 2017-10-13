
out = $(shell realpath --relative-to=. "$(OUTDIR)")

FILE_O = $(FILES:%.c=$(out)/%.o)
FILE_D = $(FILE_O:.o=.d)

all: _dirs $(out)/$(TARGET)
.PHONY: all _dirs clean

clean:
	@rm -fv $(FILE_O) $(FILE_D) $(out)/$(TARGET)

_dirs:
	@mkdir -pv $(out) $(DIRS:%=$(out)/%)

$(out)/$(TARGET): $(FILE_O)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(out)/%.o: %.c
	$(CC) -c $(CFLAGS) -MMD -o $@ $<

-include $(FILE_D)
