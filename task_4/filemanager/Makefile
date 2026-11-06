.PHONY: linux clean distclean

linux:
	bear -- gcc -std=c23 -O2 -Wall -Wextra -Wpedantic -Werror filemanager.c main.c -o filemanager

clean:
	rm -f filemanager *.out

distclean: clean
	rm compile_commands.json
	rm -rf .cache
