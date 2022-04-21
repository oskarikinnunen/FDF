/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/21 13:12:34 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_errors.h"

static	void	stage_mlxi_values(t_mlx_i *i);

int	main(int argc, char **argv)
{
	t_mlx_i			i;
	t_image_info	img;
	t_tri_map		tmaps[2];

	if (argc != 2)
		return (-1);
	ft_bzero(&i, sizeof(t_mlx_i));
	read_inputmap(argv[1], tmaps);
	i.maps = (t_tri_map *)(&tmaps);
	i.mlx = mlx_init();
	i.win = mlx_new_window(i.mlx, WSZ, WSZ, "new_window");
	img.ptr = mlx_new_image(i.mlx, WSZ, WSZ - IMAGE_Y);
	img.addr = mlx_get_data_addr(img.ptr, (int *)&(img.bpp),
			(int *)&(img.size_line), &(img.endian));
	i.img = &img;
	stage_mlxi_values(&i);
	mlx_clear_window(i.mlx, i.win);
	mlx_string_put(i.mlx, i.win, 5, IMAGE_Y / 2, INT_MAX, USAGE_MSG);
	mlx_key_hook(i.win, key_loop, &i);
	mlx_loop_hook(i.mlx, loop, &i);
	mlx_loop(i.mlx);
}

/*
	This is needed since mlx_new_image forces 'size_line' to a multiple of 256,
	which makes my assumption of:
		'sizeline == WSZ * img.bpp / 8'
	wrong in some cases, which in turn can make this program segfault
	when accessing the img.addr memory in z_drawing.c with that wrong assumption.
	(This behaviour only happens with the Metal implementation of mlx,
		see: mlx_image.swift:26)
*/
static int	mlx_freakout(t_mlx_i *i)
{
	if (i->img->size_line != WSZ * (i->img->bpp / 8))
		return (1);
	return (0);
}

#ifdef EXTRA

static void	stage_threads(t_mlx_i *i)
{
	i->thread_count = (int)sysconf(_SC_NPROCESSORS_ONLN);
	if (i->thread_count > 0)
	{
		i->threads = (pthread_t *)malloc(i->thread_count * sizeof(pthread_t));
		i->t_args = (t_thread_arg *)malloc
			(i->thread_count * sizeof(t_thread_arg));
	}
}

static void	stage_mlxi_values(t_mlx_i *i)
{
	ft_putstr("Successfully opened file \n");
	if (mlx_freakout(i))
		error_exit("MLX allocated wrong size, make sure WSZ is n^2");
	i->img->z_buffer = (int *)ft_memalloc(WSZ * (WSZ - IMAGE_Y) * sizeof(int));
	i->img->depthlayer = (int *)ft_memalloc(i->maps->tri_count * sizeof(int));
	i->x_angle = 30;
	i->y_angle = 40;
	i->z_scale = 0.5 * (127 / i->maps->z_extreme);
	if (gettimeofday(&(i->t1), NULL) <= -1)
		error_exit("Gettimeofday call failed (stage_mlxi_values)");
	stage_threads(i);
	if (i->img->depthlayer == NULL || i->img->z_buffer == NULL
		|| i->threads == NULL || i->t_args == NULL || i->thread_count <= 0)
		error_exit("Malloc failed (stage_mlxi_values)");
	if (i->maps->tri_count <= 0)
		error_exit("Invalid amount of triangles (stage_mlxi_values)");
	if (WSZ < 256)
		error_exit("WSZ too small (stage_mlxi_values)");
}
#else

static void	stage_mlxi_values(t_mlx_i *i)
{
	ft_putstr("Successfully opened file \n");
	if (mlx_freakout(i))
		error_exit("MLX allocated wrong size, make sure WSZ is n^2");
	i->img->z_buffer = (int *)ft_memalloc(WSZ * (WSZ - IMAGE_Y) * sizeof(int));
	i->img->depthlayer = (int *)ft_memalloc((unsigned int)i->maps->tri_count
			* sizeof(int));
	if (i->img->depthlayer == NULL || i->img->z_buffer == NULL)
		error_exit("Malloc failed (stage_mlxi_values)");
	i->x_angle = 30;
	i->y_angle = 40;
	i->z_scale = 0.5 * (127 / i->maps->z_extreme);
	if (i->img->depthlayer == NULL || i->img->z_buffer == NULL)
		error_exit("Malloc failed (stage_mlxi_values)");
	if (i->maps->tri_count <= 0)
		error_exit("Invalid amount of triangles (stage_mlxi_values)");
	if (WSZ < 256)
		error_exit("WSZ too small (stage_mlxi_values)");
}
#endif