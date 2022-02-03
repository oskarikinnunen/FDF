/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:15:35 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/08 16:29:55 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	iswhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/*						FT_STRTRIM										*/
/*	Returns a copy of 's' with the whitespace characters removed from	*/
/*	the beginning and end of the string.								*/

char	*ft_strtrim(const char *s)
{
	char	*res;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	while (iswhitespace(s[start]))
		start++;
	end = ft_strlen((char *)s) - 1;
	while (iswhitespace(s[end]) && end >= start)
		end--;
	if (end == start)
		return (NULL);
	res = (char *)malloc(end - start + 2);
	if (res == NULL)
		return (res);
	i = 0;
	while (i < (end - start + 1))
	{
		res[i] = s[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}
