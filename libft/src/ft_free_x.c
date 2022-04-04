/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:15:35 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/04 17:02:08 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_x(void **p, size_t size, size_t count)
{
	while (count >= 0)
	{
		free(*p);
		p += size;
		count--;
	}
	free(p);
}
