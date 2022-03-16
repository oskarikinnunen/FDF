/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/16 16:23:04 by okinnune         ###   ########.fr       */
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

void	setmatrix_iso_x(float matrix[3][3], double angle)
{
	float	v1 = sqrt(3);
	static float	iso[3][3] = {
	{1, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
	};
	int				i;
	
	angle = angle * 3.14 / 180;
	angle = asin(tan(angle));
	iso[Y][Y] = cos(angle);
	iso[Y][Z] = sin(angle);
	iso[Z][Y] = -sin(angle);
	iso[Z][Z] = cos(angle);
	i = 0;
	while (i < 3)
	{
		ft_memcpy(&(matrix[i]), &(iso[i]), sizeof(float) * 3);
		i++;
	}
}

void	setmatrix_iso_y(float matrix[3][3], double angle)
{
	static float	iso[3][3] = {
	{0, 0, 0},
	{0, 1, 0},
	{0, 0, 0}
	};
	int				i;

	angle = angle * 3.14 / 180;
	iso[X][X] = cos(angle);
	iso[X][Z] = -sin(angle);
	iso[Z][X] = sin(angle);
	iso[Z][Z] = cos(angle);
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
	int		vert_z;

	cur = 0;
	while ((cur + map.width + 1) <= map.length)
	{
		vert_z = i_i.z_values[cur] + i_i.z_values[cur + 1]
				+ i_i.z_values[cur + map.width]
				+ i_i.z_values[cur + map.width + 1];
		vert_z = vert_z / 4;
		vert_z = ft_clamp(vert_z * 2, -127, 127) + 127;
		collect_square(&(map.points[cur]), v3_integers, map.width, vert_z);
		fill_tri(v3_integers, vert_z,  da, i_i);
		fill_tri(&(v3_integers[1]), vert_z, da, i_i);
		draw_line_img(v3_integers[0], v3_integers[1], da, i_i);
		draw_line_img(v3_integers[1], v3_integers[2], da, i_i);
		draw_line_img(v3_integers[0], v3_integers[2], da, i_i);
		cur++;
		cur += ((cur + 1) % map.width == 0);
	}
}

void	preprocess(t_map *map, t_mlx_i i)
{
	float	add[3];
	float	matrix[3][3];

	add[X] = WSZ / 4;
	add[Y] = WSZ / 4;
	add[Z] = 20;
	setmatrix_scale(matrix);
	v3listmul(matrix, map->points, map->length);
	setmatrix_iso_y(matrix, i.x_angle);
	v3listmul(matrix, map->points, map->length);
	setmatrix_iso_x(matrix, i.y_angle);
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

void	mapcpy_shallow(t_map *src, t_map *dst)
{
	int	i;

	i = 0;
	while (i <= src->length)
	{
		ft_memcpy(dst->points[i], src->points[i], sizeof(float) * 3);
		i++;
	}
}

void	transform(t_map *map, double time)
{
	static float	add[3][3] = {
	{1,	0, 0},
	{0, 1, 0},
	{0, 0, 1}
	};
	
	add[Z][Z] = 1 * sin(time / 1000);
	
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

void	sort_map_z(t_map *map)
{
	int		i;
	int		c;
	float	temp[3];

	i = 0;
	c = 0;
	while (i < map->length - 1)
	{
		while (c < map->length - 1 - i)
		{
			if (map->points[c][Z] < map->points[c + 1][Z])
			{
				ft_memcpy(temp, map->points[c], sizeof(float[3]));
				ft_memcpy(map->points[c], map->points[c + 1], sizeof(float[3]));
				ft_memcpy(map->points[c + 1], temp, sizeof(float[3]));
			}
			c++;
		}
		c = 0;
		i++;
	}
}

int	loop(void *p)
{
	t_mlx_i			*i;
	t_image_info	img;
	t_map			cpy;
	char			*addr;

	i = (t_mlx_i *)p;
	img = *(i->img);
	i->time = get_time(i->t1);
	//mlx_clear_window(i->mlx, i->win);
	/*char *fps = ft_itoa(1000 / (i->time - i->p_time));
	mlx_string_put(i->mlx, i->win, 10, 10, color_red(), fps);
	free(fps);*/
	i->p_time = i->time;
	addr = mlx_get_data_addr(img.ptr, &(img.bpp), &(img.size_line), &(img.endian));
	ft_bzero(addr, WSZ * WSZ * 4);
	cpy = i->maps[1];
	mapcpy_shallow(i->maps, &cpy);
	
	transform(&cpy, i->time);
	save_z(&cpy, &img, 0);
	preprocess(&cpy, *i);
	//save_z(&cpy, &img, 1);
	//save_z(&cpy, &img, 1);
	//debug_points_zvalues(*cpy, *i);
	//sort_map_z(cpy);
	drawpoints_image(addr, cpy, img);
	//free_map(cpy);
	//free(cpy);

	

	//MOVE TO DRAW!
	mlx_put_image_to_window(i->mlx, i->win, i->img->ptr, 0, 20);
	//exit(0);
	
	return (1);
}

int	mouse_loop(int button, int x, int y, void *p)
{
	t_mlx_i			*i;

	i = (t_mlx_i *)p;
	if (button == 1)
		i->x_angle += 5 * (x < WSZ / 2) + -5 * (x > WSZ / 2);
}

int	key_loop(int keycode, void *p)
{
	t_mlx_i			*i;

	i = (t_mlx_i *)p;
	
	i->x_angle += (keycode == KEY_LEFT) * -5;
	i->x_angle += (keycode == KEY_RGHT) * 5;
	i->y_angle += (keycode == KEY_DOWN) * -5;
	i->y_angle += (keycode == KEY_UP) * 5;
	printf("Pressed button %i \n", keycode);

	if (keycode == KEY_ESC || keycode == 65307)
	{
		free_map(&(i->maps[1]));
		free_map(i->maps);
		exit(0);
	}
}


int	main(int argc, char **argv)
{
	t_mlx_i			i;
	t_image_info	img;
	t_map			maps[2];
	float			matrix[3][3];

	if (argc != 2)
		return (-1);
	i.mlx = mlx_init();
	i.win = mlx_new_window(i.mlx, WSZ, WSZ, "new_window");
	ft_bzero(maps, sizeof(t_map) * 2);
	ft_bzero(&img, sizeof(t_image_info));
	read_inputmap(argv[1], &(maps[0]));
	read_inputmap(argv[1], &(maps[1]));
	img.ptr = mlx_new_image(i.mlx, WSZ, WSZ);
	
	i.img = &img;
	i.maps = (t_map *)(&maps);
	img.z_values = malloc(sizeof(int) * i.maps->length);
	i.time = 0.0;
	i.x_angle = 45;
	i.y_angle = 30;
	gettimeofday(&(i.t1), NULL);
	mlx_loop_hook(i.mlx, loop, &i);
	mlx_mouse_hook(i.win, mouse_loop, &i);
	mlx_key_hook(i.win, key_loop, &i);
	mlx_loop(i.mlx);
	return (0);
}
