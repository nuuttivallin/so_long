/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:33:26 by nvallin           #+#    #+#             */
/*   Updated: 2024/02/20 19:00:01 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	disable_player_images(mlx_image_t **player)
{
	int	i;

	i = 0;
	while (i < 12)
		player[i++]->instances->enabled = 0;
}

void	animate_player(t_data *data)
{
	int			image;
	static int	animation = 1;
	static int	frames = 0;

	if (data->game_status == 0)
	{
		image = data->player_dir + animation;
		if (frames > 5)
		{
			disable_player_images(data->player);
			if (image < data->player_dir + 3)
			{
				data->player[image++]->instances[0].enabled = 1;
				animation++;
			}
			else
			{
				data->player[data->player_dir]->instances[0].enabled = 1;
				animation = 1;
			}
			frames = 0;
		}
		frames++;
	}
}

void	player_direction(t_data *data, int dir)
{
	disable_player_images(data->player);
	data->player[dir]->instances[0].enabled = 1;
	data->player_dir = dir;
}

void	move_player_y(t_data *data, keys_t key)
{
	int	i;

	i = 0;
	if (key == MLX_KEY_W || key == MLX_KEY_UP)
	{
		player_direction(data, 0);
		if (data->map[data->p_pos[0] - 1][data->p_pos[1]] != '1')
		{
			while (i < 20)
				data->player[i++]->instances[0].y -= 50;
			data->p_pos[0] -= 1;
			data->moves++;
		}
	}
	if (key == MLX_KEY_S || key == MLX_KEY_DOWN)
	{
		player_direction(data, 3);
		if (data->map[data->p_pos[0] + 1][data->p_pos[1]] != '1')
		{
			while (i < 20)
				data->player[i++]->instances[0].y += 50;
			data->p_pos[0] += 1;
			data->moves++;
		}
	}
}

void	move_player_x(t_data *data, keys_t key)
{
	int	i;

	i = 0;
	if (key == MLX_KEY_A || key == MLX_KEY_LEFT)
	{
		player_direction(data, 6);
		if (data->map[data->p_pos[0]][data->p_pos[1] - 1] != '1')
		{
			while (i < 20)
				data->player[i++]->instances[0].x -= 50;
			data->p_pos[1] -= 1;
			data->moves++;
		}
	}
	if (key == MLX_KEY_D || key == MLX_KEY_RIGHT)
	{
		player_direction(data, 9);
		if (data->map[data->p_pos[0]][data->p_pos[1] + 1] != '1')
		{
			while (i < 20)
				data->player[i++]->instances[0].x += 50;
			data->p_pos[1] += 1;
			data->moves++;
		}
	}
}
