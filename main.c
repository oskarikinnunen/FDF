/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/24 03:15:41 by okinnune         ###   ########.fr       */
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
		return (0);
	printf("KEYPRESS %i\n", i->key);
	i->key = convert_cocoakc_to_ascii_global(i->key);
	printf("Converted to ascii: %i\n", i->key);
	if (i->key == KEY_TILDE)
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

int	main(int argc, char **argv)
{
	t_mlx_i		i;

	if (argc != 2)
		return (-1);
	i.mlx = mlx_init();
	i.win = mlx_new_window(i.mlx, WSZ, WSZ, "new_window");
	i.curcmd = NULL;
	get_commands(&i);
	mlx_mouse_hook(i.win, mouse_win1, &i);
	mlx_key_hook(i.win, keystroke, &i);
	mlx_loop_hook(i.mlx, context_loop, &i);
	mlx_loop(i.mlx);
	return (0);
}
