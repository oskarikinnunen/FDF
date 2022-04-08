/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/08 16:45:25 by okinnune         ###   ########.fr       */
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
	read_inputmap(argv[1], tmaps);
	i.maps = (t_tri_map *)(&tmaps);
	i.mlx = mlx_init();
	i.win = mlx_new_window(i.mlx, WSZ, WSZ, "new_window");
	img.ptr = mlx_new_image(i.mlx, WSZ, WSZ - IMAGE_Y); //TODO: wrong size
	img.addr = mlx_get_data_addr(img.ptr, &(img.bpp),
			&(img.size_line), &(img.endian));
	i.img = &img;
	stage_mlxi_values(&i);
	//mlx_clear_window(i.mlx, i.win);
	mlx_string_put(i.mlx, i.win, 5, IMAGE_Y / 2, INT_MAX, USAGE_MSG);
	mlx_key_hook(i.win, key_loop, &i);
	mlx_loop_hook(i.mlx, loop, &i);
	mlx_loop(i.mlx);
}

#ifdef EXTRA
static void	stage_threads(t_mlx_i *i)
{
	i->thread_count = (int)sysconf(_SC_NPROCESSORS_ONLN);
	if (i->thread_count > 0)
	{
		i->threads = (pthread_t *)malloc(i->thread_count * sizeof(pthread_t));
		i->t_args = (t_thread_arg *)malloc(i->thread_count * sizeof(t_thread_arg));
	}
}

static void	stage_mlxi_values(t_mlx_i *i)
{
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
	if (WSZ < 180)
		error_exit("WSZ too small (stage_mlxi_values)");
}
#else

static void	stage_mlxi_values(t_mlx_i *i)
{
	printf("TRICOUNT: %i \n", i->maps->tri_count);
	i->img->z_buffer = (int *)ft_memalloc(WSZ * (WSZ - IMAGE_Y) * sizeof(int));
	i->img->depthlayer = (int *)ft_memalloc(i->maps->tri_count * sizeof(int));
	if (i->img->depthlayer == NULL || i->img->z_buffer == NULL)
		error_exit("Malloc failed (stage_mlxi_values)");
	i->x_angle = 30;
	i->y_angle = 40;
	if (i->maps->z_extreme == 0)
	{
		i->maps->z_extreme = 1;
		i->maps[1].z_extreme = 1;
	}
	i->z_scale = 0.5 * (127 / i->maps->z_extreme);
}
#endif