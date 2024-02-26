CFILES = get_map.c map_validation.c check_map.c player.c hooks.c images.c animations.c draw_images.c  main.c

OFILES = $(CFILES:.c=.o)

LIB = libft.a

LIBDIR = libft

MLX = $(MLXDIR)/build/libmlx42.a

MLXDIR = MLX42

CC = cc

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

NAME = so_long

all: $(LIB) $(MLX) $(NAME)

$(LIB):
	$(MAKE) -C $(LIBDIR)

$(MLX):
	cd $(MLXDIR) && cmake -B build
	cd $(MLXDIR) && cmake --build build -j4

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) $(LIBDIR)/$(LIB) $(MLX) $(MLXFLAGS) -o $(NAME)

clean:
	rm -f $(OFILES)
	$(MAKE) -C $(LIBDIR) clean
	$(MAKE) -C $(MLXDIR)/build clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBDIR) fclean
	cd $(MLXDIR) && rm -rf build

re: fclean all

.PHONY: all clean fclean re
