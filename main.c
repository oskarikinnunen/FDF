/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/10 14:35:58 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fdf.h"
#include "libft/libft.h"
#define WSZ 1200
//#include <mlx_int.h>

void	v3set(int x, int y, int z, t_v3 *v)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

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
	if (i->key == 0)
		return 0;
	printf("KEYPRESS %i\n", i->key);
	if (i->key == KEY_TILDE)
		i->curcmd = i->cmds[0];
	if (i->curcmd != NULL && i->key != 0)
		i->curcmd->function(i);
	i->key = 0;
}

int	keystroke(int key, void *p)
{
	t_mlx_i	*i;

	i = (t_mlx_i *)p;
	i->key = key;
}

t_v3list	*read_input(char *filename)
{
	int			res;
	int			fd;
	char		buf[1];
	int			x;
	int			y;
	int			cur;
	t_v3list	*resv;

	fd = open(filename, O_RDONLY);
	resv = malloc(sizeof(t_v3list));
	resv->list = malloc(sizeof(t_v3) * 1000);
	x = 0;
	y = 0;
	cur = 0;
	while ((res = read(fd, buf, 1)) == 1)
	{
		if (*buf == '\n' || *buf == '\t')
		{
			if (*buf == '\n')
			{
				y++;
				x = 0;
			}
			continue;
		}
		resv->list[cur].x = x;
		resv->list[cur].y = y;
		resv->list[cur].z = *buf - '0';
		x++;
		cur++;
	}
	resv->length = cur;
	return (resv);
}

int	main(int argc, char **argv)
{
	t_mlx_i 	i;
	void		*mlx;
	void		*win;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, WSZ, WSZ, "new_window");
	i.mlx = mlx;
	i.win = win;
	i.curcmd = NULL;
	get_commands(&i);

	if (argc != 2)
		return (-1);

	//int value = 69;
	mlx_mouse_hook(win,mouse_win1,&i);
	mlx_key_hook(win,keystroke,&i);
	mlx_loop_hook(mlx, context_loop, &i);

	mlx_loop(mlx);
	return (0);
}
