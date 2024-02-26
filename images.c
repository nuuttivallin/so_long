/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:16:31 by nvallin           #+#    #+#             */
/*   Updated: 2024/02/23 17:04:07 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_player_images(t_data *data)
{
	int	i;

	i = 0;
	data->player_t[0] = mlx_load_png("./textures/player_u.png");
	data->player_t[1] = mlx_load_png("./textures/player_u2.png");
	data->player_t[2] = mlx_load_png("./textures/player_u3.png");
	data->player_t[3] = mlx_load_png("./textures/player_d.png");
	data->player_t[4] = mlx_load_png("./textures/player_d2.png");
	data->player_t[5] = mlx_load_png("./textures/player_d3.png");
	data->player_t[6] = mlx_load_png("./textures/player_l.png");
	data->player_t[7] = mlx_load_png("./textures/player_l2.png");
	data->player_t[8] = mlx_load_png("./textures/player_l3.png");
	data->player_t[9] = mlx_load_png("./textures/player_r.png");
	data->player_t[10] = mlx_load_png("./textures/player_r2.png");
	data->player_t[11] = mlx_load_png("./textures/player_r3.png");
	while (i < 12)
	{
		if (!data->player_t[i])
			free_and_terminate(data, -1);
		data->player[i] = mlx_texture_to_image(data->mlx, data->player_t[i]);
		mlx_delete_texture(data->player_t[i]);
		data->player_t[i++] = NULL;
	}
}

void	get_endgame_images(t_data *data)
{
	int	i;

	i = 12;
	data->player_t[12] = mlx_load_png("./textures/explosion.png");
	data->player_t[13] = mlx_load_png("./textures/explosion2.png");
	data->player_t[14] = mlx_load_png("./textures/explosion3.png");
	data->player_t[15] = mlx_load_png("./textures/explosion4.png");
	data->player_t[16] = mlx_load_png("./textures/teleport.png");
	data->player_t[17] = mlx_load_png("./textures/teleport2.png");
	data->player_t[18] = mlx_load_png("./textures/teleport3.png");
	data->player_t[19] = mlx_load_png("./textures/teleport4.png");
	while (i < 20)
	{
		if (!data->player_t[i])
			free_and_terminate(data, -1);
		data->player[i] = mlx_texture_to_image(data->mlx, data->player_t[i]);
		mlx_delete_texture(data->player_t[i]);
		data->player_t[i++] = NULL;
	}
}

void	get_exit_images(t_data *data)
{
	int	i;

	i = 0;
	data->exit_t[0] = mlx_load_png("./textures/exit.png");
	data->exit_t[1] = mlx_load_png("./textures/exit_open.png");
	data->exit_t[2] = mlx_load_png("./textures/exit_open2.png");
	data->exit_t[3] = mlx_load_png("./textures/exit_open3.png");
	data->exit_t[4] = mlx_load_png("./textures/exit_open4.png");
	data->exit_t[5] = mlx_load_png("./textures/exit_open5.png");
	data->exit_t[6] = mlx_load_png("./textures/exit_open6.png");
	while (i < 7)
	{
		if (data->exit_t[i] == NULL)
			free_and_terminate(data, -1);
		data->exit[i] = mlx_texture_to_image(data->mlx, data->exit_t[i]);
		mlx_delete_texture(data->exit_t[i]);
		data->exit_t[i++] = NULL;
	}
}

void	get_images(t_data *data)
{
	get_player_images(data);
	get_endgame_images(data);
	get_exit_images(data);
	data->collectible_t = mlx_load_png("./textures/collectible.png");
	data->wall_t = mlx_load_png("./textures/wall.png");
	data->empty_t = mlx_load_png("./textures/empty.png");
	data->asteroid_t[0] = mlx_load_png("./textures/asteroid.png");
	data->asteroid_t[1] = mlx_load_png("./textures/asteroid2.png");
	if (!data->collectible_t || !data->wall_t || !data->empty_t
		|| !data->asteroid_t[0] || !data->asteroid_t[1])
		free_and_terminate(data, -1);
	data->collectible = mlx_texture_to_image(data->mlx, data->collectible_t);
	data->wall = mlx_texture_to_image(data->mlx, data->wall_t);
	data->empty = mlx_texture_to_image(data->mlx, data->empty_t);
	data->asteroid[0] = mlx_texture_to_image(data->mlx, data->asteroid_t[0]);
	data->asteroid[1] = mlx_texture_to_image(data->mlx, data->asteroid_t[1]);
	mlx_delete_texture(data->collectible_t);
	mlx_delete_texture(data->wall_t);
	mlx_delete_texture(data->empty_t);
	mlx_delete_texture(data->asteroid_t[0]);
	mlx_delete_texture(data->asteroid_t[1]);
	mlx_resize_image(data->empty, data->size[1] * 50, data->size[0] * 50);
}
