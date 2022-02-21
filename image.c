/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:32:00 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/18 17:13:48 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	create_image(void **img, t_image_info **info, t_mlx_i *i)
{
	*img = mlx_new_image(i->mlx, WSZ, WSZ / 2);
	*info = (t_image_info *)malloc(sizeof(t_image_info));
	(*info)->size_line = WSZ;
	(*info)->bpp = 32;
	(*info)->endian = 0;
}

//TODO: CHECK IF IMG IS NULL AFTER CREATEIMAGE
char	*ci_data_adder(t_mlx_i *i, void **imagereturn)
{
	static void			*img;
	static t_image_info	*info;

	if (img == NULL)
		create_image(&img, &info, i);
	*imagereturn = img;
	return mlx_get_data_addr(img, &(info->bpp), &(info->size_line), &(info->endian));
}