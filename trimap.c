/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:28:19 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/06 17:22:49 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	face_to_tri(float **v3, float ***tri, int width)
{
	int			i;
	int			indx[2];

	i = 0;
	tri[0] = ft_memalloc(3 * sizeof(float *)); //Maybe could be done at the same time
	tri[1] = ft_memalloc(3 * sizeof(float *)); //TODO: protec
	ft_bzero(indx, sizeof(int [2]));
	while (i < 3)
	{
		indx[0] = ((i >= 2) * width) + !((i + 1) % 2);
		indx[1] = ((i + 1 >= 2) * width) + !((i + 2) % 2);
		tri[0][i] = ft_memalloc(3 * sizeof(float));
		tri[1][i] = ft_memalloc(3 * sizeof(float)); //PROTEC
		//printf("copying v3 x%f y%f z%f \n", v3[indx[0]][X],v3[indx[0]][Y],v3[indx[0]][Z]);
		ft_memcpy(tri[0][i], v3[indx[0]], sizeof(float [3]));
		ft_memcpy(tri[1][i], v3[indx[1]], sizeof(float [3]));
		i++;
	}
}

static void	populate_simple_values(t_map *map, t_tri_map *trimap)
{
	trimap->tri_count = (map->length - map->width
		- ((map->length - map->width) / map->width)) * 2;
	trimap->z_extreme = map->z_extreme;
	trimap->dimensions[X] = map->width;
	trimap->dimensions[Y] = map->length / map->width;
	ft_memcpy(&(trimap[1]), trimap, sizeof(t_tri_map));
}

void	map_to_tri_map(t_map *map, t_tri_map *trimap) //Make copy aswell
{
	int		i;
	long	tri_i;
	
	populate_simple_values(map, trimap);
	trimap->tri_list = (float ***)
		ft_memalloc(trimap->tri_count * sizeof (float **)); //TODO: protec
	trimap[1].tri_list = (float ***)
		ft_memalloc(trimap->tri_count * sizeof (float **)); //TODO: protec
	i = 0;
	tri_i = 0;
	while (i <= map->length - map->width - 1)
	{
		face_to_tri(&(map->points[i]), &(trimap->tri_list[tri_i]), map->width);
		face_to_tri(&(map->points[i]), &(trimap[1].tri_list[tri_i]), map->width);
		i++;
		i += (i + 1) % map->width == 0;
		tri_i += 2;
	}
}
