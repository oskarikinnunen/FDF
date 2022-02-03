/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:55:54 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/03 15:20:36 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fdf.h"
#include "libft/libft.h"
#define WSZ 1200
//#include <mlx_int.h>

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

int	color(char r, char g, char b)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (i < 8)
	{
		c ^= (((1 << i & r) != 0)) << i + 16;
		c ^= (((1 << i & g) != 0)) << i + 8;
		c ^= (((1 << i & b) != 0)) << i;
		i++;
	}
	return (c);
}

void	v3set(int x, int y, int z, t_v3 *v)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

int	mouse_win1(int button,int x,int y, void *p)
{
	t_mlx_i	*i;
	t_v3	pos;

	i = (t_mlx_i *)p;
	pos.x = x;
	pos.y = y;
	if (i->curcmd->mousefunction != NULL)
	{
		i->curcmd->mousefunction(button, pos, i);
	}
	/*i->c.v3.x = x;
	i->c.v3.y = y;
	i->c.click = button;*/
	//printf("Mouse in Win1, button %d at %dx%d. c = %i\n",button,x,y, *((int *)p));
	//drawstr(*((t_mlx_i *)p), "Size X: comma, Size Y=\"equal\"", x, y);
}

int	context_loop(void *p)
{
	/*static	int framecount;
	t_mlx_i	*i;

	i = (t_mlx_i *)p;
	if (framecount == 10000)
	{
		mlx_clear_window(i->mlx, i->win);
		drawstr(*i, i->c.string, 10, 10);
		drawchar(*i, '|', 10 + ((ft_strlen(i->c.string)) * (FONTSIZE * 6)), 10);

		drawchar(*i, '|', i->c.v3.x, i->c.v3.y);
		framecount = 0;
	}
	if (i->curcmd != NULL)
	{
		(*i->curcmd->function)(i);
	}
	framecount++;
	i->c.click = 0;*/
}

int	keystroke(int key,void *p)
{
	t_mlx_i	*i;

	i = (t_mlx_i *)p;
	if (key == 167)
		i->curcmd = i->cmds[0];
	
	if (i->curcmd != NULL)
		(*i->curcmd->keyfunction)(key, i);
	/*if (ft_isalnum(key) || ft_isspace(key))
	{
		str[0] = ft_toupper(key);
		str[1] = '\0';

		i->c.string = ft_strncat(i->c.string, str, 100);
		
		printf("c string = %s\n", i->c.string);
	}
	if (key == 65288)
		i->c.string[ft_strlen(i->c.string) - 1] = '\0';*/

	/*if (key == 65293)
	{
		if (ft_strcmp(i->c.string, i->cmds->str) == 0)
		{
			//printf("CREATEBUTTON!");
			i->c.string[0] = '\0';
			(*i->cmds->function)(i);
			i->curcmd = i->cmds;
			//ft_strncat(i->c.string, , 100);
		}
	}*/
	/*if (key==0xFF1B)
		i->c.string[0] = '\0';*/
		//exit(0);
}

void	drawline(t_v3 p1, t_v3 p2, t_mlx_i i)
{
	t_v3	diff;
	t_v3	add;
	int		error;

	diff.x = ft_abs(p1.x - p2.x);
	diff.y = -ft_abs(p1.y - p2.y);
	add.x = 1 - ((p1.x > p2.x) * 2);
	add.y = 1 - ((p1.y > p2.y) * 2);
	error = diff.x + diff.y;
	while (1)
	{
		mlx_pixel_put(i.mlx, i.win, p1.x, p1.y, color(255, 120, 120));
		if ((int)p1.x == (int)p2.x && (int)p1.y == (int)p2.y)
			break ;
		if (error * 2 >= diff.y)
		{
			error += (p1.x != p2.x) * diff.y;
			p1.x += (p1.x != p2.x) * add.x;
		}
		if (error * 2 <= diff.x)
		{
			error += (p1.y != p2.y) * diff.x;
			p1.y += (p1.y != p2.y) * add.y;
		}
	}
}

