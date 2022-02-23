/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:47:59 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/23 05:09:55 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	*v3new(float x, float y, float z)
{
	float	*vf3;

	vf3 = (float *)malloc(sizeof(float) * 3);
	vf3[0] = x;
	vf3[1] = y;
	vf3[2] = z;
	return (vf3);
}

void	v3mul(float matrix[3][3], float *v3)
{
	float	t[3];
	int		index;

	index = X;
	while (index <= Z)
	{
		t[index] =
			(v3[X] * matrix[index][0])
			+ (v3[Y] * matrix[index][1])
			+ (v3[Z] * matrix[index][2]);
		index++;
	}
	v3[X] = t[X];
	v3[Y] = t[Y];
	v3[Z] = t[Z];
}

void	v3mul_list(float matrix[3][3], t_v3list *lst)
{
	int	i;

	i = 0;
	while (i < lst->length)
	{
		v3mul(matrix, &(lst->list[i]));
		i++;
	}
}

void	v3addx_list(int x, t_v3list *lst)
{
		int	i;

	i = 0;
	while (i <= lst->length)
	{
		lst->list[i].x += x;
		i++;
	}
}

void	v3addy_list(int y, t_v3list *lst)
{
		int	i;

	i = 0;
	while (i <= lst->length)
	{
		lst->list[i].y += y;
		i++;
	}
}