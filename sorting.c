/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:43:07 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/17 05:30:00 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	sort_tris(int tris[3][3])
{
	int	s_x;
	int	s_j;
	int	temp[3];

	s_x = 0;
	s_j = 0;
	while (s_x < 2)
	{
		while (s_j < 2 - s_x)
		{
			if (tris[s_j][Y] < tris[s_j + 1][Y])
			{
				ft_memcpy(temp, tris[s_j], sizeof(int) * 3);
				ft_memcpy(tris[s_j], tris[s_j + 1], sizeof(int) * 3);
				ft_memcpy(tris[s_j + 1], temp, sizeof(int) * 3);
			}
			s_j++;
		}
		s_j = 0;
		s_x++;
	}
}

void	sort_map_z(t_map *map)
{
	int		i;
	int		c;
	float	temp[3];

	i = 0;
	c = 0;
	while (i < map->length - 1)
	{
		while (c < map->length - 1 - i)
		{
			if (map->points[c][Z] < map->points[c + 1][Z])
			{
				ft_memcpy(temp, map->points[c], sizeof(float [3]));
				ft_memcpy(map->points[c], map->points[c + 1] \
										, sizeof(float [3]));
				ft_memcpy(map->points[c + 1], temp, sizeof(float [3]));
			}
			c++;
		}
		c = 0;
		i++;
	}
}
