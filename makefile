BINARY=bin
CODEDIRS=. src
INCDIRS= 

CC=gcc
OPT=-O0

DEPFLAGS=-MP -MD

CFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS) -Isrc

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

    %.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

distribute: clean
	tar zcvf dist.tgz *

diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat


-include $(DEPFILES)

.PHONY: all clean distribute diff