void	drawlinec(t_v3 p1, t_v3 p2, t_mlx_i i, int c)
{
	t_v3	diff;
	t_v3	add;
	t_v3	local;
	int		error;

	//p1.x = max(0, p1.x);
	//p1.y = max(0, p1.y);
	local.x = (int)p1.x;
	local.y = (int)p1.y;
	local.z = (int)p1.z;
	diff.x = ft_abs(local.x - (int)p2.x);
	diff.y = -ft_abs(local.y - (int)p2.y);
	add.x = 1 - ((local.x > (int)p2.x) * 2);
	add.y = 1 - ((local.y > (int)p2.y) * 2);
	
	error = diff.x + diff.y;
	while (1)
	{
		mlx_pixel_put(i.mlx, i.win, (int)local.x, (int)local.y, color(local.z - p2.z, 255, 255));
		//printf("drawpixel %f, %f. error %i addx %f addy %f diffx %f diffy %f\n", local.x, local.y, error, add.x, add.y, diff.x, diff.y);
		if (((int)local.x == (int)p2.x && (int)local.y == (int)p2.y))
			break ;
		//if (local.x)
		//	break ;
		if (error * 2 >= (int)diff.y)
		{
			error += (int)(((int)local.x != (int)p2.x) * (int)diff.y);
			local.x += (int)(((int)local.x != (int)p2.x) * add.x);
		}
		if (error * 2 <= (int)diff.x)
		{
			error += (int)(((int)local.y != (int)p2.y) * diff.x);
			local.y += (int)(((int)local.y != (int)p2.y) * add.y);
		}
	}
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

void	addbuttoncommand(int key, t_mlx_i *i)
{
	static t_v3 pos;

	mlx_clear_window(i->mlx, i->win);
	drawstr(*i, "USE ARROW KEYS TO RESIZE BUTTON", 10, 10);
	printf("KEY PUSHED %i\n", key);
	pos.x += -(key == 65361) + (key == 65363);
	pos.y += -(key == 65362) + (key == 65364);
	drawstr(*i, ft_itoa((int)pos.x), 10, 25);
	drawstr(*i, ft_itoa((int)pos.y), 10, 40);
}

void	addbuttonmcommand(int button, t_v3 pos, t_mlx_i *i)
{
	drawstr(*i, "X", pos.x, pos.y);
}

void	readcommand(int key, t_mlx_i *i)
{
	static	char *command;
	char	str[2];
	int		com_index;

	if (command == NULL)
		command = ft_strnew(100);
	mlx_clear_window(i->mlx, i->win);
	if (ft_isalnum(key) || ft_isspace(key))
	{
		str[0] = ft_toupper(key);
		str[1] = '\0';

		command = ft_strncat(command, str, 100);
		printf("c string = %s\n", command);
	}
	if (key == 65293)
	{
		com_index = 0;
		while (i->cmds[com_index] != NULL)
		{
			if (ft_strcmp(command, i->cmds[com_index]->str) == 0) {
				i->curcmd = i->cmds[com_index];
				i->curcmd->keyfunction(key, i);
			}
			com_index++;
		}
		command[0] = '\0';
	}
	if (key == 65288)
		command[ft_strlen(command) - 1] = '\0';
	if (key==0xFF1B)
		command[0] = '\0';
	
	drawstr(*i, command, 10, 10);
}

int	main(int argc, char **argv)
{
	t_mlx_i 	i;
	void		*mlx;
	void		*win;
	t_v3list	lst;
	int			cur;
	t_command	c_read;
	t_command	c_addbutton;

	c_read.str = "PROMPT";
	c_read.keyfunction = readcommand;
	c_read.mousefunction = NULL;
	c_addbutton.str = "ADDBUTTON";
	c_addbutton.keyfunction = addbuttoncommand;
	c_addbutton.mousefunction = addbuttonmcommand;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, WSZ, WSZ, "new_window");
	i.mlx = mlx;
	i.win = win;
	//i.c = malloc(sizeof(t_wincontext));
	//i.c.string = ft_strnew(100);
	i.cmds = malloc(sizeof(t_command *) * 3);
	i.cmds[0] = &c_read;
	i.cmds[1] = &c_addbutton;
	i.cmds[2] = NULL;
	i.curcmd = NULL;
	//printf("CONTEXT STRING %s\n", i.c->string);

	if (argc != 2)
		return (-1);
	lst = *(read_input(argv[1]));

	cur = 0;
	
	v3mul_list(scale, &lst);
	v3addx_list(120, &lst);
	v3addy_list(200, &lst);
	
	//
	v3mul_list(mr2, &lst);
	v3mul_list(mr, &lst);
	//v3mul_list(m3, &lst);
	v3mul_list(fnl, &lst);

	v3addx_list(600, &lst);
	
	int reset = 1;
	while (cur + 20 < lst.length)
	{
		t_v3 p = lst.list[cur];
		if (reset % 19 == 0)
		{
			reset = 1;
			cur++;
			continue ;
		}
		drawlinec(p, lst.list[cur + 1], i, INT_MAX);
		drawlinec(p, lst.list[cur + 19], i, INT_MAX);
		reset++;
		cur++;
	}
	//int value = 69;
	mlx_mouse_hook(win,mouse_win1,&i);
	mlx_key_hook(win,keystroke,&i);
	mlx_loop_hook(mlx, context_loop, &i);

	mlx_loop(mlx);
	return (0);
}
