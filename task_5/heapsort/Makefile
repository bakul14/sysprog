.PHONY: linux clean distclean

TARGET = heapsort

ARGS = \
	-std=c23 \
	-O2 \
	-Wall \
	-Werror \
	-Wextra \
	-Wpedantic \
	-Wsign-conversion

SOURCES = \
	app/heapsort.c \
	app/parser.c \
	core/array.c \
	core/heap.c \
	main.c

linux:
	bear -- cc $(ARGS) -c $(SOURCES)
	cc $(notdir $(SOURCES:.c=.o)) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o

distclean: clean
	rm -f compile_commands.json
	rm -rf .cache
