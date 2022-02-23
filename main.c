/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/23 05:43:01 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fdf.h"
#include "libft/libft.h"
//#include <mlx_int.h>

int	mouse_win1(int button, int x, int y, void *p)
{
	t_mlx_i	*i;

	i = (t_mlx_i *)p;
	i->m_x = x;
	i->m_y = y;
	i->m_b = button;
}

int	context_loop(void *p)
{
	t_mlx_i	*i;

	i = (t_mlx_i *)p;
	if (i->key == -1)
		return 0;
	printf("KEYPRESS %i\n", i->key);
	i->key = convert_cocoakc_to_ascii_global(i->key);
	printf("Converted to ascii: %i\n", i->key);
	if (i->key == KEY_TILDE || i->key == KEY_TILDE_OSX)
		i->curcmd = i->cmds[0];
	if (i->curcmd != NULL && i->key != -1)
		i->curcmd->function(i);
	i->key = -1;
	return (1);
}

int	keystroke(int key, void *p)
{
	t_mlx_i	*i;

	i = (t_mlx_i *)p;
	i->key = key;
}

t_list	*read_input(char *filename)
{
	int			res;
	int			fd;
	char		buf[1];
	int			crds[2];
	int			cur;
	t_list		*vlist;
	float		*v3;

	fd = open(filename, O_RDONLY);
	ft_bzero(crds, sizeof(int) * 2);
	vlist = NULL;
	cur = 0;
	while ((res = read(fd, buf, 1)) == 1)
	{
		if (*buf == '\n' || *buf == '\t')
		{
			if (*buf == '\n')
			{
				crds[Y]++;
				crds[X] = 0;
			}
			continue;
		}
		v3 = v3new(crds[X], crds[Y], (float)(*buf - '0'));
		printf("v3 content x: %f y: %f z: %f \n", v3[0], v3[1], v3[2]);
		if (vlist == NULL)
			vlist = ft_lstnew(v3, sizeof(float *) * 3);
		else
			ft_lstapp(&vlist, ft_lstnew(v3, V3SIZE));
		crds[X]++;
		cur++;
		printf("CUR vlist content %f \n", ((float *)vlist->content)[X]);
		printf("CUR READINPUT %i \n", cur);
	}
	return (vlist);
}

int	main(int argc, char **argv)
{
	t_mlx_i 	i;
	void		*mlx;
	void		*win;
	void		*cmdimage;
	void		*image;
	
	if (argc != 2)
		return (-1);
	mlx = mlx_init();
	win = mlx_new_window(mlx, WSZ, WSZ, "new_window");
	i.mlx = mlx;
	i.win = win;
	i.curcmd = NULL;
	//mlx_new_image(mlx, WSZ, WSZ / 2);
	get_commands(&i);
	mlx_mouse_hook(win,mouse_win1,&i);
	mlx_key_hook(win,keystroke,&i);
	mlx_loop_hook(mlx, context_loop, &i);
	mlx_loop(mlx);
	return (0);
}
