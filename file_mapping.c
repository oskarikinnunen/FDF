/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:50:03 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/19 21:51:06 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_errors.h"

static signed char	*get_mapdata(t_map *map, int fd)
{
	int			cur;
	signed char	buf[2];
	signed char	*str;

	str = (signed char *)ft_memalloc(1024);
	if (str == NULL)
		error_exit("Str malloc failed (get_mapdata).");
	ft_bzero(buf, 2);
	cur = 0;
	while (read(fd, buf, 1) == 1)
	{
		if (*buf == '\n' || *buf == '\t')
			map->width += (cur++, (map->width == 0 && *buf == '\n') * cur);
		else if (ft_isdigit(*buf))
			str[cur] = (signed char)(str[cur] * 10)
				+ (signed char)((*buf) - '0');
		else
			error_exit("Invalid character (get_mapdata)");
	}
	map->length = cur;
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
	int				crds[2];
	signed char		*data;
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
}
