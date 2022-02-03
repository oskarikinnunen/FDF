/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:23:59 by okinnune          #+#    #+#             */
/*   Updated: 2021/12/15 15:44:14 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*							FT_STRFILL						*/
/*		Sets all characters of string 's' to character 'c'	*/

void	ft_strfill(char *s, char c)
{
	while (*s)
		*s++ = c;
}
