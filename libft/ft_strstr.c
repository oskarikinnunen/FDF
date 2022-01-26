/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:00:08 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/03 00:43:01 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*					FT_STRSTR												*/
/*		Locates	substring 'needle' in 'haystack'. If found, returns the		*/
/*		pointer to the first occurence of 'needle' in 'haystack'			*/

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		ni;
	char	*match;

	i = 0;
	ni = 0;
	match = NULL;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] != '\0' && match == NULL)
	{
		if (haystack[i] == needle[0])
		{
			while (needle[ni] == haystack[i + ni] && needle[ni]
				&& haystack[i + ni])
				ni++;
			if (needle[ni] == '\0')
			{
				match = (char *)(haystack + i);
				break ;
			}
		}
		i++;
	}
	return (match);
}
