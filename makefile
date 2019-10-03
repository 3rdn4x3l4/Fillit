NAME= fillit

SRCS= main.c\
	checkerror.c\
	reader.c\
	reader_2.c\
	solver.c\
	print.c\


OBJ= $(SRCS:.c=.o)

LIBDIR= libft

LIBA= $(LIBDIR)/libft.a

CFLAGS= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@make -s -C $(LIBDIR)
	@gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBA)
	@echo "fillit build complete"

%.o : %.c
	@gcc -I $(LIBDIR) $(CFLAGS) -o $@ -c $<

clean:
		@rm -rf $(OBJ)
		@echo "fillit objects cleaned"
		@make clean -C $(LIBDIR)

fclean:
		@make fclean -s -C $(LIBDIR)
		@rm -f $(NAME)
		@rm -rf $(OBJ)
		@echo "fillit objects cleaned"
		@echo "fillit project cleaned"

re: fclean all

.PHONY: all clean fclean re
