/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:37:01 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/15 15:34:12 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*							FT_STRNEW										*/
/*	Returns a new string with size 'size'. All characters are set to '\0'.	*/

char	*ft_strnew(size_t size)
{
	char	*res;

	res = (char *)malloc(size + 1);
	if (res != NULL)
		ft_bzero(res, size + 1);
	return (res);
}
