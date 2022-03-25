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
void	threads_start(t_map map, t_image_info img, int corecount, void (*func)(void *))
{
	static pthread_t		*threads;
	static t_draw_args		*t_args;
	signed int				i;

	if (threads == NULL)
		threads = ft_memalloc(sizeof(pthread_t) * corecount);
	if (t_args == NULL)
		t_args = ft_memalloc(sizeof(t_draw_args) * corecount);
	i = -1;
	while (++i < corecount)
	{
		t_args[i].start = i * (map.length / corecount);
		t_args[i].start -= t_args[i].start % 4;
		t_args[i].stop = (i + 1) * (map.length / corecount);
		t_args[i].stop -= (i != corecount - 1) * (t_args[i].stop % 4);
		t_args[i].map = map;
		t_args[i].img = img;
		pthread_create(&(threads[i]), NULL, func, &(t_args[i]));
	}
	i = -1;
	while (++i < corecount)
		pthread_join(threads[i], NULL);
}
#endif

void	*z_pass_map(void *draw_args)
{
	t_draw_args		arg;
	int				i;
	int				face_i3[4][3];
	unsigned int	face_color;

	arg = *(t_draw_args *)draw_args;
	i = arg.start;
	printf("points range %i to %i map length %i \n", arg.start, arg.stop, arg.map.length);
	while ((i + arg.map.width + 1) <= arg.map.length && i < arg.stop)
	{
		//printf("z_buffer val INDEX: %i VALUE: %i \n", img.)
		
		collect_face_z_pass(&(arg.map.points[i]), face_i3, arg.map.width);
		printf("z values for face %i, %i, %i, %i \n", face_i3[0][Z], face_i3[1][Z], face_i3[2][Z], face_i3[3][Z]);
		face_color = calc_face_color(arg.img.depthlayer, i, arg.map.width);
		fill_z_tri(face_i3, arg.img.addr, arg.img, face_color);
		fill_z_tri(&(face_i3[1]), arg.img.addr, arg.img, face_color);
		
		/*fill_tri(&(v3_integers[1]), arg.img.addr, arg.img);
		draw_line_img(v3_integers[0], v3_integers[1], arg.img.addr, arg.img);
		draw_line_img(v3_integers[1], v3_integers[2], arg.img.addr, arg.img);
		draw_line_img(v3_integers[0], v3_integers[2], arg.img.addr, arg.img);*/
		i++;
		i += ((i + 1) % arg.map.width == 0);
	}
	return (NULL);
}

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
}

static void	collect_tri64(int v3_int[3][3], long	tri64)
{
	v3_int[0][X] = (tri64 << 0) & 0x1FF;
	v3_int[0][Y] = (tri64 << 9) & 0x1FF;
	v3_int[1][X] = (tri64 << 18) & 0x1FF;
	v3_int[1][Y] = (tri64 << 27) & 0x1FF;
	v3_int[2][X] = (tri64 << 36) & 0x1FF;
	v3_int[2][Y] = (tri64 << 45) & 0x1FF;
	v3_int[0][Z] = (tri64 << 54);
	v3_int[1][Z] = (tri64 << 54);
	v3_int[2][Z] = (tri64 << 54);
}

void	*draw_map_from_tri64s(void *draw_args)
{
	t_draw_args		arg;
	int				i;
	int				v3_int[3][3];
	unsigned int	z_color;

	arg = *(t_draw_args *)draw_args;
	i = arg.start;
	while (i < arg.stop)
	{
		z_color = (arg.img.depthlayer[i] & Z_CLRMASK)
			+ (arg.img.depthlayer[i + 1] & Z_CLRMASK)
			+ (arg.img.depthlayer[i + arg.map.width] & Z_CLRMASK)
			+ (arg.img.depthlayer[i + arg.map.width + 1] & Z_CLRMASK);
		z_color = ft_clamp((z_color / 4) * Z_CLRMUL, 0, 255);
		arg.img.tri_64s[i];
		//fill_tri(v3_integers, arg.img.addr, arg.img);
		//fill_tri(&(v3_integers[1]), arg.img.addr, arg.img);
		//draw_line_img(v3_integers[0], v3_integers[1], arg.img.addr, arg.img);
		//draw_line_img(v3_integers[1], v3_integers[2], arg.img.addr, arg.img);
		//draw_line_img(v3_integers[0], v3_integers[2], arg.img.addr, arg.img);
		i++;
	}
	return (NULL);
}