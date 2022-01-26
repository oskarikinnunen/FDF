/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:04:49 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/15 18:05:34 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*res;
	size_t	i;

	res = (t_list *)malloc(sizeof(t_list));
	if (content == NULL && res != NULL)
	{
		res->content_size = 0;
		res->content = NULL;
		res->next = NULL;
	}
	else if (res != NULL)
	{
		res->content = malloc(content_size);
		if (res->content == NULL)
		{
			free (res);
			return (NULL);
		}
		i = 0;
		while (i++ < content_size)
			*(char *)(res->content + i - 1) = *(char *)(content + i - 1);
		res->content_size = content_size;
		res->next = NULL;
	}
	return (res);
}
