/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:03:32 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/08 14:40:47 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

typedef struct s_thread_arg
{
	t_image_info *img;
	int	startPixel;
	int	endPixel;
}	t_thread_arg;

#ifdef EXTRA

static void *thread_draw(void *arg)
{
	t_thread_arg	t_arg;
	int				i;
	unsigned int	faceheight;

	t_arg = *(t_thread_arg *)arg;
	i = t_arg.startPixel;
	while (i < t_arg.endPixel)
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
	t_thread_arg arg[4];

	
	image_length = WSZ * (WSZ - IMAGE_Y);
	t_i = 0;
	while (t_i < i.thread_count)
	{
		arg[t_i].startPixel = t_i * (image_length / i.thread_count);
		arg[t_i].endPixel = (t_i + 1) * (image_length / i.thread_count);
		arg[t_i].img = i.img;
		
		pthread_create(&i.threads[t_i], NULL, thread_draw, (void *)&arg[t_i]);
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