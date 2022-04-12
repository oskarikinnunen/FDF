/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:03:32 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/12 18:11:13 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_errors.h"

/*

	int				i;
	unsigned int	faceheight;

	i = 0;
	while (i < (WSZ * (WSZ - IMAGE_Y)))
	{
		faceheight = (unsigned int)(img.z_buffer[i] & 0xFFFF);
		if (faceheight > 0)
		{
			*(unsigned int *)(img.addr + (i * sizeof(int)))
				= get_color(faceheight);
		}
		i++;
	}
*/

#ifdef EXTRA

static void	*thread_draw(void *arg)
{
	t_thread_arg	t_arg;
	int				i;
	unsigned int	faceheight;

	t_arg = *(t_thread_arg *)arg;
	i = t_arg.startpixel;
	while (i < t_arg.endpixel)
	{
		faceheight = (unsigned int)(t_arg.img->z_buffer[i] & 0xFFFF);
		if (faceheight > 0)
		{
			*(unsigned int *)(t_arg.img->addr + (i * sizeof(int)))
				= get_pixel_color(faceheight);
		}
		i++;
	}
	return (NULL);
}

void	mt_draw_from_z_buff(t_mlx_i i)
{
	int	t_i;
	int	image_length;

	image_length = WSZ * (WSZ - IMAGE_Y);
	t_i = 0;
	while (t_i < i.thread_count)
	{
		i.t_args[t_i].startpixel = t_i * (image_length / i.thread_count);
		i.t_args[t_i].endpixel = (t_i + 1) * (image_length / i.thread_count);
		i.t_args[t_i].img = i.img;
		if (pthread_create(&i.threads[t_i], NULL, thread_draw,
			(void *)&(i.t_args[t_i])) != 0)
			error_exit("pthread create fail (mt_draw_from_z_buff)");
		t_i++;
	}
	t_i = 0;
	while (t_i < i.thread_count)
	{
		pthread_join(i.threads[t_i], NULL);
		t_i++;
	}
}

#endif