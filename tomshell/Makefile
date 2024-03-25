NAME 	= minishell

OBJ	=	$(SRC:.c=.o)

SRC = main.c \
		linked_list.c \
		helper_ft.c \
		syntax_check.c \
		

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

COMP	=	$(CC) $(CFLAGS)

RM		=	rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C libft
	$(COMP) $(OBJ) libft/libft.a -lreadline -o $(NAME)
clean:
	make clean -C libft
	$(RM) libft/*.o $(OBJ)

fclean:	clean
	make fclean -C libft
	$(RM) $(NAME)

re:			fclean all