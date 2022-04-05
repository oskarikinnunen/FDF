/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:23:38 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/05 22:48:08 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*void	*draw_map(void *draw_args)
{
	t_draw_args		arg;
	int				i;
	int				v3_integers[4][3];
	unsigned int				z_color;

	arg = *(t_draw_args *)draw_args;
	i = arg.start;
	while ((i + arg.map.width + 1) <= arg.map.length && i < arg.stop)
	{
		z_color = (arg.img.depthlayer[i] & Z_CLRMASK)
			+ (arg.img.depthlayer[i + 1] & Z_CLRMASK)
			+ (arg.img.depthlayer[i + arg.map.width] & Z_CLRMASK)
			+ (arg.img.depthlayer[i + arg.map.width + 1] & Z_CLRMASK);
		z_color = ft_clamp((z_color / 4) * Z_CLRMUL, 0, 255);
		collect_square(&(arg.map.points[i]),
			v3_integers, arg.map.width, z_color);
		fill_tri(v3_integers, arg.img.addr, arg.img);
		fill_tri(&(v3_integers[1]), arg.img.addr, arg.img);
		draw_line_img(v3_integers[0], v3_integers[1], arg.img.addr, arg.img);
		draw_line_img(v3_integers[1], v3_integers[2], arg.img.addr, arg.img);
		draw_line_img(v3_integers[0], v3_integers[2], arg.img.addr, arg.img);
		i++;
		i += ((i + 1) % arg.map.width == 0);
	}
	return (NULL);
}*/

static int is_inside_image(int v3_int[3][3])
{
	int i[2];

	i[0] = 0;
	i[1] = 0;
	while (i[1] < 3)
	{
		if (i[0] == X && v3_int[i[1]][i[0]] > WSZ ||
			i[0] == Y && v3_int[i[1]][i[0]] > WSZ - IMAGE_Y ||
			v3_int[i[X]][i[Y]] < 0)
				return (0);
		i[0]++;
		if (i[0] > 2)
		{
			i[0] = 0;
			i[1]++;
		}
	}
	return (1);
}

static void	collect_v3_int(int v3int[3][3], float **tri)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		v3int[i][X] = (int)(tri[i][X]);
		v3int[i][Y] = (int)(tri[i][Y]);
		v3int[i][Z] = (int)(tri[i][Z]);
		i++;
	}
}

void	draw_img_from_trimap(t_tri_map map, t_image_info img)
{
	int				i;
	int				v3_int[3][3];
	unsigned int	z_color;

	i = 0;
	while (i < map.tri_count)
	{
		collect_v3_int(v3_int, map.tri_list[i]);
		v3_int[0][Z] = img.depthlayer[i];
		v3_int[1][Z] = img.depthlayer[i];
		v3_int[2][Z] = img.depthlayer[i];
		if (is_inside_image(v3_int))
		{
			draw_line_img(v3_int[0], v3_int[1], img);
			draw_line_img(v3_int[1], v3_int[2], img);
			draw_line_img(v3_int[0], v3_int[2], img);
			fill_tri(v3_int, img);
		}
		i++;
	}
}
