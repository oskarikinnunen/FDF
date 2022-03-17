/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/17 15:31:53 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <pthread.h>

void	get_time(t_mlx_i *i)
{
	struct timeval	t2;

	gettimeofday(&t2, NULL);
	i->time = (t2.tv_sec - i->t1.tv_sec) * 1000.0
		+ (t2.tv_usec - i->t1.tv_usec) / 1000.0;
	i->p_time = i->time;
}

/* The memory for cpy is already allocated in i->maps[1] */
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
	save_z(&cpy, &img, 0);
	map_preprocess(&cpy, *i);
	ft_bzero(addr, WSZ * WSZ * 4);
	threads_start(cpy, img, addr, 4);
	mlx_put_image_to_window(i->mlx, i->win, i->img->ptr, 0, 0);
	i->tick++;
	if (i->tick == 1000)
		exit(0);
	return (1);
}

int	mouse_loop(int button, int x, int y, void *p)
{
	t_mlx_i			*i;

	i = (t_mlx_i *)p;
	if (button == 1)
		i->x_angle += 5 * (x < WSZ / 2) + -5 * (x > WSZ / 2);
	y = 0;
	x = y;
	return (1);
}

int	key_loop(int keycode, void *p)
{
	t_mlx_i		*i;

	i = (t_mlx_i *)p;
	i->x_angle += (keycode == KEY_LEFT) * -5;
	i->x_angle += (keycode == KEY_RGHT) * 5;
	i->y_angle += (keycode == KEY_DOWN) * -5;
	i->y_angle += (keycode == KEY_UP) * 5;
	i->x_angle = ft_clamp(i->x_angle, -45, 45);
	i->y_angle = ft_clamp(i->y_angle, -30, 40);
	if (keycode == KEY_ESC || keycode == 65307)
	{
		free_map(&(i->maps[1]));
		free_map(i->maps);
		exit(0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_mlx_i			i;
	t_image_info	img;
	t_map			maps[2];

	if (argc != 2)
		return (-1);
	i.mlx = mlx_init();
	i.win = mlx_new_window(i.mlx, WSZ, WSZ, "new_window");
	ft_bzero(maps, sizeof(t_map) * 2);
	ft_bzero(&img, sizeof(t_image_info));
	read_inputmap(argv[1], &(maps[0]));
	read_inputmap(argv[1], &(maps[1]));
	img.ptr = mlx_new_image(i.mlx, WSZ, WSZ);
	i.tick = 0; // DEbug, remove
	i.img = &img;
	i.maps = (t_map *)(&maps);
	img.z_values = malloc(sizeof(int) * WSZ);
	i.x_angle = 45;
	i.y_angle = 30;
	gettimeofday(&(i.t1), NULL);
	mlx_loop_hook(i.mlx, loop, &i);
	mlx_mouse_hook(i.win, mouse_loop, &i);
	mlx_key_hook(i.win, key_loop, &i);
	printf("found %li threads\n", sysconf(_SC_NPROCESSORS_ONLN));
	mlx_loop(i.mlx);
	return (0);
}
