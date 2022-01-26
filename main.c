/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/01/26 09:31:54 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fdf.h"
#include "libft/libft.h"
#define WSZ 800
//#include <mlx_int.h>

int	color(char r, char g, char b)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (i < 8)
	{
		c ^= (((1 << i & r) != 0)) << i + 16;
		c ^= (((1 << i & g) != 0)) << i + 8;
		c ^= (((1 << i & b) != 0)) << i;
		i++;
	}
	return (c);
}

void	v3set(int x, int y, int z, t_v3 *v)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

/*void	drawline(t_v3 p1, t_v3 p2, void *mlx, void *win)
{
	int x_y;

	if ((p1.x > p2.x) > (p1.y > p2.y))
	{

	}
	if (p1.x < p2.x)
}

void	bresenham_line(t_v3 p1, t_v3 p2, void *mlx, void *win)
{
	t_v3	cpy;
	int		d_x;
	int		d_y;
	int		d_total;
	int		add;

	printf("DRAWLINE CALL ");
	d_x = p2.x - p1.x;
	d_y = p2.y - p1.y;
	cpy.x = p1.x;
	cpy.y = p1.y;
	d_total = 2* (d_y - d_x);
	while (cpy.x < p2.x)
	{
		mlx_pixel_put(mlx, win, cpy.x, cpy.y, color(255,120,120));
		if (d_total > 0) {
			cpy.y++;
			d_total -= 2 * d_x;
		}
		d_total += 2 * d_y;
		cpy.x++;
		printf("X %i Y %i \n", cpy.x, cpy.y);
	}
}*/

void	drawline(t_v3 p1, t_v3 p2, void *mlx, void *win)
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
		mlx_pixel_put(mlx, win, p1.x, p1.y, color(255, 120, 120));
		if (p1.x == p2.x && p1.y == p2.y)
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

int	main(void)
{
	void	*mlx;
	void	*win;
	t_v3	p1;
	t_v3	p2;
	t_v3	p3;
	t_v3	angle;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WSZ, WSZ, "new_window");
	v3set(0, 30, 0, &p1);
	v3set(100, 40, 0, &p2);
	v3set(50, 300, 0, &p3);
	v3set(10, 45, 0, &angle);
	drawline(p1, p2, mlx, win);
	drawline(p2, p3, mlx, win);
	drawline(p3, p1, mlx, win);
	p1 = rotate_v3(p1, angle);
	p2 = rotate_v3(p2, angle);
	p3 = rotate_v3(p3, angle);
	printf("P1 X %i Y %i\n", p1.x, p1.y);
	drawline(p1, p2, mlx, win);
	drawline(p2, p3, mlx, win);
	drawline(p3, p1, mlx, win);
	while (1)
	{
		int c = getchar();
		if (ft_isdigit(c))
		{
			angle.y += c - '0';
		}
		p1 = rotate_v3(p1, angle);
		p2 = rotate_v3(p2, angle);
		p3 = rotate_v3(p3, angle);
		printf("P1 X %i Y %i\n", p1.x, p1.y);
		//drawline(p1, p2, mlx, win);
		//drawline(p2, p3, mlx, win);
		//drawline(p3, p1, mlx, win);
	}
		
	return (0);
}
