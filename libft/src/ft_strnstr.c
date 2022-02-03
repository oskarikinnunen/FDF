/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:00:08 by okinnune          #+#    #+#             */
/*   Updated: 2021/11/17 05:52:43 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*							FT_STRNSTR										*/
/*		Locates	substring 'needle' in 'haystack', but searches only up to	*/
/* 		'len' characters. If found, returns the	pointer to the first		*/
/*		occurence of 'needle' in 'haystack'.								*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	ni;
	char	*match;

	i = 0;
	ni = 0;
	match = NULL;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] != '\0' && match == NULL && i < len)
	{
		if (haystack[i] == needle[0])
		{
			while (needle[ni] == haystack[i + ni] && i + ni < len && needle[ni])
				ni++;
			if (needle[ni] == '\0')
				match = (char *)(haystack + i);
		}
		i++;
	}
	return (match);
}
