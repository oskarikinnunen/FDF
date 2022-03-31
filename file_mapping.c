/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:50:03 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/24 04:10:31 by okinnune         ###   ########.fr       */
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
	int			i;
	unsigned char	buf[2];
	signed int	*str;

	str = (signed int *)ft_memalloc(MAPSIZE_MAX * sizeof(signed int));
	if (str == NULL)
		error_exit("Str malloc failed (get_mapdata).");
	ft_bzero(buf, 2);
	i = 0;
	while (read(fd, buf, 1) == 1)
	{
		if (i >= MAPSIZE_MAX)
			error_exit("Map length exceeds MAPSIZE_MAX (get_mapdata)");
			//increase_mapsize(&str);
			
		if (ft_isdigit(*buf) || *buf == '-') {
			read_mapnode(fd, (char *)buf, &(str[i]), *buf == '-');
			map->z_extreme = ft_max(ft_abs(str[i]), map->z_extreme);
		}
			
		if (*buf == '\n' || *buf == '\t' || *buf == ' ')
			map->width += (i++, (map->width == 0 && *buf == '\n') * i);
		else
			error_exit("Invalid character (get_mapdata)");
		/*if (*buf == '\n' && map->width != 0 && i % map->width != 0)
			error_exit("Invalid map shape (get_mapdata)");*/
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

/*
TODO: Read both maps and allocate space for both points,
	that way free_map doesn't have to check it
*/

void	read_inputmap(char *filename, t_map *map)
{
	int				fd;
	int				cr[3];
	signed int		*data;

	fd = file_open(filename);
	ft_bzero(map, sizeof(t_map) * 2);
	data = get_mapdata(map, fd);
	ft_memcpy(&map[1], map, sizeof(t_map));
	map->points = ft_memalloc((map->length + 1) * sizeof(float *));	
	(&map[1])->points = ft_memalloc((map->length + 1) * sizeof(float *));
	if (map->points == NULL || (&(map[1]))->points == NULL)
		error_exit("Vector indexes malloc failed (read_inputmap)");
	ft_bzero(cr, sizeof(int) * 3);
	while (cr[Z] <= map->length)
	{
		if (cr[Z] != 0 && cr[Z] % map->width == 0)
			cr[X] = (cr[Y]++, 0);
		map->points[cr[Z]] = v3new(cr[X], cr[Y], (float)data[cr[Z]]);
		(&(map[1]))->points[cr[Z]] = v3new(cr[X], cr[Y], (float)data[cr[Z]]);
		if (map->points[cr[Z]] == NULL || (&(map[1]))->points[cr[Z]] == NULL)
			error_exit_free_map("Vector malloc failed in read_input", map);
		cr[Z] = (cr[X]++, cr[Z] + 1);
	}
	free(data);
}
