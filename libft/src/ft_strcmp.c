/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:40:35 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/13 15:32:10 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*						FT_STRCMP										*/
/*	Compares 's1' to 's2'. In case of difference between the strings,	*/
/*	returns difference of the first different characters in the strings	*/

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
