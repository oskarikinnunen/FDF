/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strscrape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:51:35 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/21 12:58:48 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_any_delim(char c, char *delims)
{
	_Bool	result;

	result = 0;
	while (*delims)
	{
		if (c == *delims)
			result = 1;
		delims++;
	}
	return (result);
}

static int	wordcount(char *s, char *delims)
{
	int	wc;
	int	lenc;

	wc = 0;
	lenc = 0;
	while (*s)
	{
		lenc = 0;
		while (is_any_delim(*s, delims))
			s++;
		while (!is_any_delim(s[lenc], delims) && s[lenc])
			lenc++;
		s += lenc;
		if (lenc != 0)
			wc++;
	}
	return (wc);
}

static size_t	delimit_strlen(const char *s, char *delims)
{
	int	len;

	len = 0;
	while (!is_any_delim(*s, delims) && *s)
		len += (*(s++) != '\0');
	return (len);
}

char	**ft_strscrape(const char *s, char *delims)
{
	char	**arr;
	int		i;
	int		si;
	int		wc;

	wc = wordcount((char *)s, delims);
	arr = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		while (is_any_delim(*s, delims))
			s++;
		arr[i] = (char *)malloc(delimit_strlen(s, delims) + 1);
		si = 0;
		while (!is_any_delim(*s, delims) && *s)
			arr[i][si++] = *(s++);
		arr[i][si] = '\0';
		i++;
	}
	arr[i] = 0;
	return (arr);
}
