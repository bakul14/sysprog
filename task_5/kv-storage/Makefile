.PHONY: linux clean distclean

linux:
	bear -- gcc -std=c23 -O2 -Wall -Wextra -Wpedantic -Werror -c main.c
	gcc main.o -o kv-storage

clean:
	rm -f kv-storage *.o

distclean: clean
	rm -f compile_commands.json
	rm -rf .cache
