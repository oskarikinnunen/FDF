/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:50:03 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/21 13:40:33 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_errors.h"
#include <stdio.h>

static int	splen(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (i);
	while (split[i] != 0)
		i++;
	return (i);
}

static void	get_mapdata(t_map *map, int fd, signed int *data)
{
	char	*line;
	char	**split;
	int		i[2];

	ft_bzero(i, sizeof(int [2]));
	while (ft_get_next_line(fd, &line) > 0)
	{
		split = ft_strscrape(line, " \t");
		map->width += (map->width == 0) * splen(split);
		if (map->width != 0 && ((splen(split) % map->width) || map->width == 1))
			error_exit("invalid map shape");
		*i = 0;
		while (split[*i] && i[1] < MAPSIZE_MAX)
		{
			data[i[1]] = ft_clamp(ft_atoi(split[*i]), -128, 127);
			free(split[*i]);
			map->z_extreme = ft_max(map->z_extreme,
					ft_clamp(ft_abs(data[i[1]]), 1, 127));
			map->length = (i[1]++);
			(*i)++;
		}
		free(split[*i]);
		free(line);
		free(split);
	}
}

int	file_open(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd <= -1)
		error_exit("Failed to open file (file_open)");
	return (fd);
}

static void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i <= map->length)
	{
		free(map->points[i]);
		i++;
	}
	free(map->points);
}

void	read_inputmap(char *filename, t_tri_map *trimap)
{
	int				fd;
	int				cr[3];
	t_map			map;
	signed int		data[MAPSIZE_MAX];

	fd = file_open(filename);
	ft_bzero(&map, sizeof(t_map));
	map.width = 0;
	get_mapdata(&map, fd, data);
	if (map.width <= 0 || map.length < 1)
		error_exit("Invalid map length");
	map.points = ft_memalloc((map.length + 1) * sizeof(float *));
	ft_bzero(cr, sizeof(int) * 3);
	while (cr[Z] <= map.length)
	{
		if (cr[Z] != 0 && cr[Z] % map.width == 0)
			cr[X] = (cr[Y]++, 0);
		map.points[cr[Z]] = v3new(cr[X], cr[Y], (float)data[cr[Z]]);
		if (map.points[cr[Z]] == NULL)
			error_exit("Vector malloc failed in read_input");
		cr[Z] = (cr[X]++, cr[Z] + 1);
	}
	map_to_tri_maps(&map, trimap);
	free_map(&map);
}
