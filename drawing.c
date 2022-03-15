/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:38:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/15 08:28:02 by okinnune         ###   ########.fr       */
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

void	draw_rect_img(int *i1, int *i2, char *adder, t_image_info i)
{
	int	topright[2];
	int	botmleft[2];

	topright[X] = i2[X];
	topright[Y] = i1[Y];
	botmleft[X] = i2[Y];
	botmleft[Y] = i1[X];
	draw_line_img(i1, topright, adder, i, INT_MAX);
	draw_line_img(i1, botmleft, adder, i, INT_MAX);
	draw_line_img(i2, topright, adder, i, INT_MAX);
	draw_line_img(i2, botmleft, adder, i, INT_MAX);
}

void	sort_tris(int tris[3][3])
{
	int	s_x;
	int	s_j;
	int	temp[3];

	s_x = 0;
	s_j = 0;
	while (s_x < 2)
	{
		while (s_j < 2 - s_x)
		{
			printf("comparing %i and %i\n", tris[s_j][Y], tris[s_j + 1][Y]);
			if (tris[s_j][Y] < tris[s_j + 1][Y])
			{
				printf("doing swap! \n");
				ft_memcpy(temp, tris[s_j], sizeof(int) * 3);
				ft_memcpy(tris[s_j], tris[s_j + 1], sizeof(int) * 3);
				ft_memcpy(tris[s_j + 1], temp, sizeof(int) * 3);
			}
			s_j++;
		}
		s_j = 0;
		s_x++;
	}
	int i = 0;
	while (i < 3)
	{
		printf("Sorted mby %i \n", tris[i][Y]);
		i++;
	}
	printf("\n");
		
}

void	pop_brasenham(t_brasenham *b, int *from, int *to)
{
	ft_memcpy(b->local, from, sizeof(int) * 2);
	b->diff[X] = ft_abs(b->local[X] - to[X]);
	b->diff[Y] = -ft_abs(b->local[Y] - to[Y]);
	b->add[X] = 1 - ((b->local[X] > to[X]) * 2);
	b->add[Y] = 1 - ((b->local[Y] > to[Y]) * 2);
	b->error = b->diff[X] + b->diff[Y];
}

void	fill_bottom_tri(int *top, int *bot1, int *bot2, char *adder, t_image_info i)
{
	int			sort[2][2];
	t_brasenham	b[2];
	//float		xs[2];
	int			scan;

	ft_memcpy(sort[0], bot2, sizeof(int) * 2);
	ft_memcpy(sort[1], bot1, sizeof(int) * 2);
	if (bot1[X] < bot2[X])
	{
		ft_memcpy(sort[1], bot2, sizeof(int) * 2);
		ft_memcpy(sort[0], bot1, sizeof(int) * 2);
	}
	pop_brasenham(&(b[0]), top, sort[0]);
	pop_brasenham(&(b[1]), top, sort[1]);
	while (b[0].local[Y] != bot2[Y])
	{
		draw_line_img(b[0].local, b[1].local, adder, i, INT_MAX);
		int try = 0;
		while (b[0].local[Y] == b[1].local[Y]) 
		{
			if (b[0].error * 2 >= b[0].diff[Y] && b[0].local[X] != sort[0][X])
			{
				b[0].error += b[0].diff[Y];
				b[0].local[X] += b[0].add[X];
			}
			if (b[0].error * 2 <= b[0].diff[X] && b[0].local[Y] != sort[0][Y])
			{
				b[0].error += b[0].diff[X];
				b[0].local[Y] += b[0].add[Y];
			}
			//printf("local while x%i y%i add X%i Y%i\n", b[0].local[X],  b[0].local[Y], b[0].add[Y], b[0].add[Y]);
			/*try++;
			if (try > 40)
				exit(0);*/
			//printf("error 0 \n", b[0].error);
		}
		while (b[1].local[Y] != b[0].local[Y])
		{
			if (b[1].error * 2 >= b[1].diff[Y] && b[1].local[X] != sort[1][X])
			{
				b[1].error += b[1].diff[Y];
				b[1].local[X] += b[1].add[X];
			}
			if (b[1].error * 2 <= b[1].diff[X] && b[1].local[Y] != sort[1][Y])
			{
				b[1].error += b[1].diff[X];
				b[1].local[Y] += b[1].add[Y];
			}
		}
	}
}

void	fill_top_tri(int *bot, int *top1, int *top2, char *adder, t_image_info i)
{
	int			sort[2][2];
	t_brasenham	b[2];

	ft_memcpy(sort[0], top2, sizeof(int) * 2);
	ft_memcpy(sort[1], top1, sizeof(int) * 2);
	if (top1[X] < top2[X])
	{
		ft_memcpy(sort[1], top2, sizeof(int) * 2);
		ft_memcpy(sort[0], top1, sizeof(int) * 2);
	}
	pop_brasenham(&(b[0]), bot, sort[0]);
	pop_brasenham(&(b[1]), bot, sort[1]);
	while (b[0].local[Y] != top2[Y])
	{
		draw_line_img(b[0].local, b[1].local, adder, i, INT_MAX);
		while (b[0].local[Y] == b[1].local[Y]) 
		{
			if (b[0].error * 2 >= b[0].diff[Y] && b[0].local[X] != sort[0][X])
			{
				b[0].error += b[0].diff[Y];
				b[0].local[X] += b[0].add[X];
			}
			if (b[0].error * 2 <= b[0].diff[X] && b[0].local[Y] != sort[0][Y])
			{
				b[0].error += b[0].diff[X];
				b[0].local[Y] += b[0].add[Y];
			}
		}
		while (b[1].local[Y] != b[0].local[Y])
		{
			if (b[1].error * 2 >= b[1].diff[Y] && b[1].local[X] != sort[1][X])
			{
				b[1].error += b[1].diff[Y];
				b[1].local[X] += b[1].add[X];
			}
			if (b[1].error * 2 <= b[1].diff[X] && b[1].local[Y] != sort[1][Y])
			{
				b[1].error += b[1].diff[X];
				b[1].local[Y] += b[1].add[Y];
			}
		}
	}
}

