/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_nodereader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:02:27 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/06 19:09:57 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_errors.h"

/*static int	is_legal_char(char c)
{
	return (c == '-' || ft_isdigit(c));
}*/

/* TODO: check for double hyphens

	
*/

//void	nodereader(int fd, char *buf)

// make new read_mapnode, takes map, fd and cur read char(or '-' sign) as params
void	read_mapnode(int fd, char *buf, int *result, t_map *map)
{
	int	negative_flag;

	negative_flag = (*buf == '-');
	if (negative_flag)
		(void)!read(fd, buf, 1);
	while (ft_isdigit(*buf))
	{
		*result = (ft_isdigit(*buf)) * ((*result * 10) + (*buf - '0'));
		if (read(fd, buf, 1) <= 0)
			break ;
	}
	*result = *result * (1 - (negative_flag * 2));
	map->z_extreme = ft_max(ft_abs(*result), map->z_extreme);
}
