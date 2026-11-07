.PHONY: linux clean distclean

TARGET = kv-storage
	
INCLUDES = \
	-Iembedded-cli/lib/include/

SOURCES = \
	main.c \
	core/stack.c \
	embedded-cli/lib/src/embedded_cli.c
	
linux:
	bear -- cc -std=c23 -O2 -Wall -Wextra -Wpedantic -Werror -c $(SOURCES) $(INCLUDES)
	cc $(notdir $(SOURCES:.c=.o)) -o $(TARGET)

clean:
	rm -f kv-storage *.o

distclean: clean
	rm -f compile_commands.json
	rm -rf .cache
