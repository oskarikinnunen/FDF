/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/25 13:53:39 by okinnune         ###   ########.fr       */
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
	read_inputmap(argv[1], maps);
	i.maps = (t_map *)(&maps);
	i.mlx = mlx_init();
	i.win = mlx_new_window(i.mlx, WSZ, WSZ, "new_window");
	img.ptr = mlx_new_image(i.mlx, WSZ, WSZ - IMAGE_Y);
	img.addr = mlx_get_data_addr(img.ptr, &(img.bpp),
		&(img.size_line), &(img.endian));
	i.img = &img;
	stage_mlxi_values(&i);
	mlx_string_put(i.mlx, i.win, 5, IMAGE_Y / 2, INT_MAX, USAGE_MSG);
	mlx_loop_hook(i.mlx, loop, &i);
	mlx_key_hook(i.win, key_loop, &i);
	mlx_loop(i.mlx);
	return (0);
}

#ifdef EXTRA

static void	stage_mlxi_values(t_mlx_i *i)
{

	i->img->scaler = (float)WSZ / 512.0;
	i->img->tri_count = (i->maps->length - i->maps->width
		- ((i->maps->length - i->maps->width)/ i->maps->width)) * 2;
	printf("TRICOUNT: %i \n", i->img->tri_count);
	i->img->tri_64s = ft_memalloc(i->img->tri_count * sizeof(long)); // PRotec!!
	i->img->depthlayer = ft_memalloc(i->img->tri_count * sizeof(int));
	if (i->img->depthlayer == NULL)
		error_exit("Depthlayer malloc failed (stage_mlxi_values)");
	i->x_angle = -30;
	i->y_angle = -40;
	i->z_scale = 0.5 * (127 / i->maps->z_extreme);
	if (gettimeofday(&(i->t1), NULL) <= -1)
		error_exit("Gettimeofday call failed (stage_mlxi_values)");
}
#else

static void set_decimated_tricount(t_map map, t_image_info *img)
{
	int	tricount;
	int	i;
	int	target;

	tricount = 0;
	i = 0;
	while(i < map.length - (map.width * (map.decimation_factor + 2)))
	{
		
		target = i + map.decimation_factor + 1;
		while (i < target)
		{
			i++;
			if ((i + 1) % map.width == 0)
			{
				i += (map.decimation_factor * map.width) + 1;
				break ;
			}
		}
		tricount += 2 * (i == target);
	}
	printf("decim tricount function went through %i points \n", i);
	img->tri_count = tricount;
	printf("decimated tricount %i\n", tricount);
	exit(0);
}

static void	stage_mlxi_values(t_mlx_i *i)
{
	i->img->scaler = (float)WSZ / 512.0;
	i->img->tri_count = (i->maps->length - i->maps->width
		- ((i->maps->length - i->maps->width)/ i->maps->width)) * 2;
	i->maps->decimation_factor = 0;
	//printf("decimation factor %i \n", i->maps->decimation_factor);
	printf("TRICOUNT: %i \n", i->img->tri_count);
	//set_decimated_tricount(*i->maps, i->img);
	//printf("TRICOUNT AFTER DECIMATE STEP: %i \n", i->img->tri_count);
	//tricount_decimate(2, *(i->maps));
	//exit(0);
	i->img->tri_64s = ft_memalloc(i->img->tri_count * sizeof(long)); // PRotec!!
	i->img->depthlayer = ft_memalloc(i->img->tri_count * sizeof(int));
	if (i->img->depthlayer == NULL)
		error_exit("Depthlayer malloc failed (stage_mlxi_values)");
	i->x_angle = -30;
	i->y_angle = -40;
	i->z_scale = 0.5 * (127 / i->maps->z_extreme);
}
#endif