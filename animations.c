/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:25:23 by nvallin           #+#    #+#             */
/*   Updated: 2024/02/23 14:53:11 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_explosion(mlx_image_t **player, int *game_status)
{
	static int	frames = 11;
	static int	i = 12;

	if (i < 16 && frames++ > 10)
	{
		if (i == 12)
			player[i++]->instances[0].enabled = 1;
		else
		{
			player[i - 1]->instances[0].enabled = 0;
			player[i++]->instances[0].enabled = 1;
			disable_player_images(player);
		}
		frames = 0;
	}
	else if (i == 16 && frames++ > 10)
	{
		player[15]->instances[0].enabled = 0;
		*game_status = 3;
	}
}

void	animate_teleport(t_data *data)
{
	static int	frames = 1;
	static int	i = 16;

	if (i < 20 && frames++ > 0)
	{
		if (i == 16)
			data->player[i++]->instances[0].enabled = 1;
		else
		{
			data->player[i - 1]->instances[0].enabled = 0;
			data->player[i++]->instances[0].enabled = 1;
			disable_player_images(data->player);
		}
		frames = 0;
	}
	else if (i == 20 && frames++ > 0)
		data->player[19]->instances[0].enabled = 0;
}

void	set_asteroids(mlx_image_t **asteroid, int rand_x, int rand_y)
{
	asteroid[0]->instances[0].x = -50;
	asteroid[0]->instances[0].y = -50;
	asteroid[1]->instances[0].x = -50;
	asteroid[1]->instances[0].y = -50;
	asteroid[0]->instances[1].x = -50;
	asteroid[0]->instances[1].y = rand_y;
	asteroid[1]->instances[1].x = -50;
	asteroid[1]->instances[1].y = rand_y;
	asteroid[0]->instances[2].x = rand_x;
	asteroid[0]->instances[2].y = -50;
	asteroid[1]->instances[2].x = rand_x;
	asteroid[1]->instances[2].y = -50;
	asteroid[0]->instances[3].x = -50;
	asteroid[0]->instances[3].y = rand_y / 2;
	asteroid[1]->instances[3].x = -50;
	asteroid[1]->instances[3].y = rand_y / 2;
	asteroid[0]->instances[4].x = rand_x / 2;
	asteroid[0]->instances[4].y = -50;
	asteroid[1]->instances[4].x = rand_x / 2;
	asteroid[1]->instances[4].y = -50;
}

void	animate_asteroid(mlx_image_t **asteroid, int *frames, int *axis, int i)
{
	if (asteroid[0]->instances[i].x < axis[1] * 50 + 100
		|| asteroid[0]->instances[i].y < axis[0] * 50 + 100)
	{
		asteroid[0]->instances[i].x += 6;
		asteroid[0]->instances[i].y += 6;
		asteroid[1]->instances[i].x += 6;
		asteroid[1]->instances[i].y += 6;
		if (asteroid[0]->enabled == 0 && *frames % 7 == 0)
		{
			asteroid[0]->enabled = 1;
			asteroid[1]->enabled = 0;
		}
		else if (asteroid[1]->enabled == 0 && *frames % 7 == 0)
		{
			asteroid[1]->enabled = 1;
			asteroid[0]->enabled = 0;
		}
	}
	if (*frames > 476)
		*frames = 0;
}

void	animate_exit(mlx_image_t **exit, int collectibles)
{
	static int	i = 0;

	if (collectibles == 0)
	{
		if (i < 6)
		{
			exit[i++]->instances[0].enabled = 0;
			exit[i]->instances[0].enabled = 1;
		}
		if (i >= 6)
		{
			exit[6]->instances[0].enabled = 0;
			exit[1]->instances[0].enabled = 1;
			i++;
		}
		if (i == 100)
			i = 0;
	}
}
