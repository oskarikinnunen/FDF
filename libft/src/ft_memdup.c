/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:35:15 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/22 09:37:49 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memdup(const void *m, size_t n)
{
	void	*result;
	size_t	i;

	i = 0;
	result = (char *)malloc(n);
	if (result != NULL)
	{
		while (i < n)
		{
			((unsigned char *)result)[i] = ((unsigned char *)m)[i];
			i++;
		}
	}
	return (result);
}
