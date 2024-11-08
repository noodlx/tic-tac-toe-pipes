S_BINARY=server/bin
C_BINARY=client/bin

S_CODEDIRS=server/src
C_CODEDIRS=client/src

CC=gcc

DEPFLAGS=-MP -MD

CFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS) -Isrc

S_CFILES=$(foreach D,$(S_CODEDIRS),$(wildcard $(D)/*.c))
S_OBJECTS=$(patsubst %.c,%.o,$(S_CFILES))
S_DEPFILES=$(patsubst %.c,%.d,$(S_CFILES))

C_CFILES=$(foreach D,$(C_CODEDIRS),$(wildcard $(D)/*.c))
C_OBJECTS=$(patsubst %.c,%.o,$(C_CFILES))
C_DEPFILES=$(patsubst %.c,%.d,$(C_CFILES))

all: server client

server: $(S_BINARY)

client: $(C_BINARY)

$(S_BINARY): $(S_OBJECTS)
	$(CC) -o $@ $^

	
$(C_BINARY): $(C_OBJECTS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(S_BINARY) $(C_BINARY) $(S_OBJECTS) $(C_OBJECTS) $(S_DEPFILES) $(C_DEPFILES)

distribute: clean
	tar zcvf dist.tgz *

diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat


-include $(S_DEPFILES)
-include $(C_DEPFILES)

.PHONY: all clean distribute diff