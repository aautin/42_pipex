NAME		=	pipex

LIB			=	libft.a

SRC			=	src/main.c				\
				src/parsing.c

SRC_B		=	src/main_bonus.c		\
				src/utils_bonus.c

OBJ			=	$(SRC:.c=.o)

OBJ_B		=	$(SRC_B:.c=.o)

CC			=	cc

RM			=	rm -f

CFLG		+=	-Wall -Werror -Wextra

$(NAME)		:	$(OBJ)
				make -C libft
				cp libft/libft.a $(LIB)
				$(CC) $(OBJ) -o $(NAME) $(LIB)

bonus		:	$(OBJ_B)
				make -C libft
				cp libft/libft.a $(LIB)
				$(CC) $(OBJ_B) -o $(NAME) $(LIB)

%.o			:	%.c
				$(CC) $(CFLG) -c $< -o $@ -g3

.PHONY		:	all re fclean clean libclean libfclean bonus

re			:	fclean all

all			:	$(NAME)

clean		:
				$(RM) $(OBJ)
				$(RM) $(OBJ_B)
				$(RM) $(LIB)

fclean		:	clean
				$(RM) $(NAME)

libclean	:
				make clean -C libft

libfclean	:
				make fclean -C libft