/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:19:42 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/19 20:32:41 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_maps(t_map *maps)
{
	int	i;

	i = 0;
	while (i <= maps->length)
	{
		free((&(maps[0]))->points[i]);
		if (maps + (sizeof (t_map)) != NULL)
			free((&(maps[1]))->points[i]);
		i++;
	}
	free(maps->points);
}
