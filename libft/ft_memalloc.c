/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:11:34 by okinnune          #+#    #+#             */
/*   Updated: 2021/11/12 11:28:53 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*					FT_MEMALLOC							*/
/*	Allocates memory for size 'size' and initializes	*/
/*	all of the values in it to '0'.						*/

void	*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	i;

	mem = malloc(size);
	if (mem != NULL)
	{
		i = 0;
		while (i < size)
		{
			((unsigned char *)mem)[i] = '\0';
			i++;
		}
	}
	return (mem);
}
