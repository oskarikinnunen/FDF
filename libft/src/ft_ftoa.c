/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:53:37 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/07 14:35:12 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ftoa(float f, int dec)
{
	char	*final;
	char	*strinteger;
	char	*strdecimal;
	int		i;

	i = (int)f;
	f = f - i;
	f = f * (ft_pow(10, dec));
	strinteger = ft_itoa(i);
	strdecimal = ft_itoa(ft_abs((int)f));
	final = ft_strnew(ft_strlen(strinteger) + ft_strlen(strdecimal) + 1);
	ft_strcat(final, strinteger);
	ft_strcat(final, ",");
	ft_strcat(final, strdecimal);
	free(strinteger);
	free(strdecimal);
	return (final);
}