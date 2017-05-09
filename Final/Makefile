all:
	@gcc -o menu src/menu.c src/rdr.c src/rff.c src/filestrings.c src/rsi.c -I./include -std=c99 -g -Wall -lm
run:
	@./menu
frun:
	@valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all ./menu
