/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:45:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/22 10:28:50 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	save_z(t_map *map, t_image_info *img)
{
	int	i;

	i = 0;
	while (i <= map->length)
	{
		img->depthlayer[i] = (unsigned char)(map->points[i][Z] + 127);
		i++;
	}
}
