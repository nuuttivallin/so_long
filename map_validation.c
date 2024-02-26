/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:53:14 by nvallin           #+#    #+#             */
/*   Updated: 2024/02/22 17:24:21 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h" 

int	valid_map_size(char *map_str, t_data *data)
{
	int	length;
	int	height;
	int	compare;
	int	i;

	i = 0;
	length = 0;
	height = 0;
	while (map_str[i])
	{
		while (map_str[i] && map_str[i++] != '\n')
			length++;
		if (height == 0)
			compare = length;
		if (length != compare)
			return (0);
		height++;
		length = 0;
	}
	if (map_str[i - 1] == '\n')
		return (0);
	data->size[0] = height;
	data->size[1] = compare;
	return (1);
}

int	valid_map_data(char *map_str, t_data *data)
{
	int	i;
	int	exit;
	int	player;

	i = 0;
	exit = 0;
	player = 0;
	data->collectibles = 0;
	while (map_str[i])
	{
		if (map_str[i] != '0' && map_str[i] != '1' && map_str[i] != 'C'
			&& map_str[i] != 'E' && map_str[i] != 'P' && map_str[i] != '\n')
			return (0);
		if (map_str[i] == 'C')
			data->collectibles++;
		if (map_str[i] == 'E')
			exit++;
		if (map_str[i] == 'P')
			player++;
		i++;
	}
	if (exit != 1 || player != 1 || data->collectibles < 1)
		return (0);
	return (1);
}

int	valid_map_borders(char *map_str, t_data *data)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	while (map_str[i])
	{
		x = 0;
		while (map_str[i] != '\n' && map_str[i])
		{
			if (y == 0 || y == data->size[0] - 1
				|| x == 0 || x == data->size[1] - 1)
			{
				if (map_str[i] != '1')
					return (0);
			}
			i++;
			x++;
		}
		if (map_str[i++] == '\0')
			break ;
		y++;
	}
	return (1);
}

int	valid_path(char **map, int y, int x, t_data *data)
{
	static int	exit = 0;
	static int	collect = 0;

	if (map[y][x] == 'E')
		exit = 1;
	if (map[y][x] == 'C')
		collect++;
	map[y][x] = '1';
	if (map[y + 1][x] != '1')
		valid_path(map, y + 1, x, data);
	if (map[y - 1][x] != '1')
		valid_path(map, y - 1, x, data);
	if (map[y][x + 1] != '1')
		valid_path(map, y, x + 1, data);
	if (map[y][x - 1] != '1')
		valid_path(map, y, x - 1, data);
	if (exit == 1 && collect == data->collectibles)
		return (1);
	return (0);
}
