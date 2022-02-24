/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:38:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/24 06:03:58 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <assert.h>

int	color(char r, char g, char b)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (i < 8)
	{
		c ^= (((1 << i & r) != 0)) << (i + 16);
		c ^= (((1 << i & g) != 0)) << (i + 8);
		c ^= (((1 << i & b) != 0)) << i;
		i++;
	}
	return (c);
}

void	debug_matrix(float m[3][3], t_mlx_i i)
{
	int		x;
	int		y;
	char	*str;

	x = 0;
	y = 0;
	while (y < 3)
	{
		while (x < 3)
		{
			str = ft_ftoa(m[y][x], 2);
			mlx_string_put(i.mlx, i.win, 00 + ((x + 1) * DEBUG_MW), 25 + y * 10, INT_MAX, "[");
			mlx_string_put(i.mlx, i.win, 10 + ((x + 1) * DEBUG_MW), 25 + y * 10, INT_MAX, str);
			mlx_string_put(i.mlx, i.win, 50 + ((x + 1) * DEBUG_MW), 25 + y * 10, INT_MAX, "]");
			free(str);
			x++;
		}
		y++;
		x = 0;
	}
}

void	drawline(t_v3 p1, t_v3 p2, t_mlx_i i)
{
	t_v3	diff;
	t_v3	add;
	int		error;

	diff.x = ft_abs(p1.x - p2.x);
	diff.y = -ft_abs(p1.y - p2.y);
	add.x = 1 - ((p1.x > p2.x) * 2);
	add.y = 1 - ((p1.y > p2.y) * 2);
	error = diff.x + diff.y;
	while (1)
	{
		mlx_pixel_put(i.mlx, i.win, p1.x, p1.y, color(255, 120, 120));
		if ((int)p1.x == (int)p2.x && (int)p1.y == (int)p2.y)
			break ;
		if (error * 2 >= diff.y)
		{
			error += (p1.x != p2.x) * diff.y;
			p1.x += (p1.x != p2.x) * add.x;
		}
		if (error * 2 <= diff.x)
		{
			error += (p1.y != p2.y) * diff.x;
			p1.y += (p1.y != p2.y) * add.y;
		}
	}
}

//Points is always basically a t_v3[4]
/*
void	drawlinefill(t_v3 *points, t_mlx_i i, int c)
{
	float	xdiff;
	float	lerp;
	float	height;
	t_v3	origin;
	t_v3	target;

	//origin = points[0];
	origin.z = points[0].z;
	target.z = points[3].z;
	height = (points[0].z + points[1].z + points[2].z + points[3].z) / 4.0f;
	lerp = 0.0f;
	while (lerp <= 1.0f)
	{
		origin.x = (int)((points[0].x * (1 - lerp)) + (points[2].x * lerp));
		origin.y = (int)((points[0].y * (1 - lerp)) + (points[2].y * lerp));
		target.x = (int)((points[1].x * (1 - lerp)) + (points[3].x * lerp));
		target.y = (int)((points[1].y * (1 - lerp)) + (points[3].y * lerp));
		lerp += 0.01f;
		drawlinec(origin, target, i, color((char)((int)(height * 5)), 0, 0));
	}
	//if ()
	//drawstr(i, ft_ftoa(height, 2), points[0].x, points[0].y);
	//xdiff = p1.x - p2.x;
	//draw vertical line with xdiff
}*/

