make fclean &&
CFLAGS=-g3 make clientJ2T3 &&
#strace -ff ./clientJ2T3 "$@"
#valgrind --leak-check=full --show-leak-kinds=all ./clientJ2T3 "$@"
valgrind ./clientJ2T3 "$@"
