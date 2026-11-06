.PHONY: linux clean

linux:
	bear -- gcc -std=c23 -O2 -Wall -Wextra -Wpedantic -Werror filemanager.c main.c -o filemanager

clean:
	rm -f filemanager compile_commands.json *.out
	rm -rf .cache
