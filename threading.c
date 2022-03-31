/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:23:38 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/25 14:54:28 by okinnune         ###   ########.fr       */
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

static void	collect_tri64(int v3_int[3][3], long	tri64, float scaler)
{
	v3_int[0][X] = ((tri64 >> 0) & 0x1FF) * scaler;
	v3_int[0][Y] = ((tri64 >> 9) & 0x1FF) * scaler;
	v3_int[1][X] = ((tri64 >> 18) & 0x1FF) * scaler;
	v3_int[1][Y] = ((tri64 >> 27) & 0x1FF) * scaler;
	v3_int[2][X] = ((tri64 >> 36) & 0x1FF) * scaler;
	v3_int[2][Y] = ((tri64 >> 45) & 0x1FF) * scaler;
	v3_int[0][Z] = ((unsigned long)tri64 >> 54);
	v3_int[1][Z] = ((unsigned long)tri64 >> 54);
	v3_int[2][Z] = ((unsigned long)tri64 >> 54);
}

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

void	draw_img_from_tri64s(t_image_info img)
{
	int				i;
	int				v3_int[3][3];
	unsigned int	z_color;

	i = 0;
	while (i < img.tri_count)
	{
		//printf("scaler is %f \n", img.scaler);
		//exit(0);
		collect_tri64(v3_int, img.tri_64s[i], img.scaler);
		if (is_inside_image(v3_int))
		{
			draw_line_img(v3_int[0], v3_int[1], img.addr, img);
			draw_line_img(v3_int[1], v3_int[2], img.addr, img);
			draw_line_img(v3_int[0], v3_int[2], img.addr, img);
			fill_tri(v3_int, img.addr, img);
		}
			
		//fill_tri(&(v3_integers[1]), arg.img.addr, arg.img);
		//draw_line_img(v3_integers[0], v3_integers[1], arg.img.addr, arg.img);
		//draw_line_img(v3_integers[1], v3_integers[2], arg.img.addr, arg.img);
		//draw_line_img(v3_integers[0], v3_integers[2], arg.img.addr, arg.img);
		i++;
	}
}