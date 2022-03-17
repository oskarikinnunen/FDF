/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:50:03 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/17 15:34:09 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned char	*get_mapdata(t_map *map, int fd)
{
	int				res;
	int				cur;
	unsigned char	buf[2];
	unsigned char	*str;

	str = (unsigned char *)ft_memalloc(1000);
	ft_bzero(buf, 2);
	cur = 0;
	res = 1;
	while (res == 1)
	{
		res = read(fd, buf, 1);
		if (*buf == '\n' || *buf == '\t')
		{
			if (*buf == '\n' && map->width == 0)
				map->width = cur + 1;
			cur++;
			continue ;
		}
		if (ft_isdigit(*buf) && res == 1)
			str[cur] = (unsigned char)(str[cur] * 10)
				+ (unsigned char)((*buf) - '0');
	}
	map->length = cur;
	return (str);
}

void	read_inputmap(char *filename, t_map *map)
{
	int				fd;
	int				crds[2];
	unsigned char	*data;
	int				cur;

	fd = open(filename, O_RDONLY);
	data = get_mapdata(map, fd);
	ft_bzero(crds, sizeof(int) * 2);
	cur = 0;
	map->points = ft_memalloc((map->length + 1) * sizeof(float *));
	printf("MAP WIDTH IS %i\n", map->width);
	while (cur <= map->length)
	{
		if (cur != 0 && cur % map->width == 0)
		{
			crds[X] = 0;
			crds[Y]++;
		}
		map->points[cur] = v3new(crds[X], crds[Y], (float)data[cur]);
		crds[X]++;
		cur++;
	}
	free(data);
}
