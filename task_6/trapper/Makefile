.PHONY: linux clean distclean

TARGET = trapper

ARGS = \
	-std=c23 \
	-O2 \
	-Wall \
	-Werror \
	-Wextra \
	-Wpedantic \
	-Wsign-conversion

SOURCES = \
	main.c

linux:
	bear -- cc $(ARGS) -c $(SOURCES)
	cc $(notdir $(SOURCES:.c=.o)) -o $(TARGET)

clean:
	rm -f trapper *.o

distclean: clean
	rm -f compile_commands.json
	rm -rf .cache
