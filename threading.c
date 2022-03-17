/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:23:38 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/17 14:21:40 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <pthread.h>

void	*thread_bzero(void *args)
{
	t_thread_args	t_arg;

	t_arg = *(t_thread_args *)args;
	//ft_bzero(&(t_arg.addr[t_arg.index * WSZ * WSZ]), (WSZ * WSZ));
	//printf("thread %i bzeroing index %i\n", t_arg.index, (t_arg.index * WSZ * 4));
	return (NULL);
}

void	threads_start(t_map map, t_image_info img, char *addr, int corecount)
{
	static pthread_t		*threads;
	static t_thread_args	*t_args;
	int						i;

	if (threads == NULL)
		threads = ft_memalloc(sizeof(pthread_t) * corecount);
	if (t_args == NULL)
		t_args = ft_memalloc(sizeof(t_thread_args) * corecount);
	i = 0;
	while (i < corecount)
	{
		t_args[i].start = i * (map.length / corecount);
		t_args[i].stop =  (i + 1) * (map.length / corecount);
		//printf("Thread: %i Start: %i Stop: %i\n", i, t_args[i].start, t_args[i].stop);
		t_args[i].index = i;
		t_args[i].addr = addr;
		t_args[i].map = map;
		t_args[i].img = img;
		pthread_create(&(threads[i]), NULL, thread_drawmap, &(t_args[i]));
		//ft_bzero(&(addr[i * WSZ * WSZ]), (WSZ * WSZ));
		i++;
	}
	i = 0;
	while (i < corecount)
	{
		pthread_join(threads[i], NULL);
		//pthread_create(&(threads[i]), NULL, thread_drawmap, &(t_args[i]));
		i++;
	}
	/*i = 0;
	while (i < corecount)
	{
		pthread_join(threads[i], NULL);
		i++;
	}*/
}

void	*thread_drawmap(void *args)
{
	t_thread_args	t_arg;
	int				cur;
	int				v3_integers[4][3];
	int				vert_z;

	t_arg = *(t_thread_args *)args;
	cur = t_arg.start;
	while ((cur + t_arg.map.width + 1) <= t_arg.map.length && cur < t_arg.stop)
	{
		vert_z = (char)t_arg.img.z_values[cur] + (char)t_arg.img.z_values[cur + 1]
			+ (char)t_arg.img.z_values[cur + t_arg.map.width]
			+ (char)t_arg.img.z_values[cur + t_arg.map.width + 1];
		vert_z = ft_clamp(vert_z / 4, -128, 127) + 128;
		//move z buff to "real" coordinate
		collect_square(&(t_arg.map.points[cur]), v3_integers, t_arg.map.width, vert_z);
		fill_tri(v3_integers, t_arg.addr, t_arg.img);
		fill_tri(&(v3_integers[1]), t_arg.addr, t_arg.img);
		draw_line_img(v3_integers[0], v3_integers[1], t_arg.addr, t_arg.img);
		draw_line_img(v3_integers[1], v3_integers[2], t_arg.addr, t_arg.img);
		draw_line_img(v3_integers[0], v3_integers[2], t_arg.addr, t_arg.img);
		cur++;
		cur += ((cur + 1) % t_arg.map.width == 0);
	}
	return (NULL);
}