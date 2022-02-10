/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:25:44 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/10 13:03:50 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


float m[3][3] =
{
	{1,	0, 0},
	{0, 0.903, -0.4281},
	{0, 0.4281, 0.903}
};

float m2[3][3] =
{
	{0.5253,	0, -0.8509},
	{0, 1, 0},
	{0.8509, 0, 0.5253}
};

float m3[3][3] =
{
	{1.73 * 0.4, 0, -1.73 * 0.4},
	{1* 0.4, 2* 0.4, 1* 0.4},
	{1.41* 0.4, -1.41* 0.4, 1.41* 0.4}
};

float mr[3][3] =
{
	{1,	0, 0},
	{0.3, 1, 0.3/*0.81, 0.57*/},
	{0, -0.57, -0.81}
};

float mr2[3][3] =
{
	{0.71,	0, -0.70},
	{0, 1, 0},
	{0.70, 0, 0.71}
};

/*float mr3[3][3] =
{
	{1.73 * 0.4, 0, -1.73 * 0.4},
	{1* 0.4, 2* 0.4, 1* 0.4},
	{1.41* 0.4, -1.41* 0.4, 1.41* 0.4}
};*/

float fnlr[3][3] =
{
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
};

float fnl[3][3] =
{
	{1.5253, 0, 0},
	{0, 1, 0},
	{0, 0, 0.4}
};

float scale[3][3] =
{
	{22, 0, 0},
	{0, 22, 0},
	{0, 0, -3}
};

void	c_readcommands(t_mlx_i *i)
{
	static	char *command;
	char	str[2];
	int		com_index;

	if (command == NULL)
		command = ft_strnew(100);
	mlx_clear_window(i->mlx, i->win);
	if (ft_isalnum(i->key) || ft_isspace(i->key))
	{
		str[0] = ft_toupper(i->key);
		str[1] = '\0';

		command = ft_strncat(command, str, 100);
		printf("c string = %s\n", command);
	}
	if (i->key == KEY_ENTER)
	{
		com_index = 0;
		while (i->cmds[com_index] != NULL)
		{
			if (ft_strcmp(command, i->cmds[com_index]->str) == 0) {
				i->curcmd = i->cmds[com_index];
				i->curcmd->function(i);
			}
			com_index++;
		}
		command[0] = '\0';
	}
	if (i->key == 65288)
		command[ft_strlen(command) - 1] = '\0';
	if (i->key== 0xFF1B)
		command[0] = '\0';
	
	drawstr(*i, command, 10, 10);
}

void	preprocess_points(t_v3list *points)
{
	v3mul_list(scale, points);
	v3addx_list(120, points);
	v3addy_list(200, points);
	v3mul_list(mr, points);
	v3addx_list(600, points);
}

/*t_v3	*collect_edges(t_v3 *l)
{
	t_v3	edges[4];

	edges[0] = l[0];
	edges[1] = l[1];
	edges[2] = l[19];
	edges[3] = l[20];
	return (edges);
}*/

void	draw_points(t_mlx_i i)
{
	t_v3list	lst;
	int			cur;
	t_v3		edges[4];

	lst = *(read_input("input"));
	preprocess_points(&lst);
	cur = 0;
	while (cur + 20 < lst.length)
	{
		t_v3 *l = lst.list;
		if ((cur + 1) % 19 == 0)
		{
			cur++;
			continue ;
		}
		//edges = collect_edges(&(l[cur]));
		edges[0] = l[cur];
		edges[1] = l[cur + 1];
		edges[2] = l[cur + 19];
		edges[3] = l[cur + 20];
		drawlinec(edges[0], edges[1], i, INT_MAX);
		drawlinec(edges[0], edges[2], i, INT_MAX);
		drawlinec(edges[2], edges[3], i, INT_MAX);
		drawlinec(edges[1], edges[3], i, INT_MAX);
		drawlinefill(edges, i, 1);
		//drawlinec(lst.list[cur + 1], lst.list[cur + 20],  i, INT_MAX);
		//drawlinec(lst.list[cur + 19], lst.list[cur + 20],  i, INT_MAX);
		//drawlinec(p, lst.list[cur + 19], i, INT_MAX);
		cur++;
	}
}

void	c_modmatrix(t_mlx_i *i)
{
	static float	w_x;
	static int		shift_mode;
	static int		mpos[2];
	//static int	w_y;

	mlx_clear_window(i->mlx, i->win);
	drawstr(*i, "LEFT AND RIGHT ARROW KEYS = MODIFY VALUE, SHIFT = MODIFY MATRIX POSITION", 10, 10);
	shift_mode += (i->key == KEY_LEFTSHIFT) * (shift_mode == 0);
	if (shift_mode == 1)
	{
		mpos[0] += -(i->key == KEY_LEFT) + (i->key == KEY_RGHT);
		mpos[1] += -(i->key == KEY_UP)	+ (i->key == KEY_DOWN);
		drawstr(*i, "USE ARROW KEYS TO SELECT MATRIX POSITION TO EDIT", 10, 80);
		drawstr(*i, ft_itoa(mpos[0] + 1), 10, 94);
		drawstr(*i, ".", 20, 94);
		drawstr(*i, ft_itoa(mpos[1] + 1), 30, 94);
		w_x == 0.0f;
		shift_mode -= (i->key == KEY_ENTER);
	}
	if (shift_mode == 0) {
		if (w_x == 0.0f)
		w_x = mr[mpos[0]][mpos[1]];
		w_x += (float)(-(i->key == KEY_LEFT) + (i->key == KEY_RGHT)) * 0.1f;
		mr[mpos[0]][mpos[1]] = w_x;
	}
	debug_matrix(mr, *i);
	draw_points(*i);
	w_x = mr[mpos[0]][mpos[1]];
}

void	c_addbutton(t_mlx_i *i)
{
	static int	w_x;
	static int	w_y;

	mlx_clear_window(i->mlx, i->win);
	drawstr(*i, "USE ARROW KEYS TO RESIZE BUTTON", 10, 10);
	//printf("KEY PUSHED %i\n", key);
	w_x += -(i->key == KEY_LEFT) + (i->key == KEY_RGHT);
	w_y += -(i->key == KEY_UP)	+ (i->key == KEY_DOWN);
	drawstr(*i, ft_itoa(w_x), 10, 25);
	drawstr(*i, ft_itoa(w_y), 10, 40);
}

void	get_commands(t_mlx_i *i)
{
	//t_command	***cmds;

	i->cmds = malloc(sizeof(t_command *) * 3);
	i->cmds[0] = malloc(sizeof(t_command));
	i->cmds[0]->str = "PROMPT";
	i->cmds[0]->function = c_readcommands;
	i->cmds[1] = malloc(sizeof(t_command));
	i->cmds[1]->str = "ADDBUTTON";
	i->cmds[1]->function = c_addbutton;
	i->cmds[2] = malloc(sizeof(t_command));
	i->cmds[2]->str = "MODMATRIX";
	i->cmds[2]->function = c_modmatrix;
	i->cmds[3] = NULL;
}
