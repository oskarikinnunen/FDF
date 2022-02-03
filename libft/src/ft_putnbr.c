/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:13:51 by okinnune          #+#    #+#             */
/*   Updated: 2021/11/25 17:46:19 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int		dc;

	if (n < 0)
		ft_putchar('-');
	dc = ft_digitcount(n);
	while (dc-- > 0)
		ft_putchar(ft_abs((n / ft_pow(10, dc)) % 10)
			+ '0');
}
