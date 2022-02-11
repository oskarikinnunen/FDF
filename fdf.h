/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:34:33 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/11 17:05:19 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define FONTSIZE 2

/* Maybe use enum for these? */
# define KEY_LEFT 65361
# define KEY_RGHT 65363
# define KEY_DOWN 65364
# define KEY_UP 65362
# define KEY_TILDE 167
# define KEY_TILDE_OSX 10
# define KEY_ENTER 65293
# define KEY_LEFTSHIFT 65505

# define DEBUG_MW 50
# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_v3
{
	float	x;
	float	y;
	float	z;
}				t_v3;

typedef struct s_v3list
{
	t_v3	*list;
	size_t	length;
}				t_v3list;

typedef struct s_mlx_info
{
	void				*mlx;
	void				*win;
	int					m_x;
	int					m_y;
	int					m_b;
	int					key;
	struct s_command	**cmds;
	struct s_command	*curcmd;
}			t_mlx_i;

typedef struct s_command
{
	char	*str;
	void	(*function)(t_mlx_i *i);
}				t_command;

void	v3mul(float matrix[3][3], t_v3 *v);
void	v3mul_list(float matrix[3][3], t_v3list *lst);
void	v3addx_list(int x, t_v3list *lst);
void	v3addy_list(int y, t_v3list *lst);
void	drawstr(t_mlx_i i, char *str, int x, int y);
int		max(int a, int b);

/* COMMANDS */
void		get_commands(t_mlx_i *i);
void		c_readcommands(t_mlx_i *i);
void		c_addbutton(t_mlx_i *i);

t_v3list	*read_input(char *filename);

/* DRAWING */
void	drawlinefill(t_v3 *points, t_mlx_i i, int c);
void	drawlinec(t_v3 p1, t_v3 p2, t_mlx_i i, int c);
void	drawline(t_v3 p1, t_v3 p2, t_mlx_i i);
void	drawchar(t_mlx_i i, char c, int x, int y);
void	debug_matrix(float m[3][3], t_mlx_i i);

int		convert_cocoakc_to_ascii_global(int kc);

#endif