.PHONY: linux clean distclean

linux:
	bear -- gcc -std=c23 -O2 -Wall -Wextra -Wpedantic -Werror -c filemanager.c main.c
	gcc filemanager.o main.o -o filemanager

clean:
	rm -f filemanager *.o

distclean: clean
	rm compile_commands.json
	rm -rf .cache