void	drawline_toimage(t_v3 p1, t_v3 p2, char *img, int c)
{
	t_v3	diff;
	t_v3	add;
	t_v3	local;
	int		error;

	//p1.x = max(0, p1.x);
	//p1.y = max(0, p1.y);
	local.x = (int)p1.x;
	local.y = (int)p1.y;
	local.z = (int)p1.z;
	diff.x = ft_abs(local.x - (int)p2.x);
	diff.y = -ft_abs(local.y - (int)p2.y);
	add.x = 1 - ((local.x > (int)p2.x) * 2);
	add.y = 1 - ((local.y > (int)p2.y) * 2);
	
	error = diff.x + diff.y;
	while (1)
	{
		if (local.x < WSZ && local.y * WSZ < WSZ / 2) //TODO: Remove *32 multiplier to draw something, it's not right tho...
			*(img + (int)local.x + (((int)local.y) * WSZ)) = INT_MAX;
		if (((int)local.x == (int)p2.x && (int)local.y == (int)p2.y))
			break ;
		if (error * 2 >= (int)diff.y)
		{
			error += (int)(((int)local.x != (int)p2.x) * (int)diff.y);
			local.x += (int)(((int)local.x != (int)p2.x) * add.x);
		}
		if (error * 2 <= (int)diff.x)
		{
			error += (int)(((int)local.y != (int)p2.y) * diff.x);
			local.y += (int)(((int)local.y != (int)p2.y) * add.y);
		}
	}
}

void	draw_line(int *i1, int *i2, t_mlx_i i, int c)
{
	int		diff[3];
	int		add[3];
	int		local[3];
	int		error;

	local[X] = i1[X];
	local[Y] = i1[Y];
	local[Z] = i1[Z]; //Memset, cpy, mikälie
	diff[X] = ft_abs(local[X] - i2[X]);
	diff[Y] = -ft_abs(local[Y] - i2[Y]);
	add[X] = 1 - ((local[X] > i2[X]) * 2);
	add[Y] = 1 - ((local[Y] > i2[Y]) * 2);
	printf("ADD  X: %i Y: %i\n", add[X], add[Y]);
	printf("DIFF X: %i Y: %i\n", diff[X], diff[Y]);
	
	error = diff[X] + diff[Y];
	while (1)
	{
		mlx_pixel_put(i.mlx, i.win, local[X], local[Y], c);
		//printf("drawpixel %f, %f. error %i addx %f addy %f diffx %f diffy %f\n", local.x, local.y, error, add.x, add.y, diff.x, diff.y);
		if (local[X] == i2[X] && local[Y] == i2[Y])
			break ;
		if (error * 2 >= diff[Y])
		{
			error += (local[X] != i2[X]) * diff[Y];
			local[X] += (local[X] != i2[X]) * add[X];
		}
		if (error * 2 <= diff[X])
		{
			error += (local[Y] != i2[Y]) * diff[X];
			local[Y] += (local[Y] != i2[Y]) * add[Y];
		}
	}
}

void	drawlinec(t_v3 p1, t_v3 p2, t_mlx_i i, int c)
{
	t_v3	diff;
	t_v3	add;
	t_v3	local;
	int		error;

	//p1.x = max(0, p1.x);
	//p1.y = max(0, p1.y);
	local.x = (int)p1.x;
	local.y = (int)p1.y;
	local.z = (int)p1.z;
	diff.x = ft_abs(local.x - (int)p2.x);
	diff.y = -ft_abs(local.y - (int)p2.y);
	add.x = 1 - ((local.x > (int)p2.x) * 2);
	add.y = 1 - ((local.y > (int)p2.y) * 2);
	
	error = diff.x + diff.y;
	while (1)
	{
		mlx_pixel_put(i.mlx, i.win, (int)local.x, (int)local.y, c);
		//printf("drawpixel %f, %f. error %i addx %f addy %f diffx %f diffy %f\n", local.x, local.y, error, add.x, add.y, diff.x, diff.y);
		if (((int)local.x == (int)p2.x && (int)local.y == (int)p2.y))
			break ;
		//if (local.x)
		//	break ;
		if (error * 2 >= (int)diff.y)
		{
			error += (int)(((int)local.x != (int)p2.x) * (int)diff.y);
			local.x += (int)(((int)local.x != (int)p2.x) * add.x);
		}
		if (error * 2 <= (int)diff.x)
		{
			error += (int)(((int)local.y != (int)p2.y) * diff.x);
			local.y += (int)(((int)local.y != (int)p2.y) * add.y);
		}
	}
}
