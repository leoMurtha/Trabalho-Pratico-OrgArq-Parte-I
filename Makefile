all:
	@gcc -o menu menu.c rff.c filestrings.c rsi.c -I./ -g -Wall -lm
run:
	@./menu
frun:
	@valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all ./rff
