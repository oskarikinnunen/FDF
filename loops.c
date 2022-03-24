/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:13:50 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/24 15:42:55 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_errors.h"

#ifdef EXTRA

static void	get_time(t_mlx_i *i)
{
	struct timeval	t2;

	gettimeofday(&(t2), NULL);
	if (gettimeofday(&(t2), NULL) <= -1)
		error_exit_free_map("Gettimeofday call failed (get_time)", i->maps);
	i->time = (t2.tv_sec - i->t1.tv_sec) * 1000.0
		+ (t2.tv_usec - i->t1.tv_usec) / 1000.0;
}

void	debug_zvalues(t_map map, t_mlx_i *mlx_i)
{
	for (int i = 0; i < map.length; i++)
		mlx_string_put(mlx_i->mlx, mlx_i->win, map.points[i][X], map.points[i][Y], INT_MAX, ft_itoa(map.points[i][Z]));
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
	if (addr == NULL)
		error_exit_free_map("mlx_get_data_addr rtn NULL value (loop)", i->maps);
	cpy_map(i->maps, &cpy);
	get_time(i);
	//animate_map(&cpy, i->time);
	save_z(&cpy, &img);
	preprocess_map(&cpy, *i);
	//mlx_clear_window(i->mlx, i->win);
	//debug_zvalues(cpy, i);
	ft_bzero(addr, WSZ * WSZ * 4);
	i->threads = 1;
	//threads_start(cpy, img, i->threads,	z_pass_map);
	threads_start(cpy, img, i->threads, draw_map);
	mlx_put_image_to_window(i->mlx, i->win, i->img->ptr, 0, IMAGE_Y);
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
	//Get data addrs only once!!!
	addr = img.addr;
	/*addr = mlx_get_data_addr
		(img.ptr, &(img.bpp), &(img.size_line), &(img.endian));
	if (addr == NULL)
		error_exit_free_map("mlx_get_data_addr rtn NULL value (loop)", i->maps);*/
	cpy_map(i->maps, &cpy);
	save_z(&cpy, &img);
	preprocess_map(&cpy, *i);
	ft_bzero(addr, WSZ * WSZ * sizeof(int));
	draw_args.img = img;
	draw_args.map = cpy;
	draw_args.start = 0;
	draw_args.stop = cpy.length;
	draw_map((void *)&draw_args);
	mlx_put_image_to_window(i->mlx, i->win, i->img->ptr, 0, IMAGE_Y);
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
	i->y_angle = ft_clamp(i->y_angle, -45, 45);
	if (keycode == KEY_ESC || keycode == 65307)
	{
		free_maps(i->maps);
		exit(0);
	}
	return (1);
}
