/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:43:07 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/25 14:56:11 by okinnune         ###   ########.fr       */
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

/*
tri64
	18 bits	|18 bits |18 bits | 	10 bits		   |
	x0 y0	|x1 y1	 |x2 y2	  |	collective z_depth |
*/
static void	face_to_tri64(float **v3, long *set_64, int width)
{
	int			i;
	int			indx[2];
	float		z;

	i = 0;
	z = 0.0;
	ft_bzero(indx, sizeof(int [2]));
	while (i < 3)
	{
		indx[0] = ((i >= 2) * width) + !((i + 1) % 2);
		indx[1] = ((i + 1 >= 2) * width) + !((i + 2) % 2);
		set_64[0] += ((long)v3[indx[0]][X] << (9 * i * 2))
					+ ((long)v3[indx[0]][Y] << (9 * i * 2) + 9);
		set_64[1] += ((long)v3[indx[1]][X] << (9 * i * 2))
					+ ((long)v3[indx[1]][Y] << (9 * i * 2) + 9);
		z += v3[indx[1]][Z] + v3[indx[0]][Z];
		i++;
	}
	z = z / 6.0;
	set_64[0] += ((long)z << 9 * 6);
	set_64[1] += ((long)z << 9 * 6);
}

static void	sort_face64s(long *list, int len)
{
	int		i;
	int		c;
	long	temp[2];

	i = 0;
	c = 0;
	while (i < len - 1)
	{
		while (c < len - 1 - i)
		{
			if ((signed long)list[c] >> 54 > (signed long)list[c + 2] >> 54)
			{
				ft_memcpy(temp, &(list[c]), sizeof(long) * 2);
				ft_memcpy(&(list[c]), &(list[c + 2]), sizeof(long) * 2);
				ft_memcpy(&(list[c + 2]), temp, sizeof(long) * 2);
			}
			c += 2;
		}
		c = 0;
		i++;
	}
}

static void	print_face64_zvalues(long *tri_list, int len)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		printf("collected face x0 %li y0 %li x1 %li y1 %li z0f %li z1f %li \n",
			(tri_list[i])			& 0x1FF,
			(tri_list[i] >> 9)		& 0x1FF,
			(tri_list[i] >> 9 * 2)	& 0x1FF,
			(tri_list[i] >> 9 * 3)	& 0x1FF,
			((signed long)tri_list[i] >> 9 * 6),
			((signed long)tri_list[i + 1] >> 9 * 6));
		i++;
	}
}

long int	*face64b_list(t_map *map)
{
	long	*tri_list;
	int		i;
	long	tri_i;

	i = 0;
	tri_i = 0;
	tri_list = ft_memalloc(map->length * 2 * sizeof(long)); //TODO: PROTECT!
	while (i < map->length - map->width - 1)
	{
		face_to_tri64(&(map->points[i]), &(tri_list[tri_i]), map->width);
		i += (i++, (i + 1) % map->width == 0);
		tri_i += 2;
	}
	sort_face64s(tri_list, (map->length * 2) - (map->width * 3));
	//print_face64_zvalues(tri_list, (map->length * 2) - (map->width * 3));
	return (tri_list);
}

void	sort_map_faces_z(t_map *map)
{
	face64b_list(map);
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
