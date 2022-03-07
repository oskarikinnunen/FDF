/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/07 21:31:27 by okinnune         ###   ########.fr       */
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

void	setmatrix_iso(float matrix[3][3])
{
	static float	iso[3][3] = {
	{1,	-0.6, 0},
	{0, 1, -0.2},
	{0, 0.0, 2.0}
	};
	int				i;

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
		draw_line_img(v3_integers[0], v3_integers[1], da, i_i, color_red());
		draw_line_img(v3_integers[0], v3_integers[2], da, i_i, color_red());
		if ((cur + 2) % map.width == 0)
			draw_line_img(v3_integers[1], v3_integers[3], da, i_i, color_green());
		if (cur > map.length - map.width * 2)
			draw_line_img(v3_integers[2], v3_integers[3], da, i_i, color_green());
		cur++;
		cur += ((cur + 1) % map.width == 0);
	}
}

void	preprocess(t_map *map)
{
	float	add[3];
	float	matrix[3][3];

	add[X] = 400;
	add[Y] = 400;
	add[Z] = 0;
	setmatrix_scale(matrix);
	v3listmul(matrix, map->points, map->length);
	setmatrix_iso(matrix);
	v3listmul(matrix, map->points, map->length);
	v3listadd(map->points, add, map->length);
}

t_map	preprocess_return(t_map *map)
{
	t_map	*l_map;
	int		i;
	float	add[3];
	float	matrix[3][3];

	i = 0;
	l_map = (t_map *)ft_memalloc(sizeof(t_map));
	ft_memcpy(l_map, map, sizeof(t_map));
	l_map->points = (float **)ft_memalloc((map->length + 1) * sizeof(float *));
	while (i <= map->length)
	{
		l_map->points[i] = v3new(map->points[i][X], map->points[i][Y], map->points[i][Z]);
		i++;
	}
	add[X] = 400;
	add[Y] = 400;
	add[Z] = 0;
	setmatrix_scale(matrix);
	v3listmul(matrix, l_map->points, map->length);
	setmatrix_iso(matrix);
	v3listmul(matrix, l_map->points, map->length);
	v3listadd(l_map->points, add, map->length);
	return (*l_map);
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
	/*ft_bzero(add[X], sizeof(float *) * 3);
	ft_bzero(add[Y], sizeof(float *) * 3);
	ft_bzero(add[Z], sizeof(float *) * 3);*/
	//printf("zinoid %f", sin(time / 1000));
	//add[X][Y] = 2 * sin(time / 1000);
	add[Z][Z] = 2 * sin(time / 1000);
	add[X][Z] = 0.02 * sin(time / 500);
	//add[2][Y] = 10 * sin(time / 1000);
	v3listmul(add, map->points, map->length);
	//v3listadd(map->points, add, map->length);
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

int	loop(void *p)
{
	t_mlx_i			*i;
	t_image_info	img;
	t_map			*cpy;
	char			*addr;

	i = (t_mlx_i *)p;
	img = *(i->img);
	cpy = mapcpy(i->map);
	//Transform points with matrix or some kind of function here, before clearing the picture and drawing again
	i->time = get_time(i->t1);
	//printf("SINOIDAL is %f\n", sin(i->time / 1000));
	addr = mlx_get_data_addr(img.ptr, &(img.bpp), &(img.size_line), &(img.endian));
	ft_bzero(addr, WSZ * WSZ * 4);
	
	transform(cpy, i->time);
	preprocess(cpy);
	
	drawpoints_image(addr, *cpy, img);
	mlx_put_image_to_window(i->mlx, i->win, i->img->ptr, 0, 50);


	return (1);
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
	
	img.bpp = 32;
	img.endian = 1;
	img.size_line = WSZ * img.bpp; //Times bpp??
	img.ptr = mlx_new_image(i.mlx, WSZ, WSZ);
	i.img = &img;
	i.map = &map;
	i.time = 0.0;
	gettimeofday(&(i.t1), NULL);
	//preprocess_return(&map);

	//mlx_put_image_to_window(i.mlx, i.win, img.ptr, 0,0);
	mlx_loop_hook(i.mlx, loop, &i);
	mlx_loop(i.mlx);
	return (0);
}
