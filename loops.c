/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:13:50 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/18 22:46:57 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#ifdef EXTRA

static void	get_time(t_mlx_i *i)
{
	struct timeval	t2;

	gettimeofday(&t2, NULL);
	i->time = (t2.tv_sec - i->t1.tv_sec) * 1000.0
		+ (t2.tv_usec - i->t1.tv_usec) / 1000.0;
	i->p_time = i->time;
}

int	loop(void *p)
{
	t_mlx_i			*i;
	t_image_info	img;
	t_map			cpy;
	char			*addr;

	i = (t_mlx_i *)p;
	img = *(i->img);
	cpy = i->maps[1];
	addr = mlx_get_data_addr
		(img.ptr, &(img.bpp), &(img.size_line), &(img.endian));
	map_cpy(i->maps, &cpy);
	get_time(i);
	map_animate(&cpy, i->time);
	save_z(&cpy, &img);
	map_preprocess(&cpy, *i);
	ft_bzero(addr, WSZ * WSZ * 4);
	threads_start(cpy, img, addr, i->threads);
	mlx_put_image_to_window(i->mlx, i->win, i->img->ptr, 0, 25);
	i->tick++;
	return (1);
}
#else

//static void	populate_draw_args(t_draw_args *args) {}

int	loop(void *p)
{
	t_mlx_i			*i;
	t_image_info	img;
	t_map			cpy;
	t_draw_args		draw_args;
	char			*addr;

	i = (t_mlx_i *)p;
	img = *(i->img);
	cpy = i->maps[1];
	addr = mlx_get_data_addr
		(img.ptr, &(img.bpp), &(img.size_line), &(img.endian));
	map_cpy(i->maps, &cpy);
	save_z(&cpy, &img);
	map_preprocess(&cpy, *i);
	ft_bzero(addr, WSZ * WSZ * 4);
	draw_args.addr = addr;
	draw_args.img = img;
	draw_args.map = cpy;
	draw_args.start = 0;
	draw_args.stop = cpy.length;
	drawmap((void *)&draw_args);
	mlx_put_image_to_window(i->mlx, i->win, i->img->ptr, 0, 25);
	return (1);
}
#endif

int	key_loop(int keycode, void *p)
{
	t_mlx_i		*i;

	i = (t_mlx_i *)p;
	i->x_angle += (keycode == KEY_LEFT) * -5;
	i->x_angle += (keycode == KEY_RGHT) * 5;
	i->y_angle += (keycode == KEY_DOWN) * -5;
	i->y_angle += (keycode == KEY_UP) * 5;
	i->x_angle = ft_clamp(i->x_angle, -45, 45);
	i->y_angle = ft_clamp(i->y_angle, -30, 30);
	if (keycode == KEY_ESC || keycode == 65307)
	{
		free_map(&(i->maps[1]));
		free_map(i->maps);
		exit(0);
	}
	return (1);
}
