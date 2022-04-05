/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:50:03 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/05 23:02:55 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_errors.h"

/*static void	increase_mapsize(int **str)
{
	char	*new;
	int		strlen;

	strlen = ft_digitcount(*)
	new = ft_memalloc(strlen * 2 * sizeof(signed int));
	if (new == NULL)
		error_exit("Str malloc failed (increase_mapsize)");
	ft_memcpy(new, *str, strlen * sizeof(signed int));
	free(*str);
	str = &new;
}*/

static signed int	*get_mapdata(t_map *map, int fd)
{
	int				i;
	unsigned char	buf[2];
	signed int		*str;

	str = (signed int *)ft_memalloc(MAPSIZE_MAX * sizeof(signed int));
	if (str == NULL)
		error_exit("Str malloc failed (get_mapdata).");
	ft_bzero(buf, 2);
	i = 0;
	while (read(fd, buf, 1) == 1)
	{
		if (i >= MAPSIZE_MAX)
			error_exit("Map length exceeds MAPSIZE_MAX (get_mapdata)");
		if (ft_isdigit(*buf) || *buf == '-')
		{
			read_mapnode(fd, (char *)buf, &(str[i]), *buf == '-');
			map->z_extreme = ft_max(ft_abs(str[i]), map->z_extreme);
		}
		if (*buf == '\n' || *buf == '\t' || *buf == ' ')
			map->width += (i++, (map->width == 0 && *buf == '\n') * i);
		else
			error_exit("Invalid character (get_mapdata)");
		if (*buf == '\n' && map->width != 0 && i % map->width != 0)
			error_exit("Invalid map shape (get_mapdata)");
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
	float			**points;
	t_map			map;
	signed int		*data;

	fd = file_open(filename);
	ft_bzero(&map, sizeof(t_map));
	data = get_mapdata(&map, fd);
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
	map_to_tri_map(&map, trimap);
	free_map(&map);
}
