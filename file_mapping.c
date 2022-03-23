/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:50:03 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/23 06:24:31 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_errors.h"

static signed int	*get_mapdata(t_map *map, int fd)
{
	int			i;
	unsigned char	buf[2];
	signed int	*str;

	str = (signed int *)ft_memalloc(MAPSIZE_MAX);
	if (str == NULL)
		error_exit("Str malloc failed (get_mapdata).");
	ft_bzero(buf, 2);
	i = 0;
	map->length = 0;
	map->width = 0;
	while (read(fd, buf, 1) == 1)
	{
		if (i >= MAPSIZE_MAX)
			error_exit("Map length exceeds MAPSIZE_MAX (get_mapdata)");
		if (ft_isdigit(*buf) || *buf == '-')
			read_mapnode(fd, (char *)buf, &(str[i]), *buf == '-');
		//if (*buf == '\n' && map->width != 0 && i % map->width != 0)
		//	error_exit("Invalid map shape (get_mapdata)");
		if (*buf == '\n' || *buf == '\t' || *buf == ' ')
			map->width += (i++, (map->width == 0 && *buf == '\n') * i);
		else
			error_exit("Invalid character (get_mapdata)");
		
	}
	map->length = i;
	printf("map length %i \n", map->length);
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

void	read_inputmap(char *filename, t_map	*map)
{
	int				fd;
	int				cr[3];
	signed int		*data;

	fd = file_open(filename);
	//ft_bzero(map, sizeof(t_map) * 2);
	//map->width = 0;
	//map = ft_memalloc(sizeof(t_map));
	data = get_mapdata(map, fd);
	//(&(map[1]))->length = map->length;
	//(&(map[1]))->width = map->width;
	
	
	//map->length = 2500;
	printf("map->length %i \n", map->length);
	printf("malloc size %li \n", (map->length + 1) * sizeof(float *));
	//map->points = ft_memalloc(21008);
	map->points = ft_memalloc((map->length + 1) * sizeof(float *));
	exit(0);
	//map->points = ft_memalloc(100000);
	//map->points = ft_memalloc((map->length + 1) * sizeof(float *));
	//(&(map[1]))->points = ft_memalloc((map->length + 1) * sizeof(float *));
	if (map->points == NULL || (&(map[1]))->points == NULL)
		error_exit("Vector indexes malloc failed (read_inputmap)");
	ft_bzero(cr, sizeof(int) * 3);
	printf("map width is %i \n", map->width);
	/*while (cr[Z] <= map->length)
	{
		if (cr[Z] != 0 && cr[Z] % map->width == 0)
			cr[X] = (cr[Y]++, 0);
		printf("going thru %i %i \n", cr[X], cr[Y]);
		map->points[cr[Z]] = v3new(cr[X], cr[Y], (float)data[cr[Z]]);
		(&(map[1]))->points[cr[Z]] = v3new(cr[X], cr[Y], (float)data[cr[Z]]);
		if (map->points[cr[Z]] == NULL || (&(map[1]))->points[cr[Z]] == NULL)
			error_exit_free_map("Vector malloc failed in read_input", map);
		cr[Z] = (cr[X]++, cr[Z] + 1);
	}*/
	exit(0);
	free(data);
}

/*void	read_inputmap(char *filename, t_map *map)
{
	int				fd;
	int				crds[2];
	unsigned char		*data;
	int				cur;

	fd = file_open(filename);
	ft_bzero(map, sizeof(t_map));
	data = get_mapdata(map, fd);
	map->points = ft_memalloc((map->length + 1) * sizeof(float *));
	if (map->points == NULL)
		error_exit("Vector indexes malloc failed (read_inputmap)");
	ft_bzero(crds, sizeof(int) * 2);
	cur = 0;
	while (cur <= map->length)
	{
		if (cur != 0 && cur % map->width == 0)
			crds[X] = (crds[Y]++, 0);
		map->points[cur] = v3new(crds[X], crds[Y], (float)data[cur]);
		if (map->points[cur] == NULL)
			error_exit_free_map("Vector malloc failed in read_input",
				map);
		crds[X]++;
		cur++;
	}
	free(data);
}*/
