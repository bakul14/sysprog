.PHONY: linux clean

linux:
	bear -- gcc -std=c23 -Wall -Wextra -Wpedantic -Werror filemanager.c main.c -o filemanager

clean:
	rm -f filemanager compile_commands.json
	rm -rf .cache
