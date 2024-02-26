/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:57:49 by nvallin           #+#    #+#             */
/*   Updated: 2024/02/26 17:34:02 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

typedef struct s_data
{
	int				collectibles;
	int				size[2];
	int				p_pos[2];
	int				player_dir;
	int				moves;
	int				game_status;
	mlx_image_t		*collectible;
	mlx_image_t		*wall;
	mlx_image_t		*empty;
	mlx_image_t		*exit[7];
	mlx_image_t		*player[20];
	mlx_image_t		*asteroid[2];
	mlx_image_t		*count_img;
	mlx_texture_t	*collectible_t;
	mlx_texture_t	*wall_t;
	mlx_texture_t	*empty_t;
	mlx_texture_t	*exit_t[7];
	mlx_texture_t	*player_t[20];
	mlx_texture_t	*asteroid_t[2];
	mlx_t			*mlx;
	char			**map;
}			t_data;

char	*get_map_str(int fd);
char	**get_map_matrix(char *map_str, t_data *data);
char	**get_map(char *file, t_data *data);
char	*ft_strcombine(char *dest, char *src);
int		valid_map_str(char *map_str, t_data *data);
int		valid_map_size(char *map_str, t_data *data);
int		valid_map_data(char *map_str, t_data *data);
int		valid_map_borders(char *map, t_data *data);
int		valid_path(char **map, int y, int x, t_data *data);
int		valid_map(char *map_str, t_data *data);
void	find_start(char **map, t_data *data);
void	free_map(char **map, int y);
void	disable_player_images(mlx_image_t **player);
void	animate_player(t_data *data);
void	animate_explosion(mlx_image_t **player, int *game_status);
void	animate_teleport(t_data *data);
void	animate_asteroid(mlx_image_t **asteroid, int *frames, int *axis, int i);
void	animate_exit(mlx_image_t **exit, int collectibles);
void	asteroids(mlx_image_t **ast, mlx_image_t **p, int *stat, int *axis);
void	set_asteroids(mlx_image_t **asteroid, int rand_x, int rand_y);
void	player_direction(t_data *data, int dir);
void	move_player_y(t_data *data, keys_t key);
void	move_player_x(t_data *data, keys_t key);
void	check_position(mlx_image_t *c, mlx_image_t **p, t_data *data);
void	game_hook(void *param);
void	move_hook(mlx_key_data_t keydata, void *param);
void	move_counter(mlx_t *mlx, mlx_image_t **count_img, int moves, int x);
void	get_player_images(t_data *data);
void	get_endgame_images(t_data *data);
void	get_exit_images(t_data *data);
void	get_images(t_data *data);
void	set_background(mlx_t *mlx, t_data *data);
void	draw_map(mlx_t *mlx, char **map, t_data *data);
void	draw_exit_or_player(t_data *data, int x, int y, char obj);
void	draw_asteroids(t_data *data, mlx_image_t **asteroid);
void	end_game_messages(mlx_t *mlx, int *axis, int game_status);
void	init_textures(t_data *data);
void	free_and_terminate(t_data *data, int i);

#endif
