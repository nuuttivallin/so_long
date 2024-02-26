/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:32:26 by nvallin           #+#    #+#             */
/*   Updated: 2024/02/23 11:52:50 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	valid_map_str(char *map_str, t_data *data)
{
	if (!valid_map_size(map_str, data))
	{
		write(2, "Error\nMap not rectangular\n", 26);
		return (0);
	}
	if (!valid_map_data(map_str, data))
	{
		write(2, "Error\nInvalid map content\n", 26);
		return (0);
	}
	if (!valid_map_borders(map_str, data))
	{
		write(2, "Error\nMap has no borders\n", 25);
		return (0);
	}
	return (1);
}

void	find_start(char **map, t_data *data)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (map[y][x] != 'P')
	{
		while (map[y][x] != '\0' && map[y][x] != 'P')
			x++;
		if (map[y][x] == 'P')
			break ;
		y++;
		x = 0;
	}
	data->p_pos[0] = y;
	data->p_pos[1] = x;
}

int	valid_map(char *map_str, t_data *data)
{
	char	**map_cpy;

	if (!valid_map_str(map_str, data))
		return (0);
	map_cpy = get_map_matrix(map_str, data);
	if (!map_cpy)
		return (0);
	find_start(map_cpy, data);
	if (!valid_path(map_cpy, data->p_pos[0], data->p_pos[1], data))
	{
		write(2, "Error\nValid path not found\n", 27);
		free_map(map_cpy, data->size[0]);
		return (0);
	}
	free_map(map_cpy, data->size[0]);
	return (1);
}
