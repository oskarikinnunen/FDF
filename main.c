/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/23 06:23:56 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_errors.h"

static	void	stage_mlxi_values(t_mlx_i *i);

int	main(int argc, char **argv)
{
	t_mlx_i			i;
	t_image_info	img;
	t_map			maps[2];

	if (argc != 2)
		return (-1);
	//ft_bzero(&(maps[0]), sizeof(t_map));
	//ft_bzero(&(maps[1]), sizeof(t_map));
	read_inputmap(argv[1], maps);
	i.maps[0] = maps[0];
	i.maps[1] = maps[1];
	i.mlx = mlx_init();
	i.win = mlx_new_window(i.mlx, WSZ, WSZ, "new_window");
	img.ptr = mlx_new_image(i.mlx, WSZ, WSZ);
	i.img = &img;
	stage_mlxi_values(&i);
	mlx_string_put(i.mlx, i.win, 5, IMAGE_Y / 2, INT_MAX, USAGE_MSG);
	mlx_loop_hook(i.mlx, loop, &i);
	mlx_key_hook(i.win, key_loop, &i);
	mlx_loop(i.mlx);
	return (0);
}

#ifdef EXTRA

static void	announce_threadcount(t_mlx_i *i)
{
	char	announcement_str[64];
	char	*threadcount_str;

	threadcount_str = ft_itoa(i->threads);
	if (threadcount_str == NULL)
		error_exit("Threadcount_str malloc failed (announce_threadcount)");
	ft_bzero(announcement_str, 64);
	ft_strcat(announcement_str, "Utilising ");
	ft_strcat(announcement_str, threadcount_str);
	ft_strcat(announcement_str, " logical processors.");
	mlx_string_put(i->mlx, i->win, 5, 10, 255 << 16, announcement_str);
	free(threadcount_str);
}

static void	stage_mlxi_values(t_mlx_i *i)
{
	i->img->depthlayer = ft_memalloc(sizeof(int) * WSZ);
	if (i->img->depthlayer == NULL)
		error_exit("Depthlayer malloc failed (stage_mlxi_values)");
	i->x_angle = -30;
	i->y_angle = 45;
	i->threads = sysconf(_SC_NPROCESSORS_ONLN);
	if (i->threads <= 0)
		error_exit("Sysconf found no logical processors (stage_mlxi_values)");
	announce_threadcount(i);
	if (gettimeofday(&(i->t1), NULL) <= -1)
		error_exit("Gettimeofday call failed (stage_mlxi_values)");
}
#else

static void	stage_mlxi_values(t_mlx_i *i)
{
	i->img->depthlayer = ft_memalloc(sizeof(int) * WSZ);
	if (i->img->depthlayer == NULL)
		error_exit("Depthlayer malloc failed (stage_mlxi_values)");
	i->x_angle = -30;
	i->y_angle = 45;
}
#endif