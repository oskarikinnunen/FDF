/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depthbuffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:45:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/06 18:21:08 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	face_depth(float **tri)
{
	int			i;
	int			z;

	i = 0;
	z = 10000;
	while (i < 3)
	{
		z = ft_min(z, (int)(tri[i][Z]));
		i++;
	}
	z += 1000.0;
	return (z);
}

static	int	face_color(float **tri)
{
	int	i;
	int	color;

	i = 0;
	color = 0;
	while (i < 3)
	{
		color += (int)tri[i][Z];
		i++;
	}
	color = (color / 3) + 127;
	return (color);
}

void	save_face_colors(t_tri_map map, t_image_info img)
{
	int	i;
	int	z;

	i = 0;
	while (i < map.tri_count)
	{
		z = (face_color(map.tri_list[i]) + face_color(map.tri_list[i + 1])) / 2;
		img.depthlayer[i] = z;
		img.depthlayer[i + 1] = z;
		i += 2;
	}
}

void	save_depths(t_tri_map map, t_image_info img)
{
	int	i;

	i = 0;
	while (i < map.tri_count)
	{
		img.depthlayer[i] += face_depth(map.tri_list[i]) << 16;
		i++;
	}
}
