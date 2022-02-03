/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:11:07 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/08 17:17:49 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	dstlen;
	size_t	i;

	dstlen = 0;
	i = 0;
	dstlen = ft_strlen(dst);
	if (siz == 0)
		return (ft_strlen((char *)src));
	while (dstlen + i < siz - 1 && src[i])
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	if (siz < dstlen)
		dstlen = siz;
	return (dstlen + ft_strlen((char *)src));
}
