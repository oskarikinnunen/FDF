/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:45:14 by okinnune          #+#    #+#             */
/*   Updated: 2021/11/25 17:46:52 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		dc;

	if (n < 0)
		ft_putchar_fd('-', fd);
	dc = ft_digitcount(n);
	while (dc-- > 0)
		ft_putchar_fd(ft_abs((n / ft_pow(10, dc)) % 10)
			+ '0', fd);
}
