/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:45:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/16 16:22:59 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	save_z(t_map *map, t_image_info *info, int index)
{
	int	i;

	i = 0;
	while (i <= map->length)
	{
		((char *)&(info->z_values[i]))[index] = (char)(map->points[i][Z]);
		//(info->z_values[i]) = map->points[i][Z];
		i++;
	}
}