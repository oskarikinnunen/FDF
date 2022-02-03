/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:42:27 by okinnune          #+#    #+#             */
/*   Updated: 2022/01/05 17:55:21 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if ((dst == NULL && src == NULL) || dst == src || len == 0)
		return (dst);
	if (src < dst && dst < len + src)
		while (len-- > 0)
			((char *)dst)[len] = ((const char *)src)[len];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
