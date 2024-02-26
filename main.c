/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:10:54 by nvallin           #+#    #+#             */
/*   Updated: 2024/02/23 17:03:26 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_textures(t_data *data)
{
	int	i;

	i = 0;
	data->collectible_t = NULL;
	data->wall_t = NULL;
	data->empty_t = NULL;
	while (i < 7)
		data->exit_t[i++] = NULL;
	i = 0;
	while (i < 20)
		data->player_t[i++] = NULL;
	data->asteroid_t[0] = NULL;
	data->asteroid_t[1] = NULL;
	i = 0;
	data->collectible = NULL;
	data->wall = NULL;
	data->empty = NULL;
	while (i < 7)
		data->exit[i++] = NULL;
	i = 0;
	while (i < 20)
		data->player[i++] = NULL;
	data->asteroid[0] = NULL;
	data->asteroid[1] = NULL;
}

void	free_and_terminate(t_data *data, int i)
{
	if (data->collectible_t != NULL)
		mlx_delete_texture(data->collectible_t);
	if (data->wall_t != NULL)
		mlx_delete_texture(data->wall_t);
	if (data->empty_t != NULL)
		mlx_delete_texture(data->empty_t);
	while (++i < 7)
	{
		if (data->exit_t[i] != NULL)
			mlx_delete_texture(data->exit_t[i]);
	}
	i = -1;
	while (++i < 20)
	{
		if (data->player_t[i] != NULL)
			mlx_delete_texture(data->player_t[i]);
	}
	if (data->asteroid_t[0] != NULL)
		mlx_delete_texture(data->asteroid_t[0]);
	if (data->asteroid_t[1] != NULL)
		mlx_delete_texture(data->asteroid_t[1]);
	free_map(data->map, data->size[0]);
	mlx_terminate(data->mlx);
	write(2, "Error\nSomething wrong with textures\n", 36);
	exit (1);
}

void	end_game_messages(mlx_t *mlx, int *axis, int game_status)
{
	mlx_image_t	*end[2];
	static int	game_over = 0;

	end[0] = NULL;
	end[1] = NULL;
	if (game_status != 0)
	{
		if (!game_over)
		{
			if (game_status == 1)
				end[0] = mlx_put_string(mlx, "You Win! So long...", \
				axis[1] * 25 - 40, axis[0] * 25);
			else
				end[0] = mlx_put_string(mlx, "Game Over! So long...", \
				axis[1] * 25 - 40, axis[0] * 25);
			end[1] = mlx_put_string(mlx, "Press ESC to quit", \
			axis[1] * 25 - 40, axis[0] * 25 + 50);
			game_over = 1;
		}
	}
}

void	free_map(char **map, int y)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		while (i < y && map[i])
		{
			free(map[i]);
			map[i++] = NULL;
		}
		free(map);
		map = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2 && !ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".ber", 4))
	{
		init_textures(&data);
		data.map = get_map(argv[1], &data);
		if (!data.map)
			return (1);
		mlx_set_setting(MLX_STRETCH_IMAGE, 1);
		data.mlx = mlx_init(data.size[1] * 50 + 100, data.size[0] * 50 + 100, \
							"so_long", true);
		if (!data.mlx)
			return (1);
		draw_map(data.mlx, data.map, &data);
		mlx_key_hook(data.mlx, move_hook, &data);
		mlx_loop_hook(data.mlx, game_hook, &data);
		mlx_loop(data.mlx);
		free_map(data.map, data.size[0]);
		mlx_terminate(data.mlx);
		return (EXIT_SUCCESS);
	}
	write(2, "Error\nInvalid argument\n", 23);
	return (1);
}
