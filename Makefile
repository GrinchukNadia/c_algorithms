NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iinclude

SRCS = src/main.c \
	src/input/parse_input.c \
	src/input/parse_utils.c \
	src/operations/push.c \
	src/operations/swap.c \
	src/operations/rotate.c \
	src/operations/reverse.c \
	src/operations/operation_utils.c \
	src/stack/stack_utils.c \
	src/stack/disorder.c \
	src/sorting/small.c \
	src/sorting/simple.c \
	src/sorting/medium.c \
	src/sorting/complex.c \
	src/sorting/adaptive.c \
	src/sorting/sort_utils.c \
	src/utils/print_utils.c \
	src/utils/benchmark.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c include/push_swap.h Makefile
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re