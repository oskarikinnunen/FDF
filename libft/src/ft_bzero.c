/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:06:39 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/17 08:46:52 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	/*while (n > sizeof(long))
	{
		*(long *) s = (long)0;
		s += sizeof(long);
		n -= sizeof(long);
	}
	while (n > sizeof(int))
	{
		*(int *) s = 0;
		s += sizeof(int);
		n -= sizeof(int);
	}*/
	while (n-- > 0)
		*(char *)s++ = 0;
}
