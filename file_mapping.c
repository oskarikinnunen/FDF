/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:50:03 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/14 02:03:54 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_errors.h"

//static void ft_read(int *res, )

//TODO: FIX NORMINETTE
static signed int	*get_mapdata(t_map *map, int fd)
{
	int				i;
	unsigned char	buf[2];
	signed int		*str;
	int				res;

	str = (signed int *)ft_memalloc(MAPSIZE_MAX * sizeof(signed int));
	if (str == NULL)
		error_exit("Str malloc failed (get_mapdata).");
	ft_bzero(buf, 2);
	i = 0;
	while ((res = read(fd, buf, 1)) == 1 && i < MAPSIZE_MAX)
	{
		if ((ft_isdigit(*buf) || *buf == '-') && read_mapnode(fd, buf, &str[i], map) >= 0)
		{
			i++;
			if (*buf == '\n')
			{
				if (map->width == 0)
					map->width = i;
				else if (i % map->width != 0)
					error_exit("Invalid map shape (get_mapdata)");
			}
		}
		else if (*buf != '\t' && *buf != ' ')
			error_exit("Invalid character in map (get_mapdata)");
	}
	map->length = i;
	return (str);
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
	signed int		*data;

	fd = file_open(filename);
	ft_bzero(&map, sizeof(t_map));
	data = get_mapdata(&map, fd);
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
	free(data);
	map_to_tri_maps(&map, trimap);
	free_map(&map);
}
