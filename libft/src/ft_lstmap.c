/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:51:09 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/16 19:28:53 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	delete(void *content, size_t size)
{
	if (size > 0)
		free(content);
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*temp;

	new = NULL;
	while (lst != NULL)
	{
		temp = f(lst);
		if (temp == NULL)
		{
			if (new != NULL)
				ft_lstdel(&new, delete);
			return (NULL);
		}
		if (new == NULL)
			new = temp;
		else
			ft_lstapp(&new, temp);
		lst = lst->next;
	}
	return (new);
}
