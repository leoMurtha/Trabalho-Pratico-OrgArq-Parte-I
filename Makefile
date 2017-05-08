all:
	@gcc -o menu menu.c rff.c filestrings.c -I./ -g -lm
run:
	@./menu
frun:
	@valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all ./menu
