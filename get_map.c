/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:58:39 by nvallin           #+#    #+#             */
/*   Updated: 2024/02/21 18:29:30 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h" 

char	*get_map_str(int fd)
{
	char	*map_str;
	char	buff[10];

	map_str = NULL;
	ft_bzero(buff, 10);
	while (read(fd, buff, 9) > 0)
	{
		if (map_str == NULL)
			map_str = ft_strdup(buff);
		else
			map_str = ft_strcombine(map_str, buff);
		if (!map_str)
			return (0);
		ft_bzero(buff, 10);
	}
	close(fd);
	if (!map_str)
		write(2, "Error\nEmpty file\n", 17);
	return (map_str);
}

char	**get_map_matrix(char *map_str, t_data *data)
{
	char	**map;
	int		y;
	int		x;
	int		i;

	y = 0;
	i = 0;
	map = malloc(sizeof(char *) * (data->size[0]));
	if (!map)
		return (0);
	while (y < data->size[0])
	{
		map[y] = malloc(sizeof(char) * (data->size[1] + 1));
		if (!map[y])
		{
			free_map(map, y);
			return (0);
		}
		x = 0;
		while (map_str[i] != '\n' && map_str[i] != '\0')
			map[y][x++] = map_str[i++];
		map[y++][x] = '\0';
		i++;
	}
	return (map);
}

char	**get_map(char *file, t_data *data)
{
	char		*map_str;
	char		**map;
	int			fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nFailed to open file\n", 26);
		return (0);
	}
	map_str = get_map_str(fd);
	if (!map_str)
		return (0);
	if (!valid_map(map_str, data))
	{
		free(map_str);
		return (0);
	}
	map = get_map_matrix(map_str, data);
	free(map_str);
	if (!map)
		return (0);
	return (map);
}

char	*ft_strcombine(char *dest, char *src)
{
	int		i;
	int		i2;
	char	*new;

	if (src == NULL)
	{
		if (dest != NULL)
			free(dest);
		return (NULL);
	}
	i = ft_strlen(dest);
	i2 = ft_strlen(src);
	new = malloc((sizeof(char) * (i + i2 + 1)));
	if (!new)
	{
		free(dest);
		return (NULL);
	}
	ft_strlcpy(new, dest, i + 1);
	i2 = 0;
	while (src[i2] != '\0')
		new[i++] = src[i2++];
	new[i] = '\0';
	free(dest);
	return (new);
}
