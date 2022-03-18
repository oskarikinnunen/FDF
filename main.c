/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/18 20:22:05 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	stage_mlxi_values(t_mlx_i *i);

int	main(int argc, char **argv)
{
	t_mlx_i			i;
	t_image_info	img;
	t_map			maps[2];

	if (argc != 2)
		return (-1);
	read_inputmap(argv[1], &(maps[0]));
	read_inputmap(argv[1], &(maps[1]));
	i.maps = (t_map *)(&maps);
	i.mlx = mlx_init();
	i.win = mlx_new_window(i.mlx, WSZ, WSZ, "new_window");
	img.ptr = mlx_new_image(i.mlx, WSZ, WSZ);
	i.img = &img;
	stage_mlxi_values(&i);
	mlx_loop_hook(i.mlx, loop, &i);
	mlx_key_hook(i.win, key_loop, &i);
	mlx_loop(i.mlx);
	return (0);
}

#ifdef EXTRA

static void	stage_mlxi_values(t_mlx_i *i)
{
	i->img->z_values = ft_memalloc(sizeof(int) * WSZ);
	i->x_angle = 45;
	i->y_angle = 30;
	i->threads = sysconf(_SC_NPROCESSORS_ONLN);
	gettimeofday(&(i->t1), NULL);
}
#else

static void	stage_mlxi_values(t_mlx_i *i)
{
	i->img->z_values = ft_memalloc(sizeof(int) * WSZ);
	i->x_angle = 45;
	i->y_angle = 30;
}
#endif