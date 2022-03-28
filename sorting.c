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
	9x2bits+|9x2bits+|9x2bits+| 	10 bits		| = 64 bits
	x0 y0	|x1 y1	 |x2 y2	  |	tri z_color		|
*/
static void	face_to_tri64(float **v3, long *set_64, int width, int color)
{
	int			i;
	int			indx[2];

	i = 0;
	ft_bzero(indx, sizeof(int [2]));
	while (i < 3)
	{
		indx[0] = ((i >= 2) * width) + !((i + 1) % 2);
		indx[1] = ((i + 1 >= 2) * width) + !((i + 2) % 2);
		set_64[0] += ((long)v3[indx[0]][X] << (9 * i * 2))
					+ ((long)v3[indx[0]][Y] << (9 * i * 2) + 9);
		set_64[1] += ((long)v3[indx[1]][X] << (9 * i * 2))
					+ ((long)v3[indx[1]][Y] << (9 * i * 2) + 9);
		i++;
	}
	set_64[0] += ((long)color << 9 * 6);
	set_64[1] += ((long)color << 9 * 6);
}

static void	sort_face64s(long *tri_list, int *depth_list, int len)
{
	int		i;
	int		c;
	long	temp;

	i = 0;
	c = 0;
	while (i < len - 1)
	{
		while (c < len - 1 - i)
		{
			if ((depth_list[c] >> 16) > (depth_list[c + 1] >> 16))
			{
				temp = tri_list[c];
				tri_list[c] = tri_list[c + 1];
				tri_list[c + 1] = temp;
				temp = depth_list[c];
				depth_list[c] = depth_list[c + 1];
				depth_list[c + 1] = temp;
			}
			c++;
		}
		c = 0;
		i++;
	}
}

static void	print_face64_zvalues(long *tri_list, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("collected face v0 %li %li \n v1 %li %li \n v2 %li %li \n z0f %li \n ENDOFVECTOR \n",
			(tri_list[i])			& 0x1FF,
			(tri_list[i] >> 9)		& 0x1FF,
			(tri_list[i] >> 9 * 2)	& 0x1FF,
			(tri_list[i] >> 9 * 3)	& 0x1FF,
			(tri_list[i] >> 9 * 4)	& 0x1FF,
			(tri_list[i] >> 9 * 5)	& 0x1FF,
			((signed long)tri_list[i] >> 9 * 6));
		i++;
	}
}

/*
	tri[0][X] = list[i][X]
	tri[0][X] = list[i+1][X]
	tri[0][X] = list[i+1+w][X]
	tri[1][X] = list[i+w][X]
	tri[1][X] = list[i+1+w][X]
	tri[1][X] = list[i+2+w][X]
*/

long int	*sorted_tri64s(t_map *map, t_image_info *img)
{
	long	*tri_list;
	int		i;
	long	tri_i;

	i = 0;
	tri_i = 0;
	tri_list = ft_memalloc(map->tri_count * sizeof(long)); //TODO: PROTECT!
	depth_save(map, img, 1);
	while (i <= map->length - map->width - 1)
	{
		face_to_tri64(&(map->points[i]), &(tri_list[tri_i]), map->width,
			img->depthlayer[tri_i] & 0xFFFF);
		i += (i++, (i + 1) % map->width == 0);
		tri_i += 2;
	}
	sort_face64s(tri_list, img->depthlayer, map->tri_count);
	return (tri_list);
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
