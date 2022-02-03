/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:42:33 by okinnune          #+#    #+#             */
/*   Updated: 2021/11/26 15:42:22 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	size_t	occurence;
	char	*chrres;

	i = 0;
	chrres = (char *)ft_memchr((void *)src, c, n);
	if (chrres != NULL)
		occurence = chrres - (char *) src;
	else
		occurence = n;
	while (i < n && i < occurence + 1)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	if (chrres != NULL)
		return (dst + i);
	else
		return (NULL);
}
