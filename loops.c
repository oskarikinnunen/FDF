/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:13:50 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/25 11:17:41 by okinnune         ###   ########.fr       */
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

int	loop(void *p)
{
	t_mlx_i			*i;
	t_image_info	img;
	t_map			cpy;
	char			*addr;

	i = (t_mlx_i *)p;
	img = *(i->img);
	cpy = i->maps[1];
	addr = img.addr;
	cpy_map(i->maps, &cpy);
	ft_bzero(img.depthlayer, img.tri_count * sizeof(int));
	get_time(i);
	scale_with_size_matrix(&cpy, i->z_scale);
	animate_map(&cpy, i->time);
	depth_save(&cpy, &img, 0);
	preprocess_map(&cpy, *i);
	sorted_tri64s(&cpy, &img);
	ft_bzero(addr, (WSZ * (WSZ - IMAGE_Y)) * sizeof(int));
	draw_img_from_tri64s(img);
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
	char			*addr;

	i = (t_mlx_i *)p;
	img = *(i->img);
	cpy = i->maps[1];
	addr = img.addr;
	cpy_map(i->maps, &cpy);
	ft_bzero(img.depthlayer, img.tri_count * sizeof(int));
	scale_with_size_matrix(&cpy, i->z_scale);
	depth_save(&cpy, &img, 0);
	preprocess_map(&cpy, *i);
	sorted_tri64s(&cpy, &img);
	ft_bzero(addr, (WSZ * (WSZ - IMAGE_Y)) * sizeof(int));
	draw_img_from_tri64s(img);
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
	i->z_scale += (keycode == KEY_Z) * -0.05 * (127 / i->maps->z_extreme);
	i->z_scale += (keycode == KEY_X) * 0.05 * (127 / i->maps->z_extreme);
	i->z_scale = ft_clampf(i->z_scale, (127 / i->maps->z_extreme) * -1,
			(127 / i->maps->z_extreme));
	i->x_angle = ft_clamp(i->x_angle, -45, 45);
	i->y_angle = ft_clamp(i->y_angle, -40, 40);
	if (keycode == KEY_ESC || keycode == 65307)
	{
		free_maps(i->maps);
		exit(0);
	}
	return (1);
}
