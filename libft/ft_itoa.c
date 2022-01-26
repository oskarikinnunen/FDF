/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:56:19 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/15 15:46:13 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*								FT_ITOA										*/
/*				Returns a string representation of the integer n			*/
/*																			*/
/* 						LINE50: neg + len - (i - neg) - 1					*/
/*		This is an 'inverted index' to access the array in reverse order	*/

char	*ft_itoa(int n)
{
	int		len;
	char	*res;
	int		i;
	int		neg;

	neg = n < 0;
	len = ft_digitcount(n);
	res = (char *)malloc(neg + len + 1);
	if (res == NULL)
		return (res);
	i = 0;
	if (neg)
		res[i++] = '-';
	while (i < neg + len)
	{
		res[neg + len - (i - neg) - 1] = ft_abs(n % 10) + '0';
		n = n / 10;
		i++;
	}
	res[i] = '\0';
	return (res);
}
