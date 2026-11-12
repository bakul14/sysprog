.PHONY: linux clean distclean

TARGET = kv-storage

ARGS = \
	-std=c23 \
	-O2 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror

INCLUDES = \
	-Icli/embedded-cli/lib/include/

SOURCES = \
	cli/cli.c \
	cli/cli_command_map.c \
	cli/embedded-cli/lib/src/embedded_cli.c \
	core/list.c \
	core/stack.c \
	main.c
	
linux:
	bear -- cc $(ARGS) -c $(SOURCES) $(INCLUDES)
	cc $(notdir $(SOURCES:.c=.o)) -o $(TARGET)

clean:
	rm -f kv-storage *.o

distclean: clean
	rm -f compile_commands.json
	rm -rf .cache
