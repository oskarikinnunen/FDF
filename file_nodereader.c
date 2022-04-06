/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_nodereader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:02:27 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/06 17:22:07 by okinnune         ###   ########.fr       */
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
void	read_mapnode(int fd, char *buf, int *result, int negative_flag)
{
	if (negative_flag)
		(void)!read(fd, buf, 1);
	while (ft_isdigit(*buf))
	{
		*result = (ft_isdigit(*buf)) * ((*result * 10) + (*buf - '0'));
		if (read(fd, buf, 1) <= 0)
			break ;
	}
	*result = *result * (1 - (negative_flag * 2));
}
