CC=cc
CFLAGS=-Wall -Wextra -Werror
DEPENDENCIES=./libft/libft.a
SRC=ft_get_argument.c ft_printf.c ft_printf_options.c
OBJ=$(SRC:.c=.o)
NAME=libftprintf.a

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $@ $?

libft.a:
	(cd libft && make bonus)

bonus: $(BONUS_OBJ)
	make $(NAME)
	ar -rcs $(NAME) $?

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJ)

re: fclean all

.PHONY : fclean clean all re bonus
