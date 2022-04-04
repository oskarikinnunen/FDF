/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:45:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/04 22:24:53 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	collect_tri_colors(float **v3, int *color_ptr, int shift)
{
	int			i;
	float		z;

	i = 0;
	z = shift * 10000.0;
	while (i < 3)
	{
		if (!shift)
			z += v3[i][Z];
		else
			z = ft_min((int)z, (int)(v3[i][Z]));
		/*if (!shift)
			z += v3[indx[0]][Z] + v3[indx[1]][Z];
		else
			z = ft_min((int)z, ft_min(v3[indx[1]][Z], v3[indx[0]][Z]));*/
		i++;
	}
	if (!shift)
	{
		z = (z / 3.0) + 127;
		//printf("og face color %f \n", z);
	}	
	*color_ptr += (int)z << (16 * shift);
}

void	apply_z_from_depth(t_tri_map *map, int *depthlayer)
{
	int	i;

	i = 0;
	while(i < map->tri_count)
	{
		map->tri_list[i][0][Z] = depthlayer[i] & 0xFFFF;
		map->tri_list[i][1][Z] = depthlayer[i] & 0xFFFF;
		map->tri_list[i][2][Z] = depthlayer[i] & 0xFFFF;
		i++;
	}
}

void	depth_save(t_tri_map *map, t_image_info *img, int shift)
{
	int	i;

	i = 0;
	while (i < map->tri_count)
	{
		collect_tri_colors(map->tri_list[i], &(img->depthlayer[i]), shift);
		/*collect_tri_colors(&(map->points[i]), &(img->depthlayer[tri_i]),
			map->width, shift);*/
		//i += (i++, (i + 1) % map->width == 0);
		i++;
		//tri_i += 2;
	}
}
