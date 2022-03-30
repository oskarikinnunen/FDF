/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:45:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/25 06:59:53 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	collect_tri_colors(float **v3, int *color_ptr, int width, int shift)
{
	int			i;
	int			indx[2];
	float		z;

	i = 0;
	z = shift * 10000.0;
	ft_bzero(indx, sizeof(int [2]));
	while (i < 3)
	{
		indx[0] = ((i >= 2) * width) + !((i + 1) % 2);
		indx[1] = ((i + 1 >= 2) * width) + !((i + 2) % 2);
		if (!shift)
			z += v3[indx[0]][Z] + v3[indx[1]][Z];
		else
			z = ft_min((int)z, ft_min(v3[indx[1]][Z], v3[indx[0]][Z]));
		i++;
	}
	if (!shift)
		z = (z / 6.0) + 127;
	color_ptr[0] += (int)z << (16 * shift);
	color_ptr[1] += (int)z << (16 * shift);
}

void	depth_save(t_map *map, t_image_info *img, int shift)
{
	int	i;
	int	tri_i;

	i = 0;
	tri_i = 0;
	while (i <= map->length - map->width - 1)
	{
		collect_tri_colors(&(map->points[i]), &(img->depthlayer[tri_i]),
			map->width, shift);
		i += (i++, (i + 1) % map->width == 0);
		tri_i += 2;
	}
}
