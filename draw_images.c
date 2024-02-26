/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:19:28 by nvallin           #+#    #+#             */
/*   Updated: 2024/02/23 17:06:01 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	img_to_window_and_errorcheck(t_data *dt, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(dt->mlx, img, x, y) == -1)
	{
		write(2, "Error\nFailed to put an image to window\n", 39);
		free_map(dt->map, dt->size[0]);
		mlx_close_window(dt->mlx);
		mlx_terminate(dt->mlx);
		exit (1);
	}
}

void	draw_exit_or_player(t_data *data, int x, int y, char obj)
{
	int	i;

	i = -1;
	if (obj == 'E')
	{
		while (++i < 7)
			img_to_window_and_errorcheck(data, data->exit[i], x, y);
		while (--i > 0)
			data->exit[i]->instances->enabled = 0;
	}
	else
	{
		while (++i < 20)
		{
			img_to_window_and_errorcheck(data, data->player[i], x, y);
			if (i > 0 && i < 20)
				data->player[i]->instances[0].enabled = 0;
		}
		data->player_dir = 0;
		data->moves = 0;
	}
}

void	set_background(mlx_t *mlx, t_data *data)
{
	mlx_texture_t	*bg_tx;
	mlx_image_t		*bg;

	bg_tx = mlx_load_png("./textures/purple.png");
	if (!bg_tx)
	{
		free_map(data->map, data->size[0]);
		mlx_terminate(mlx);
		write(2, "Error\nFailed to load background image\n", 38);
		exit (1);
	}
	bg = mlx_texture_to_image(mlx, bg_tx);
	mlx_resize_image(bg, data->size[1] * 50 + 100, data->size[0] * 50 + 100);
	img_to_window_and_errorcheck(data, bg, 0, 0);
	mlx_delete_texture(bg_tx);
	get_images(data);
	img_to_window_and_errorcheck(data, data->empty, 50, 50);
}

void	draw_map(mlx_t *mlx, char **map, t_data *data)
{
	int	y;
	int	x;

	y = 50;
	x = 50;
	set_background(mlx, data);
	while ((y - 50) / 50 < data->size[0])
	{
		while ((x - 50) / 50 < data->size[1])
		{
			if (map[(y - 50) / 50][(x - 50) / 50] == '1')
				img_to_window_and_errorcheck(data, data->wall, x, y);
			if (map[(y - 50) / 50][(x - 50) / 50] == 'C')
				img_to_window_and_errorcheck(data, data->collectible, \
											x + 5, y + 15);
			if (map[(y - 50) / 50][(x - 50) / 50] == 'E')
				draw_exit_or_player(data, x + 10, y + 10, 'E');
			if (map[(y - 50) / 50][(x - 50) / 50] == 'P')
				draw_exit_or_player(data, x, y, 'P');
			x += 50;
		}
		y += 50;
		x = 50;
	}
	draw_asteroids(data, data->asteroid);
}

void	draw_asteroids(t_data *data, mlx_image_t **asteroid)
{
	img_to_window_and_errorcheck(data, asteroid[0], -500, -500);
	img_to_window_and_errorcheck(data, asteroid[1], -500, -500);
	img_to_window_and_errorcheck(data, asteroid[0], -500, 100);
	img_to_window_and_errorcheck(data, asteroid[1], -500, 100);
	img_to_window_and_errorcheck(data, asteroid[0], 100, -500);
	img_to_window_and_errorcheck(data, asteroid[1], 100, -500);
	img_to_window_and_errorcheck(data, asteroid[0], -500, 200);
	img_to_window_and_errorcheck(data, asteroid[1], -500, 200);
	img_to_window_and_errorcheck(data, asteroid[0], 200, -500);
	img_to_window_and_errorcheck(data, asteroid[1], 200, -500);
	asteroid[0]->enabled = 0;
}
