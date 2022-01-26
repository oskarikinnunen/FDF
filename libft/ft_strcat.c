/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:04:48 by okinnune          #+#    #+#             */
/*   Updated: 2022/01/05 17:30:35 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *destination, const char *source)
{
	int	i;
	int	dlen;

	i = 0;
	while (destination[i])
		i++;
	dlen = i;
	while (source[i - dlen])
	{
		destination[i] = source[i - dlen];
		i++;
	}
	destination[i] = '\0';
	return (destination);
}
