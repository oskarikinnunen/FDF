/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:16:27 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/09 19:20:37 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	expose_loop(void *param)
{
	t_mlx_i	*i;

	i = (t_mlx_i *)param;
	mlx_put_image_to_window(i->mlx, i->win, i->img->ptr, 0, 0);
}