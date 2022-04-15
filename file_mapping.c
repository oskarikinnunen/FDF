/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:50:03 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/15 02:34:17 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_errors.h"

static void	get_mapdata(t_map *map, int fd, signed int *data)
{
	int				i;
	char			buf[2];

	ft_bzero(buf, 2);
	i = 0;
	while (read(fd, buf, 1) > 0 && i < MAPSIZE_MAX)
	{
		if ((ft_isdigit(*buf) || *buf == '-')
			&& read_mapnode(fd, buf, &data[i], map) > 0)
		{
			i++;
			if (*buf == '\n')
			{
				if (map->width == 0)
					map->width = i;
				if (i % map->width != 0 || map->width == 1)
					error_exit("Invalid map shape (get_mapdata)");
			}
		}
		else if (*buf != '\t' && *buf != ' ')
			error_exit("Invalid character in map (get_mapdata)");
	}
	map->length = i;
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
