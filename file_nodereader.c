/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_nodereader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:02:27 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/24 04:05:47 by okinnune         ###   ########.fr       */
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
		read(fd, buf, 1);
	while (ft_isdigit(*buf)) //Aint working
	{
		*result = (ft_isdigit(*buf)) * ((*result * 10) + (*buf - '0'));
		if (read(fd, buf, 1) <= 0)
			break ;
	}
	*result = *result * (1 - (negative_flag * 2));
}
