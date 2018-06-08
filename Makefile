NAME = coin_hunter
CC = gcc
CFLAGS = -O3 -Wall -Wextra -Werror
SRC = wolf3d.c control.c dimensions.c fill.c project3d.c fill_walls.c \
pickups.c cool_program.c
OBJ = $(SRC:.c=.o)

GRAPHICS = -framework OpenGL -framework AppKit -lpthread
MLX_LNK = -L ./minilibx_macos -lmlx
FT_LNK = -L ./libft -lft

all:
	$(CC) $(CFLAGS) $(MLX_LNK) $(FT_LNK) $(GRAPHICS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