void	fill_tri(int tris[3][3], char *adder, t_image_info i)
{
	int		split[3];
	int		sorted[3][3];
	float	lerp;

	ft_memcpy(sorted, tris, sizeof(int[3][3]));
	sort_tris(sorted);
	/*for (int x = 0; x < 3; x++)
	{
		printf("TRIS %i X%i Y%i Z%i\n", x, tris[x][X], tris[x][Y], tris[x][Z]);
	}*/
	//if ()
	lerp = (float)(sorted[1][Y] - sorted[2][Y]) / (float)(sorted[0][Y] - sorted[2][Y]);
	printf("0 %i 1 %i 2 %i lerp is %f \n", sorted[0][Y], sorted[1][Y], sorted[2][Y], lerp);
	split[X] = sorted[2][X] + (lerp * (sorted[0][X] - sorted[2][X]));
	split[Y] = sorted[2][Y] + (lerp * (sorted[0][Y] - sorted[2][Y]));
	split[Z] = 0;

	fill_bottom_tri(sorted[0], sorted[1], split, adder, i);
	fill_top_tri(sorted[2], sorted[1], split, adder, i);
	draw_line_img(sorted[0], sorted[1], adder, i, color_green());
	//draw_line_img(sorted[0], split, adder, i, INT_MAX);
	//draw_line_img(sorted[1], split, adder, i, INT_MAX);

	//exit(0);
}

void	flood_fill(int pos[2], char *adder, t_image_info i, int borderclr)
{
	//printf("pos X%i Y%i\n", pos[X], pos[Y]);
	/*if (*(int *)(adder + (pos[X] * (i.bpp / 8)) + (i.size_line * pos[Y])) == borderclr)
		printf("FOUND RED \n");*/
	if (*(int *)(adder + (pos[X] * (i.bpp / 8)) + (i.size_line * pos[Y])) != borderclr
	&& *(int *)(adder + (pos[X] * (i.bpp / 8)) + (i.size_line * pos[Y])) != INT_MAX)
	{
		*(int *)(adder + (pos[X] * (i.bpp / 8)) + (i.size_line * pos[Y])) = INT_MAX;
		if (pos[Y] > 1000 || pos[X] > 1000)
			return ;
		flood_fill((int [2]){pos[X], pos[Y] + 1}, adder, i, borderclr);
		flood_fill((int [2]){pos[X], pos[Y] - 1}, adder, i, borderclr);
		flood_fill((int [2]){pos[X] - 1, pos[Y]}, adder, i, borderclr);
		flood_fill((int [2]){pos[X] + 1, pos[Y]}, adder, i, borderclr);
	}
	
	//flood_fill((int [2]){pos[X] - 1, pos[Y]}, adder, i, borderclr);
	//flood_fill((int [2]){pos[X], pos[Y] + 1}, adder, i, borderclr);
	//flood_fill((int [2]){pos[X], pos[Y] - 1}, adder, i, borderclr);
	//printf("floodfill! \n");
}


void	draw_line_img(int *i1, int *i2, char *adder, t_image_info i, int clr)
{
	t_brasenham	b;

	ft_memcpy(b.local, i1, sizeof(int) * 3);
	b.diff[X] = ft_abs(b.local[X] - i2[X]);
	b.diff[Y] = -ft_abs(b.local[Y] - i2[Y]);
	b.add[X] = 1 - ((b.local[X] > i2[X]) * 2);
	b.add[Y] = 1 - ((b.local[Y] > i2[Y]) * 2);
	b.error = b.diff[X] + b.diff[Y];
	while ((b.local[X] != i2[X] || b.local[Y] != i2[Y]))
	{
		*(int *)(adder + (b.local[X] * (i.bpp / 8)) + (i.size_line * b.local[Y])) = clr; //Have no idea why this needs to be hardcoded 4 instead of i.bpp...
		//Linememory.add(local);
		if (b.error * 2 >= b.diff[Y] && b.local[X] != i2[X])
		{
			b.error += b.diff[Y];
			b.local[X] += b.add[X];
		}
		if (b.error * 2 <= b.diff[X] && b.local[Y] != i2[Y])
		{
			b.error += b.diff[X];
			b.local[Y] += b.add[Y];
		}
	}
}

void	draw_line(int *i1, int *i2, t_mlx_i i, int c)
{
	int		diff[3];
	int		add[3];
	int		local[3];
	int		error;

	ft_memcpy(local, i1, sizeof(int) * 3);
	diff[X] = ft_abs(local[X] - i2[X]);
	diff[Y] = -ft_abs(local[Y] - i2[Y]);
	add[X] = 1 - ((local[X] > i2[X]) * 2);
	add[Y] = 1 - ((local[Y] > i2[Y]) * 2);
	error = diff[X] + diff[Y];
	printf("Initial error %i \n", error);
	while ((local[X] != i2[X] || local[Y] != i2[Y]))
	{
		mlx_pixel_put(i.mlx, i.win, local[X], local[Y], c);
		printf("error step %i \n", error);
		if (error * 2 >= diff[Y] && local[X] != i2[X])
		{
			error += diff[Y];
			local[X] += add[X];
		}
		if (error * 2 <= diff[X] && local[Y] != i2[Y])
		{
			error += diff[X];
			local[Y] += add[Y];
		}
	}
	exit(0);
}
