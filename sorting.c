/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:43:07 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/04 21:37:24 by okinnune         ###   ########.fr       */
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
static void	tri_to_tri64(float **v3, long *set_64, int color)
{
	int			i;

	i = 0;
	*set_64 = 0L;
	while (i < 3)
	{
		*set_64 += ((long)v3[i][X] << (9 * i * 2))
					+ ((long)v3[i][Y] << (9 * i * 2) + 9);
		/*set_64[1] += ((long)v3[indx[1]][X] << (9 * i * 2))
					+ ((long)v3[indx[1]][Y] << (9 * i * 2) + 9);*/
		i++;
	}
	*set_64 += ((long)color << 9 * 6);
	//set_64[1] += ((long)color << 9 * 6);
}

static void	swap_tris (float **tri1, float **tri2)
{
	int		i;
	float	tempv3[3];

	i = 0;
	while(i < 3)
	{
		ft_memcpy(tempv3, tri1[i], sizeof(float [3]));
		ft_memcpy(tri1[i], tri2[i], sizeof(float [3]));
		ft_memcpy(tri2[i], tempv3, sizeof(float [3]));
		i++;
	}
}

static void	sort_face64s(t_tri_map map, long *tri_list, int *depth_list, int len)
{
	int		i;
	int		c;
	long	temp;

	i = 0;
	while (i < len)
	{
		c = i;
		while (c > 0 && (depth_list[c - 1] >> 16) > (depth_list[c] >> 16))
		{
			//printf("depth list value masked %i \n", depth_list[c - 1] & 0xFFFF);
			temp = tri_list[c];
			tri_list[c] = tri_list[c - 1];
			tri_list[c - 1] = temp;
			temp = depth_list[c];
			depth_list[c] = depth_list[c - 1];
			depth_list[c - 1] = temp;
			swap_tris(map.tri_list[c], map.tri_list[c - 1]);
			//printf("swaps %i \n", swaps);
			c--;
		}
		i++;
	}
	//exit(0);
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
	//exit(0);
}

/*while (i <= map->length - map->width - 1)
	{
		face_to_tri64(&(map->points[i]), &(img->tri_64s[tri_i]), map->width,
			img->depthlayer[tri_i] & 0xFFFF);
		i += (i++, (i + 1) % map->width == 0);
		tri_i += 2;
	}
*/

void	sort_simple(t_tri_map map, int *depthlayer)
{
	int		i;
	int		c;
	int		swaps;
	int		temp;

	i = 0;
	swaps = 0;
	while (i < map.tri_count)
	{
		c = i;
		while (c > 0 && (depthlayer[c - 1] >> 16) > (depthlayer[c] >> 16))
		{
			swap_tris(map.tri_list[c], map.tri_list[c - 1]);
			temp = depthlayer[c];
			depthlayer[c] = depthlayer[c - 1];
			depthlayer[c - 1] = temp;
			swaps++;
			printf("swaps %i \n", swaps);
			//swap_tris(map->tri_list[c], map->tri_list[c - 1]);
			c--;
		}
		i++;
		//printf("swapping index %i \n", i);
	}
}

void	sorted_tri64s(t_tri_map *map, t_tri_map *orig, t_image_info *img)
{
	int		i;

	
	depth_save(map, img, 1);
	i = 0;
	while (i < map->tri_count)
	{
		tri_to_tri64(map->tri_list[i], &(img->tri_64s[i]), img->depthlayer[i] & 0xFFFF);
		i++;
	}
	sort_face64s(*orig, img->tri_64s, img->depthlayer, img->tri_count);
	//sort_simple(*map, img->depthlayer);
	
	/*while (i < map->tri_count)
	{
		map->tri_list[i][0][Z] = (float)(img->depthlayer[i] & 0xFFFF);
		map->tri_list[i][1][Z] = (float)(img->depthlayer[i] & 0xFFFF);
		map->tri_list[i][2][Z] = (float)(img->depthlayer[i] & 0xFFFF);
		i++;
	}*/
	//printf("sort end \n");
	//exit(0);
}
