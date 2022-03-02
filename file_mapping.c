/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:50:03 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/02 17:13:56 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned char *get_mapdata(t_map *map, int fd)
{
	int				res;
	int				cur;
	unsigned char	buf[2];
	unsigned char	*str;

	str = ft_strnew(1000);
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
			continue;
		}
		if (ft_isdigit(*buf) && res == 1)
		{
			printf("Adding left hand %i right hand %i\n", (int)(str[cur] * 10), (int)(*buf - '0'));
			str[cur] = (unsigned char)(str[cur] * 10) + (unsigned char)((*buf) - '0'); //TODO: overflow
		}
	}
	map->length = cur; //Fix with real indexing
	printf("map length %i \n", map->length);
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
		//printf("cur %i moduloresult = %i\n", cur, (cur + 1) % (map->width));
		if (cur != 0 && cur % map->width == 0)
		{
			crds[X] = 0;
			crds[Y]++;
		}
		map->points[cur] = v3new(crds[X], crds[Y], (float)data[cur]);
		printf("assigned vector %f %f %f \n", map->points[cur][X], map->points[cur][Y], map->points[cur][Z]);
		crds[X]++;
		cur++;
		/*(float **)((map->points) + cur) = 
		v3 = v3new(crds[X], crds[Y], (float)(*buf - '0'));
		crds[X]++;
		cur++;
		printf("CUR vlist content %f \n", ((float *)vlist->content)[X]);
		printf("CUR READINPUT %i \n", cur);*/
	}
}