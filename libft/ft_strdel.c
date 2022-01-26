/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:40:12 by okinnune          #+#    #+#             */
/*   Updated: 2021/11/26 15:27:30 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*									FT_STRDEL								*/
/*			frees the string's address 'as'  and sets the pointer to NULL	*/

void	ft_strdel(char **as)
{
	free(*as);
	*as = NULL;
}
