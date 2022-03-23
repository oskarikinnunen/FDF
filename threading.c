/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:23:38 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/23 01:28:10 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//#define EXTRA

#ifdef EXTRA

/*static	void	*bzero_image(void	*args)
{
	t_draw_args	*draw_args;

	draw_args = ((t_draw_args *)args);
	ft_bzero(draw_args->addr + (draw_args->start * 4), (draw_args->stop - draw_args->start) * 1024);
	printf("Should have bzeroed! %i to %i \n", draw_args->start, draw_args->stop);
	return (NULL);
}*/

/* TODO: Make start and stop values dividible by 4 */
void	threads_start(t_map map, t_image_info img, char *addr, int corecount)
{
	static pthread_t		*threads;
	static t_draw_args		*t_args;
	int						i;

	if (threads == NULL)
		threads = ft_memalloc(sizeof(pthread_t) * corecount);
	if (t_args == NULL)
		t_args = ft_memalloc(sizeof(t_draw_args) * corecount);
	i = -1;
	while (++i < corecount)
	{
		t_args[i].start = i * (map.length / corecount);
		t_args[i].stop = (i + 1) * (map.length / corecount);
		t_args[i].addr = addr;
		t_args[i].map = map;
		t_args[i].img = img;
		pthread_create(&(threads[i]), NULL, draw_map, &(t_args[i]));
	}
	i = 0;
	while (i < corecount)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
#endif

/*void	*z_pass_map(void *draw_args)
{
	t_draw_args		arg;
	int				i;
	int				v3_integers[4][3];
	unsigned int				z_color;

	arg = *(t_draw_args *)draw_args;
	i = arg.start;
	while ((i + arg.map.width + 1) <= arg.map.length && i < arg.stop)
	{
		collect_square_z_pass(arg.map.points[i], v3_integers, arg.map.width);
		fill_tri(v3_integers, arg.addr, arg.img);
		fill_tri(&(v3_integers[1]), arg.addr, arg.img);
		draw_line_img(v3_integers[0], v3_integers[1], arg.addr, arg.img);
		draw_line_img(v3_integers[1], v3_integers[2], arg.addr, arg.img);
		draw_line_img(v3_integers[0], v3_integers[2], arg.addr, arg.img);
		i++;
		i += ((i + 1) % arg.map.width == 0);
	}
	return (NULL);
}*/

void	*draw_map(void *draw_args)
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
		/*printf("dl 0 %i \n", arg.img.depthlayer[i]);
		printf("dl 1 %i \n", arg.img.depthlayer[i + 1]);
		printf("i %i color is %i \n", i, z_color);*/
		z_color = ft_clamp((z_color / 4) * Z_CLRMUL, 0, 255);
		collect_square(&(arg.map.points[i]),
			v3_integers, arg.map.width, z_color);
		/*fill_tri(v3_integers, arg.addr, arg.img);
		fill_tri(&(v3_integers[1]), arg.addr, arg.img);*/
		draw_line_img(v3_integers[0], v3_integers[1], arg.addr, arg.img);
		//draw_line_img(v3_integers[1], v3_integers[2], arg.addr, arg.img);
		draw_line_img(v3_integers[0], v3_integers[2], arg.addr, arg.img);
		i++;
		i += ((i + 1) % arg.map.width == 0);
	}
	return (NULL);
}
