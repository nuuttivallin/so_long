/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:03:11 by nvallin           #+#    #+#             */
/*   Updated: 2024/02/23 15:55:19 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_position(mlx_image_t *c, mlx_image_t **p, t_data *data)
{
	int	i;

	i = 0;
	animate_player(data);
	if (data->map[data->p_pos[0]][data->p_pos[1]] == 'C')
	{
		while (c->instances[i].x - 5 != p[0]->instances[0].x
			|| c->instances[i].y - 15 != p[0]->instances[0].y)
			i++;
		if (c->instances[i].enabled == 1)
		{
			c->instances[i].enabled = 0;
			data->collectibles--;
		}
	}
	if (data->map[data->p_pos[0]][data->p_pos[1]] == 'E'
		&& data->collectibles == 0)
	{
		disable_player_images(p);
		data->game_status = 1;
		animate_teleport(data);
	}
}

void	asteroids(mlx_image_t **ast, mlx_image_t **p, int *stat, int *axis)
{
	static int	frames = 222;
	static int	i = -1;
	static int	rand_x = 0;
	static int	rand_y = 0;

	if (rand_x++ > axis[1] * 50)
		rand_x = 0;
	if (rand_y++ > axis[0] * 50)
		rand_y = 0;
	if (frames++ > 420 && ast[0]->instances[0].y > axis[0] * 50 + 90)
		set_asteroids(ast, rand_x, rand_y);
	while (++i < 5)
	{
		animate_asteroid(ast, &frames, axis, i);
		if (ast[0]->instances[i].x + 30 > p[0]->instances[0].x
			&& ast[0]->instances[i].x + 30 < p[0]->instances[0].x + 50
			&& ast[0]->instances[i].y + 30 > p[0]->instances[0].y
			&& ast[0]->instances[i].y + 30 < p[0]->instances[0].y + 50)
		{
			*stat = 2;
			ast[0]->instances[i].enabled = 0;
			ast[1]->instances[i].enabled = 0;
		}
	}
	i = -1;
}

void	game_hook(void *param)
{
	t_data	*data;

	data = param;
	check_position(data->collectible, data->player, data);
	animate_exit(data->exit, data->collectibles);
	if (data->game_status == 0)
		asteroids(data->asteroid, data->player, &data->game_status, data->size);
	if (data->game_status == 2)
		animate_explosion(data->player, &data->game_status);
	move_counter(data->mlx, &data->count_img, data->moves, data->size[1]);
	end_game_messages(data->mlx, data->size, data->game_status);
}

void	move_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
	{
		if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			&& data->game_status == 0)
			move_player_y(data, keydata.key);
	}
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D
		|| keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
	{
		if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			&& data->game_status == 0)
			move_player_x(data, keydata.key);
	}
}

void	move_counter(mlx_t *mlx, mlx_image_t **count_img, int moves, int x)
{
	static int	temp = -1;
	mlx_image_t	*moves_img;
	char		*count_str;

	if (moves > temp)
	{
		count_str = ft_itoa(moves);
		if (!count_str)
		{
			write(2, "Error\nMove counter failed\n", 26);
			mlx_close_window(mlx);
		}
		ft_printf("Moves: %d\n", moves);
		if (moves == 0)
			moves_img = mlx_put_string(mlx, "Moves:", x * 25, 30);
		if (*count_img)
			mlx_delete_image(mlx, *count_img);
		*count_img = mlx_put_string(mlx, count_str, x * 25 + 70, 30);
		temp = moves;
		free(count_str);
	}
}
