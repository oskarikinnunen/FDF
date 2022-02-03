/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:47:59 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/03 12:57:48 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	v3mul(float matrix[3][3], t_v3 *v)
{
	float x;
	float y;
	float z;

	x = (v->x * matrix[0][0]) + (v->y * matrix[0][1]) + (v->z * matrix[0][2]);
	y = (v->x * matrix[1][0]) + (v->y * matrix[1][1]) + (v->z * matrix[1][2]);
	z = (v->x * matrix[2][0]) + (v->y * matrix[2][1]) + (v->z * matrix[2][2]);

	v->x = x;
	v->y = y;
	v->z = z;
}

t_v3	rotate_v3(t_v3 in, t_v3 angle)
{
	t_v3	new;
	int		x;
	int		y;

	//x = in.x;
	//y = in.y;
	x = in.x * (int)cos(angle.x) + in.y * (int)sin(angle.x);
	y = in.x * -(int)sin(angle.x) + in.y * (int)cos(angle.x);

	y = y * (int)cos(angle.y) - in.z * (int)sin(angle.y);
	
	new.x = x;
	new.y = y;
	//new.x += WSZ * 0.5;
	//new.y += WSZ * 0.5;
	return (new);
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