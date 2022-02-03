/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 14:52:38 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/13 15:32:50 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*								FT_ATOI										*/
/*				Returns an integer representation of the string str			*/

int	ft_atoi(const char *str)
{
	int				mul;
	long long int	res;

	res = 0;
	mul = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || (*str >= 11
			&& *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		mul += -(*(str++) == '-') * 2;
	while (*str == '0')
		str++;
	while (ft_isdigit(*str))
	{
		res = (res * 10) + (*str - '0');
		str++;
		if (res > 2147483648 - mul)
			return (-(res * mul > 2147483647));
	}
	return (res * mul);
}
