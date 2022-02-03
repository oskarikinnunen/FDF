/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:01:23 by okinnune          #+#    #+#             */
/*   Updated: 2021/11/12 13:38:39 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = (char *)malloc(len + 1);
	if (res != NULL)
	{
		i = 0;
		while (i < len)
		{
			while (*s1)
				res[i++] = *(s1++);
			while (*s2)
				res[i++] = *(s2++);
		}
		res[i] = '\0';
	}
	return (res);
}
