/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:25:27 by okinnune          #+#    #+#             */
/*   Updated: 2021/11/26 13:46:16 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*						FT_POWER						*/
/*		Returns int 'n' raised to the power of 'p'		*/

int	ft_pow(int n, int p)
{
	int	cur_p;
	int	r;

	if (p == 0)
		return (1);
	cur_p = 1;
	r = n;
	while (cur_p < p)
	{
		r = r * n;
		cur_p++;
	}
	return (r);
}
