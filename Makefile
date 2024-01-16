NAME			:=	pipex

LIBPATH			:=	-L libft -l ft
LIB				:=	libft.a

INCPATH			:=	-I includes
FILES			:=	pipex.c			\
					child_process.c	\
					utils.c

SRCPATH			:=	src
SRC				:=	$(addprefix $(SRCPATH)/,$(FILES))

OBJPATH			:=	obj
OBJ				:=	$(addprefix $(OBJPATH)/,$(FILES:.c=.o))

DEFAULT			:=	"\033[0m"
YELLOW			:=	"\033[0;33m"
RED				:=	"\033[0;31m"
GREEN			:=	"\033[0;32m"

CC				:=	cc

RM				:=	rm -f

CFLG			:=	-Wall -Werror -Wextra -g3

all				:	$(NAME)

$(OBJPATH)		:
					@mkdir $@

$(NAME)			:	$(OBJPATH) $(OBJ)
					@make -s -C libft
					@echo "Libft compilation..."
					@$(CC) $(OBJ) -o $(NAME) $(LIBPATH)
					@echo -n $(YELLOW)
					@echo -n "$(NAME) created"
					@echo $(GREEN)
					@sleep 1
					@echo "Project successfully compiled"
					@echo -n $(DEFAULT)

$(OBJPATH)/%.o	:	$(SRCPATH)/%.c
					@sleep 0.2
					@$(CC) $(CFLG) -c $< -o $@ $(INCPATH)
					@printf "%s\n" $<

.PHONY			:	all re fclean clean

re				:	fclean all

clean			:
					@echo -n $(RED)
					@$(RM) $(OBJ)
					@$(RM) $(OBJ_B)
					@echo "Removed the object files..."
					@make clean -s -C libft
					@echo -n $(DEFAULT)
					@sleep 0.2

fclean			:	clean
					@echo -n $(RED)
					@$(RM) $(NAME)
					@$(RM) $(LIB)
					@echo "Removed $(NAME) and $(LIB)"
					@make fclean -s -C libft
					@echo -n $(DEFAULT)
					@sleep 0.2