/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:11:16 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/24 04:40:42 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(const char *s)
{
	size_t	len;

	len = ft_strlen((char *)s);
	if (len > 0)
		(void)!write(1, s, len);
	ft_putchar('\n');
}
