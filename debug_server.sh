make fclean &&
CFLAGS=-g3 make serverJ2T3 &&
#strace -ff ./serverJ2T3 "$@"
#valgrind --leak-check=full --show-leak-kinds=all ./serverJ2T3 "$@"
valgrind ./serverJ2T3 "$@"
echo "return = $?"
