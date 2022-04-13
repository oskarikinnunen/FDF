/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_nodereader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:02:27 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/14 02:39:39 by okinnune         ###   ########.fr       */
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
int	read_mapnode(int fd, char *buf, int *result, t_map *map)
{
	_Bool	negative_flag;
	int		i;

	negative_flag = (*buf == '-');
	i = 1;
	if (negative_flag)
		i = read(fd, buf, 1);
	if (i <= 0)
		error_exit("'-' at the end of file");
	while (i && ft_isdigit(*buf))
	{
		*result = (ft_isdigit(*buf)) * ((*result * 10) + (*buf - '0'));
		i = read(fd, buf, 1);
	}
	*result = *result * (1 - (negative_flag * 2));
	map->z_extreme = ft_max(ft_abs(*result), map->z_extreme);
	map->z_extreme = ft_max(map->z_extreme, 1); //TODO: test
	return (i);
}
