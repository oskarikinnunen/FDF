/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:23:38 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/20 17:20:58 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_inside_image(int tri_int[3][3])
{
	int	tri;

	tri = 0;
	while (tri < 3)
	{
		if (tri_int[tri][X] >= WSZ - 1 || tri_int[tri][Y] >= WSZ - IMAGE_Y - 1
			|| tri_int[tri][X] < 0 || tri_int[tri][Y] < 0)
			return (0);
		tri++;
	}
	return (1);
}

static void	collect_v3_int(int tri_int[3][3], float **tri)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		tri_int[i][X] = (int)(tri[i][X]);
		tri_int[i][Y] = (int)(tri[i][Y]);
		tri_int[i][Z] = (int)(tri[i][Z]);
		i++;
	}
}

int	get_pixel_color(int z)
{
	int	r;
	int	g;
	int	b;
	int	range;
	int	color;

	range = 100;
	r = ft_max(0, range - ft_abs(z - 0));
	g = ft_max(0, range - ft_abs(z - 127));
	b = ft_max(0, range - ft_abs(z - 255));
	color = b + (g << 8) + (r << 16);
	return (color);
}

void	draw_from_z_buff(t_image_info img)
{
	int				i;
	unsigned int	faceheight;

	i = 0;
	while (i < (WSZ * (WSZ - IMAGE_Y)))
	{
		faceheight = (unsigned int)(img.z_buffer[i] & 0xFFFF);
		if (faceheight > 0)
		{
			*(unsigned int *)(img.addr + (i * sizeof(int)))
				= get_pixel_color(faceheight);
		}
		i++;
	}
}

void	z_pass(t_tri_map map, t_image_info img, _Bool wireframe)
{
	int				i;
	int				tri_int[3][3];

	ft_bzero(img.addr, (WSZ * (WSZ - IMAGE_Y)) * sizeof(int));
	ft_bzero(img.z_buffer, (WSZ * (WSZ - IMAGE_Y)) * sizeof(int));
	i = 0;
	while (i < map.tri_count)
	{
		collect_v3_int(tri_int, map.tri_list[i]);
		tri_int[0][Z] = img.depthlayer[i];
		tri_int[1][Z] = img.depthlayer[i];
		tri_int[2][Z] = img.depthlayer[i];
		if (is_inside_image(tri_int))
		{
			if (!wireframe)
				z_fill_tri(tri_int, img);
			z_draw_line(tri_int[0], tri_int[1], img);
			z_draw_line(tri_int[1], tri_int[2], img);
			z_draw_line(tri_int[0], tri_int[2], img);
		}
		i++;
	}
}
