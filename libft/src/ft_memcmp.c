/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:09:24 by okinnune          #+#    #+#             */
/*   Updated: 2021/11/25 15:45:30 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t	i;

	i = 0;
	if (num == 0)
		return (0);
	while (((unsigned char *)ptr1)[i] == ((unsigned char *)ptr2)[i]
			&& i < num - 1)
		i++;
	return (((unsigned char *)ptr1)[i] - ((unsigned char *)ptr2)[i]);
}
