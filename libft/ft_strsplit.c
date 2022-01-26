/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:51:35 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/15 23:25:30 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char *s, char c)
{
	int	wc;
	int	lenc;

	wc = 0;
	lenc = 0;
	while (*s)
	{
		lenc = 0;
		while (*s == c)
			s++;
		while (s[lenc] != c && s[lenc])
			lenc++;
		s += lenc;
		if (lenc != 0)
			wc++;
	}
	return (wc);
}

static size_t	delimit_strlen(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s)
		len += (*(s++) != '\0');
	return (len);
}

char	**ft_strsplit(const char *s, char c)
{
	char	**arr;
	int		i;
	int		si;
	int		wc;

	wc = wordcount((char *)s, c);
	arr = (char **)malloc(sizeof(char *) * wc + 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		while (*s == c)
			s++;
		arr[i] = (char *)malloc(delimit_strlen(s, c) + 1);
		si = 0;
		while (*s != c && *s)
			arr[i][si++] = *(s++);
		arr[i][si] = '\0';
		i++;
	}
	arr[i] = 0;
	return (arr);
}
