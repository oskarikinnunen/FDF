/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/10 02:03:51 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fdf.h"
#include "libft/libft.h"
//#include <mlx_int.h>

void	setmatrix_scale(float matrix[3][3])
{
	static float	scale[3][3] = {
	{22, 0, 0},
	{0, 22, 0},
	{0, 0, 3}
	};
	int				i;

	i = 0;
	while (i < 3)
	{
		ft_memcpy(&(matrix[i]), &(scale[i]), sizeof(float) * 3);
		i++;
	}
}

void	setmatrix_iso(float matrix[3][3], double angle)
{
	/*static float	iso[3][3] = {
	{1,	-0.6, -0.4},
	{0, 1, -0.2},
	{0.4, 0.0, 2.0}
	};*/
	float	v1 = sqrt(3);
	static float	iso[3][3] = {
	{1, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
	};
	int				i;
	//iso[Y][Y] = cos()
	
	angle = angle * 3.14 / 180;
	angle = asin(tan(angle));
	iso[Y][Y] = cos(angle);
	iso[Y][Z] = sin(angle);
	iso[Z][Y] = -sin(angle);
	iso[Z][Z] = cos(angle);
	//iso[Y][Z] = a;
	i = 0;
	while (i < 3)
	{
		ft_memcpy(&(matrix[i]), &(iso[i]), sizeof(float) * 3);
		i++;
	}
}

void	setmatrix_iso2(float matrix[3][3], double angle)
{
	/*static float	iso[3][3] = {
	{1,	-0.6, -0.4},
	{0, 1, -0.2},
	{0.4, 0.0, 2.0}
	};*/
	float	v1 = sqrt(3);
	static float	iso[3][3] = {
	{0, 0, 0},
	{0, 1, 0},
	{0, 0, 0}
	};
	int				i;
	//iso[Y][Y] = cos()
	//double angle = 45;
	angle = angle * 3.14 / 180;
	iso[X][X] = cos(angle);
	iso[X][Z] = -sin(angle);
	iso[Z][X] = sin(angle);
	iso[Z][Z] = cos(angle);
	//iso[Y][Z] = a;
	i = 0;
	while (i < 3)
	{
		ft_memcpy(&(matrix[i]), &(iso[i]), sizeof(float) * 3);
		i++;
	}
}

int color_green()
{
	static int	cached_green;

	if (cached_green == 0)
		cached_green = color(0,250,0);
	return(cached_green);
}

int color_red()
{
	static int	cached_red;

	if (cached_red == 0)
		cached_red = color(250,0,0);
	return(cached_red);
}

void	drawpoints_image(char *da, t_map map, t_image_info i_i)
{
	int		cur;
	int		v3_integers[4][3];
	int		i;

	cur = 0;
	while ((cur + map.width + 1) <= map.length)
	{
		i = 0;
		while (i < 4)
		{
			v3_int_block(map.points
						[cur + ((i >= 2) * map.width) + !((i + 1) % 2)],
						v3_integers[i]);
			i++;
		}
		//printf("drawing point X%i Y%i \n", v3_integers[0][0], v3_integers[0][1]);
		//fill_tri(v3_integers, da, i_i);
		draw_line_img(v3_integers[0], v3_integers[1], da, i_i, color_red());
		draw_line_img(v3_integers[0], v3_integers[2], da, i_i, color_red());
		if ((cur + 2) % map.width == 0)
			draw_line_img(v3_integers[1], v3_integers[3], da, i_i, color_green());
		if (cur > map.length - map.width * 2)
			draw_line_img(v3_integers[2], v3_integers[3], da, i_i, color_green());
		int pos[2];
		pos [X] = (v3_integers[0][X] + v3_integers[1][X] + v3_integers[2][X] + v3_integers[3][X]) / 4;
		pos [Y] = (v3_integers[0][Y] + v3_integers[1][Y] + v3_integers[2][Y] + v3_integers[3][Y]) / 4;
		flood_fill(pos, da, i_i, color_red);
		
		cur++;
		cur += ((cur + 1) % map.width == 0);
	}
}

void	preprocess(t_map *map, t_mlx_i i)
{
	float	add[3];
	float	matrix[3][3];

	add[X] = 400;
	add[Y] = 400;
	add[Z] = 0;
	setmatrix_scale(matrix);
	v3listmul(matrix, map->points, map->length);
	setmatrix_iso2(matrix, i.x_angle);
	v3listmul(matrix, map->points, map->length);
	setmatrix_iso(matrix, i.y_angle);
	v3listmul(matrix, map->points, map->length);
	v3listadd(map->points, add, map->length);
}

t_map	*mapcpy(t_map *map)
{
	t_map	*l_map;
	int		i;

	i = 0;
	l_map = (t_map *)ft_memalloc(sizeof(t_map));
	l_map->length = map->length;
	l_map->width = map->width;
	l_map->points = (float **)ft_memalloc((map->length + 1) * sizeof(float *));
	while (i <= map->length)
	{
		l_map->points[i] = v3new(map->points[i][X], map->points[i][Y], map->points[i][Z]);
		i++;
	}
	return (l_map);
}

void	transform(t_map *map, double time)
{
	static float	add[3][3] = {
	{1,	0, 0},
	{0, 1, 0},
	{0, 0, 1}
	};
	
	//add[Z][Z] = 1 * sin(time / 1000);
	
	v3listmul(add, map->points, map->length);
}

double	get_time(struct timeval t1)
{
	struct timeval	t2;
	double			time;

	gettimeofday(&t2, NULL);
	time = (t2.tv_sec - t1.tv_sec) * 1000.0
	+ (t2.tv_usec - t1.tv_usec) / 1000.0;
	return (time);
}

int	debug_points_zvalues(t_map map, t_mlx_i i)
{
	int	c;

	c = 0;
	while (c < map.length)
	{
		int *i3 = v3_int(map.points[c]);
		mlx_string_put(i.mlx, i.win, i3[X], i3[Y], INT_MAX, ft_itoa(i3[Z])); //Memory!!
		free(i3);
		c++;
	}
}

int	loop(void *p)
{
	t_mlx_i			*i;
	t_image_info	img;
	t_map			*cpy;
	char			*addr;

	i = (t_mlx_i *)p;
	img = *(i->img);
	
	//Transform points with matrix or some kind of function here, before clearing the picture and drawing again
	i->time = get_time(i->t1);
	//printf("SINOIDAL is %f\n", sin(i->time / 1000));
	addr = mlx_get_data_addr(img.ptr, &(img.bpp), &(img.size_line), &(img.endian));
	ft_bzero(addr, WSZ * WSZ * 4);

	cpy = mapcpy(i->map);
	transform(cpy, i->time);
	preprocess(cpy, *i);
	drawpoints_image(addr, *cpy, img);

	//MOVE TO DRAW!
	
	//debug_points_zvalues(*cpy, *i);
	mlx_put_image_to_window(i->mlx, i->win, i->img->ptr, 0, 50);
	//mlx_string_put(i->mlx, i->win, WSZ / 2, WSZ / 2, INT_MAX, "HEllo");


	return (1);
}

int	mouse_loop(int button, int x, int y, void *p)
{
	t_mlx_i			*i;

	i = (t_mlx_i *)p;
	//	i->x_axis;
	if (button == 1)
	{
		//printf("X axis = %i", x);
		//i->x_angle += 5;
		i->x_angle += 5 * (x < WSZ / 2) + -5 * (x > WSZ / 2);
	}
}

int	key_loop(int keycode, void *p)
{
	t_mlx_i			*i;

	i = (t_mlx_i *)p;
	
	i->x_angle += (keycode == KEY_LEFT) * -5;
	i->x_angle += (keycode == KEY_RGHT) * 5;
	i->y_angle += (keycode == KEY_DOWN) * -5;
	i->y_angle += (keycode == KEY_UP) * 5;
}

//TODO: animate!!
int	main(int argc, char **argv)
{
	t_mlx_i			i;
	t_image_info	img;
	t_map			map;
	float			matrix[3][3];

	if (argc != 2)
		return (-1);
	i.mlx = mlx_init();
	i.win = mlx_new_window(i.mlx, WSZ, WSZ, "new_window");
	ft_bzero(&map, sizeof(t_map));
	read_inputmap(argv[1], &map);
	//preprocess(&map); // Move this elsewhere!
	img.ptr = mlx_new_image(i.mlx, WSZ, WSZ);
	i.img = &img;
	i.map = &map;
	i.time = 0.0;
	i.x_angle = 45;
	i.y_angle = 30;
	gettimeofday(&(i.t1), NULL);
	//preprocess_return(&map);

	//mlx_put_image_to_window(i.mlx, i.win, img.ptr, 0,0);
	mlx_loop_hook(i.mlx, loop, &i);
	mlx_mouse_hook(i.win, mouse_loop, &i);
	//mlx_expose_hook(i.win, expose_loop, &i);
	mlx_key_hook(i.win, key_loop, &i);
	mlx_loop(i.mlx);
	return (0);
}
