/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:29:26 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/13 15:47:06 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*						FT_STRRCHR										*/
/*	Locates the last occurence of 'character' in 'str'. If found,		*/
/*	returns a pointer to the last occurence of 'character' in 'str'		*/

char	*ft_strrchr(const char *str, int character)
{
	const char	*match;

	match = NULL;
	while (*str != '\0')
	{
		if (*str == (char)character)
			match = str;
		str++;
	}
	if (character == '\0' && *str == '\0')
		match = str;
	return ((char *)match);
}
