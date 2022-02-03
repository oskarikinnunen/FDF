/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:40:19 by okinnune          #+#    #+#             */
/*   Updated: 2021/11/26 15:31:47 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	r;
	int	temp;

	r = 0;
	temp = 0;
	if (nb <= 0)
		return (0);
	while (temp < nb)
	{
		r++;
		temp = r * r;
	}
	if (temp == nb)
		return (r);
	else
		return (0);
}
