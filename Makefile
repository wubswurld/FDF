NAME = fdf

CFILES = main.c draw.c rotate.c parse.c keypress.c free.c

FLAGS = -Wall -Werror -Wextra -g 
# -fsanitize=address

LIBFT = libft

MINLIB = Minilibx

MINILIBX = -I Minilibx -L Minilibx -lmlx -framework OpenGL -framework AppKit

GCC = gcc

all: $(NAME)

$(NAME):
	@echo "\033[32mCompiling files . . .\033[0;33m"
	@make -C $(LIBFT)
	@make -C $(MINLIB)
	$(GCC) $(FLAGS) $(MINILIBX) $(CFILES) -L $(LIBFT) -lft -o $(NAME) 

clean:
	@echo "\033[32mCleaning .\033[0;33m"
	@rm -rf $(NAME)
	@make clean -C $(LIBFT)

fclean: clean
	@echo "\033[32mClean more . .\033[0;33m"
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: clean fclean all re