/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:04:48 by okinnune          #+#    #+#             */
/*   Updated: 2022/01/05 15:20:34 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	dlen;

	if (n == 0)
		return (s1);
	i = 0;
	dlen = 0;
	while (s1 [dlen] != '\0')
		dlen++;
	i = 0;
	while (i < n && s2[i])
	{
		s1[i + dlen] = s2[i];
		i++;
	}
	s1[i + dlen] = '\0';
	return (s1);
}
