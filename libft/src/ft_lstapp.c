/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:38:53 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/08 18:41:43 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*							FT_LSTAPP 									*/
/*	Appends t_list 'new' to the end of the list pointed by alst.		*/

void	ft_lstapp(t_list **alst, t_list *new)
{
	t_list	*orig;

	orig = *alst;
	while ((*alst)->next != NULL)
	{
		*alst = (*alst)->next;
	}
	new->next = NULL;
	(*alst)->next = new;
	(*alst) = orig;
}
