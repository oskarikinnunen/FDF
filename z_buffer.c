/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:45:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/18 21:07:39 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	save_z(t_map *map, t_image_info *img)
{
	int	i;

	i = 0;
	while (i <= map->length)
	{
		//((char *)&(img->z_values[i]))[index] = (char)(map->points[i][Z]);
		img->z_values[i] = (char)(map->points[i][Z]);
		i++;
	}
}

/*void	save_z_depth(t_map *map, t_image_info *img, int index)
{
	int	i;

	i = 0;
	while (i <= map->length)
	{
		((char *)&(img->z_values[i]))[index] = (char)(map->points[i][Z]);
		i++;
	}
}*/