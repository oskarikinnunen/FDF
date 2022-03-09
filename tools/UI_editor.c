/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI_editor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 19:54:32 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/08 20:07:39 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UI_ed.h"
#include <stdio.h>

int	mouse_loop(int button, int x, int y, void *p)
{
	printf("button %i\n", x);
}

int	main(int argc, char **argv)
{
	t_mlx_i			i;

	i.mlx = mlx_init();
	i.win = mlx_new_window(i.mlx, WSZ, WSZ, "new_window");
	//preprocess(&map); // Move this elsewhere!
	i.img = mlx_new_image(i.mlx, WSZ, WSZ);
	//preprocess_return(&map);

	//mlx_loop_hook(i.mlx, loop, &i);
	mlx_mouse_hook(i.win, mouse_loop, &i);
	mlx_loop(i.mlx);
	return (0);
}
