/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:45:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/24 15:42:36 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	save_z(t_map *map, t_image_info *img)
{
	int	i;

	i = 0;
	while (i <= map->length)
	{
		img->depthlayer[i] = 0;
		img->depthlayer[i] = map->points[i][Z] + 127;
		//img->depthlayer[i] += (-1024 << 8);
		//printf("saved depthlayer %i && %i \n", img->depthlayer[i] & Z_CLRMASK, img->depthlayer[i] >> 8);
		i++;
	}
	/*while (i <= WSZ * WSZ)
	{
		img->depthlayer[i] = 0;
		img->depthlayer[i] += (-1024 << 8);
		i++;
	}*/
}

int		calc_face_color(int *depthlayer, int index, int width)
{
	int	color;

	color = 0;
	color += (depthlayer[index] & Z_CLRMASK);
	printf("READ FACE Z CLR value %i index %i\n", color, index);
	color += (depthlayer[index + 1] & Z_CLRMASK);
	printf("ADD  FACE Z CLR value %i index %i\n", color, index + 1);
	color += (depthlayer[index + width] & Z_CLRMASK);
	printf("ADD2 FACE Z CLR value %i index %i\n", color, index + 1 + width);
	color += (depthlayer[index + width + 1] & Z_CLRMASK);
	color = ft_clamp((color / 4) * Z_CLRMUL, 0, 255);
	printf("calculated face color %i\n", color);
	return (color);
}
