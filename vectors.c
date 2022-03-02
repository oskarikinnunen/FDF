/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:47:59 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/02 16:18:45 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	*v3new(float x, float y, float z)
{
	float	*v3;

	v3 = (float *)malloc(sizeof(float) * 3);
	v3[X] = x;
	v3[Y] = y;
	v3[Z] = z;
	return (v3);
}

int		*v3_int(float	*v3)
{
	int	*i3;

	i3 = (int *)malloc(sizeof(int) * 3);
	i3[X] = (int)v3[X];
	i3[Y] = (int)v3[Y];
	i3[Z] = (int)v3[Z];
	return (i3);
}

/*int		i3_equal(int *i1, int *i2)
{
	return (i1[X])
}*/

/*TODO: make an "for all" function for vectors, applies something to all dimensions */
void	v3add(float *v3, float *add)
{
	v3[X] += add[X];
	v3[Y] += add[Y];
	v3[Z] += add[Z];
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

void	v3listmul(float matrix[3][3], float **v3s, int len)
{
	while (len >= 0)
	{
		v3mul(matrix, v3s[len]);
		len--;
	}
}

void	v3listadd(float **v3s, float *add, int len)
{
	while (len >= 0)
	{
		v3add(v3s[len], add);
		len--;
	}
}