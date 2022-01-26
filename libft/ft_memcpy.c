/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:42:33 by okinnune          #+#    #+#             */
/*   Updated: 2022/01/05 15:15:41 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*								FT_MEMCPY									*/
/*			Copies 'n' bytes from memory area 'src' to memory area 'dst'	*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*cpy;

	cpy = dst;
	if (dst == src || n == 0)
		return (cpy);
	while (n > sizeof(long))
	{
		*(long *) cpy = *(const long *) src;
		n -= ((cpy += sizeof(long)) != 0) * sizeof(long);
		src += sizeof(long);
	}
	while (n >= sizeof(int))
	{
		*(int *) cpy = *(const int *) src;
		n -= ((cpy += sizeof(int)) != 0) * sizeof(int);
		src += sizeof(int);
	}
	while (n-- > 0)
		*(char *) cpy++ = *(const char *) src++;
	return (dst);
}
