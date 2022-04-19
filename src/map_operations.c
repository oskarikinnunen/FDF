/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 04:36:32 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/19 17:42:26 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cpy_map(t_tri_map src, t_tri_map dst)
{
	int	i;

	i = 0;
	while (i < src.tri_count)
	{
		ft_memcpy(dst.tri_list[i][0], src.tri_list[i][0], sizeof(int [3]));
		ft_memcpy(dst.tri_list[i][1], src.tri_list[i][1], sizeof(int [3]));
		ft_memcpy(dst.tri_list[i][2], src.tri_list[i][2], sizeof(int [3]));
		i++;
	}
}

#ifdef EXTRA

void	animate_map(t_tri_map map, double time)
{
	static float	add[3][3] = {
	{1,	0, 0},
	{0, 1, 0},
	{0, 0, 1}
	};

	add[Z][Z] = sin(time / 1000);
	mul_tri_map(add, map);
}
#endif

static void	add_tri_map(t_tri_map map, float add[3])
{
	int	i;

	i = 0;
	while (i < map.tri_count)
	{
		v3add(map.tri_list[i][0], add);
		v3add(map.tri_list[i][1], add);
		v3add(map.tri_list[i][2], add);
		i++;
	}
}

static void	fit_to_screen(t_tri_map map)
{
	int		min_x;
	int		min_y;
	int		i;

	min_x = WSZ;
	min_y = WSZ;
	i = 0;
	while (i < map.tri_count)
	{
		min_x = ft_min(min_x, (int)map.tri_list[i][0][X]);
		min_x = ft_min(min_x, (int)map.tri_list[i][1][X]);
		min_x = ft_min(min_x, (int)map.tri_list[i][2][X]);
		min_y = ft_min(min_y, (int)map.tri_list[i][0][Y]);
		min_y = ft_min(min_y, (int)map.tri_list[i][1][Y]);
		min_y = ft_min(min_y, (int)map.tri_list[i][2][Y]);
		i++;
	}
	add_tri_map(map, (float [3]){(float)-min_x, (float)-min_y, 0.0});
}

void	preprocess_map(t_tri_map map, t_mlx_i i)
{
	scale_with_size_matrix(map, i.z_scale);
	ft_bzero(i.img->depthlayer, map.tri_count * sizeof(int));
	save_face_colors(map, *i.img);
	add_tri_map(map, (float [3]){-WSZ / 2, -WSZ / 2, 0});
	scale_with_x_matrix(map, i.x_angle);
	scale_with_y_matrix(map, i.y_angle);
	save_depths(map, *i.img);
	fit_to_screen(map);
}
