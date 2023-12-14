NAME		=	pipex

LIB			=	libft.a

SRC			=	src/main.c				\
				src/errors_mgmt.c		\
				src/parsing.c			\
				src/utils.c

OBJ			=	$(SRC:.c=.o)

CC			=	cc

RM			=	rm -f

CFLG		+=	-Wall -Werror -Wextra

$(NAME)		:	$(OBJ)
				make -C libft
				cp libft/libft.a $(LIB)
				$(CC) $(OBJ) -o $(NAME) $(LIB)

%.o			:	%.c
				$(CC) $(CFLG) -c $< -o $@ -g3

.PHONY		:	all re fclean clean libclean libfclean

re			:	fclean all

all			:	$(NAME)

clean		:
				$(RM) $(OBJ)
				$(RM) $(LIB)

fclean		:	clean
				$(RM) $(NAME)

libclean	:
				make clean -C libft

libfclean	:
				make fclean -C libft