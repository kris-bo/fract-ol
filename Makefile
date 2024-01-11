
NAME	= fractol

SRC		= main.c keyboard.c draw.c formulas.c utils.c mouse.c
OBJ		= $(SRC:.c=.o)

CC		= clang
CFLAGS	= -Wall -Wextra -Werror

MLX		= ./miniLibX/
MLX_LNK	= -L $(MLX) -l mlx -framework OpenGL -framework AppKit
MLX_LIB	= mlx.a

all : $(MLX_LIB) $(NAME)

$(MLX_LIB) :
	@make -C $(MLX)

%.o : %.c
	$(CC) -I $(MLX) -c $< -o $@

$(NAME) : $(OBJ) fractal.h Makefile
	$(CC) $(OBJ) $(MLX_LNK) -o $(NAME)

clean :
	make -C $(MLX) clean
	rm -f $(OBJ)

fclean : clean
	rm $(NAME)

re : fclean all

.PHONY : all clean fclean re