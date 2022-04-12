/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:13:50 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/12 18:08:22 by okinnune         ###   ########.fr       */
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
		error_exit("Gettimeofday call failed (get_time)");
	i->time = (t2.tv_sec - i->t1.tv_sec) * 1000.0
		+ (t2.tv_usec - i->t1.tv_usec) / 1000.0;
}

int	loop(void *p)
{
	t_mlx_i			*i;
	t_image_info	img;
	t_tri_map		cpy;

	i = (t_mlx_i *)p;
	img = *(i->img);
	cpy = i->maps[1];
	cpy_map(*i->maps, cpy);
	ft_bzero(img.depthlayer, cpy.tri_count * sizeof(int));
	get_time(i);
	animate_map(cpy, i->time);
	preprocess_map(cpy, *i);
	z_pass(cpy, img, i->wireframe_toggle);
	mt_draw_from_z_buff(*i);
	mlx_put_image_to_window(i->mlx, i->win, i->img->ptr, 0, IMAGE_Y);
	mlx_do_sync(i->mlx);
	return (1);
}
#else

int	loop(void *p)
{
	t_mlx_i			*i;
	t_image_info	img;
	t_tri_map		cpy;

	i = (t_mlx_i *)p;
	img = *(i->img);
	cpy = i->maps[1];
	cpy_map(*i->maps, cpy);
	preprocess_map(cpy, *i);
	z_pass(cpy, img, i->wireframe_toggle);
	draw_from_z_buff(img);
	mlx_put_image_to_window(i->mlx, i->win, i->img->ptr, 0, IMAGE_Y);
	mlx_do_sync(i->mlx);
	return (1);
}
#endif

int	key_loop(int keycode, void *p)
{
	t_mlx_i		*i;

	if (keycode == KEY_ESC)
		exit(0);
	i = (t_mlx_i *)p;
	i->x_angle += (keycode == KEY_LEFT) * -5;
	i->x_angle += (keycode == KEY_RGHT) * 5;
	i->y_angle += (keycode == KEY_DOWN) * -5;
	i->y_angle += (keycode == KEY_UP) * 5;
	i->z_scale += (keycode == KEY_Z) * -0.10 * (127 / i->maps->z_extreme);
	i->z_scale += (keycode == KEY_X) * 0.10 * (127 / i->maps->z_extreme);
	i->z_scale = ft_clampf(i->z_scale, (127 / i->maps->z_extreme) * -1,
			(127 / i->maps->z_extreme));
	i->x_angle = ft_clamp(i->x_angle, -45, 45);
	i->y_angle = ft_clamp(i->y_angle, 0, 40);
	if (keycode == KEY_W)
		i->wireframe_toggle = !i->wireframe_toggle;
	return (1);
}
