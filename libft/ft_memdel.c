/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:27:25 by okinnune          #+#    #+#             */
/*   Updated: 2021/11/12 13:49:00 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*							FT_MEMDEL							*/
/*			frees the memory of pointer ap and sets ap to NULL	*/

void	ft_memdel(void **ap)
{
	free(*ap);
	*ap = NULL;
}
