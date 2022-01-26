/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:34:55 by okinnune          #+#    #+#             */
/*   Updated: 2021/11/23 12:31:09 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	**temp;

	temp = alst;
	while ((*alst) != NULL)
	{
		temp = alst;
		del((*temp)->content, (*temp)->content_size);
		free (*temp);
		*alst = (*alst)->next;
	}
}
