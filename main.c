/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/04 18:25:49 by okinnune         ###   ########.fr       */
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

void	drawpoints(t_mlx_i i, t_map map)
{
	int		cur;
	int		*v3_integers[4];

	cur = 0;
	printf("initial drawpoints\n");
	while ((cur + map.width + 1) <= map.length)
	{
		v3_integers[0] = v3_int(map.points[cur]);
		v3_integers[1] = v3_int(map.points[cur + 1]);
		v3_integers[2] = v3_int(map.points[cur + map.width]);
		v3_integers[3] = v3_int(map.points[cur + map.width + 1]);
		draw_line(v3_integers[0], v3_integers[1], i, INT_MAX);
		draw_line(v3_integers[0], v3_integers[2], i, INT_MAX);
		draw_line(v3_integers[3], v3_integers[1], i, INT_MAX);
		draw_line(v3_integers[3], v3_integers[2], i, INT_MAX);
		cur++;
		cur += ((cur + 1) % map.width == 0);
		free(v3_integers[0]);
		free(v3_integers[1]);
		free(v3_integers[2]);
		free(v3_integers[3]);
	}
}

		/*draw_line(v3_integers[0], v3_integers[1], i, INT_MAX);
		draw_line(v3_integers[0], v3_integers[2], i, INT_MAX);
		draw_line(v3_integers[3], v3_integers[1], i, INT_MAX);
		draw_line(v3_integers[3], v3_integers[2], i, INT_MAX);*/
		//make a draw_line_toimage!!

void	drawpoints_image(char *da, t_map map)
{
	int		cur;
	int		v3_integers[4][3];
	int		i;

	cur = 0;
	printf("initial drawpoints\n");
	while ((cur + map.width + 1) <= map.length)
	{
		i = 0;
		while (i < 4)
		{
			/*v3_integers[i] = v3_int(map.points
				[cur + (i >= 2 * map.width) + ((i + 1) % 2)]);*/
			v3_int_block(map.points
						[cur + ((i >= 2) * map.width) + !((i + 1) % 2)],
						v3_integers[i]);
			printf("int block addresses cur index %i \n", cur + ((i >= 2) * map.width) + !((i + 1) % 2));
			i++;
		}
		cur++;
		cur += ((cur + 1) % map.width == 0);
		printf("drawpoints while call\n");
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

char	*image_data_addr(void *mlx)
{
	void			*image;
	t_image_info	t;

	t.bpp = 16;
	t.size_line = WSZ;
	t.endian = 0;
	image = mlx_new_image(mlx, WSZ, WSZ);
	return (mlx_get_data_addr(image, &(t.bpp), &(t.size_line), &(t.endian)));
}

int	main(int argc, char **argv)
{
	t_mlx_i		i;
	t_map		map;
	float		matrix[3][3];

	if (argc != 2)
		return (-1);
	i.mlx = mlx_init();
	i.win = mlx_new_window(i.mlx, WSZ, WSZ, "new_window");
	ft_bzero(&map, sizeof(t_map));
	read_inputmap(argv[1], &map);
	preprocess(&map);
	drawpoints_image(image_data_addr(i.mlx), map);
	mlx_loop(i.mlx);
	return (0);
}
