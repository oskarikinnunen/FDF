/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:29:26 by okinnune          #+#    #+#             */
/*   Updated: 2022/01/03 12:22:08 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*						FT_STRCHR										*/
/*	Locates the first occurence of 'character' in 'str'. If found,		*/
/*	returns a pointer to the first occurence of 'character' in 'str'	*/
/*	Added null protection for get_next_line								*/

char	*ft_strchr(const char *str, int character)
{
	while (*str != (char)character && *str != '\0')
		str++;
	if (*str == (char)character)
		return ((char *)str);
	return (NULL);
}
