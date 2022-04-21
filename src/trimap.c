/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:28:19 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/21 13:21:41 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_errors.h"

static void	face_to_tri(float **v3, float ***tri, int width)
{
	int			i;
	int			indx[2];

	i = 0;
	tri[0] = (float **)ft_memalloc(3 * sizeof(float *));
	tri[1] = (float **)ft_memalloc(3 * sizeof(float *));
	if (tri[0] == NULL || tri[1] == NULL)
		error_exit("Malloc failed (face_to_tri)");
	ft_bzero(indx, sizeof(int [2]));
	while (i < 3)
	{
		indx[0] = ((i >= 2) * width) + !((i + 1) % 2);
		indx[1] = ((i + 1 >= 2) * width) + !((i + 2) % 2);
		tri[0][i] = (float *)ft_memalloc(3 * sizeof(float));
		tri[1][i] = (float *)ft_memalloc(3 * sizeof(float));
		if (tri[0][i] == NULL || tri[1][i] == NULL)
			error_exit("Malloc failed (face_to_tri)");
		ft_memcpy(tri[0][i], v3[indx[0]], sizeof(float [3]));
		ft_memcpy(tri[1][i], v3[indx[1]], sizeof(float [3]));
		i++;
	}
}

static void	populate_simple_values(t_map *map, t_tri_map *trimap)
{
	ft_bzero(trimap, sizeof(t_tri_map [2]));
	trimap->tri_count = (map->length - map->width
			- ((map->length - map->width) / map->width)) * 2;
	trimap->z_extreme = map->z_extreme;
	trimap->dimensions[X] = map->width;
	trimap->dimensions[Y] = map->length / map->width;
	if (trimap->tri_count <= 0)
		error_exit("Invalid amount of triangles");
	ft_memcpy(&(trimap[1]), trimap, sizeof(t_tri_map));
}

void	map_to_tri_maps(t_map *map, t_tri_map *trimap)
{
	int		i;
	long	tri_i;

	populate_simple_values(map, trimap);
	trimap->tri_list = (float ***)
		ft_memalloc(trimap->tri_count * sizeof (float **));
	trimap[1].tri_list = (float ***)
		ft_memalloc(trimap->tri_count * sizeof (float **));
	if (trimap->tri_list == NULL || trimap[1].tri_list == NULL)
		error_exit("Malloc failed (map_to_tri_map)");
	i = 0;
	tri_i = 0;
	while (i <= map->length - map->width - 1)
	{
		face_to_tri(&(map->points[i]),
			&(trimap->tri_list[tri_i]), map->width);
		face_to_tri(&(map->points[i]),
			&(trimap[1].tri_list[tri_i]), map->width);
		tri_i += 2;
		i++;
		i += (i + 1) % map->width == 0;
	}
}
