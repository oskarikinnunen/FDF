/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:34:33 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/24 03:17:58 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define FONTSIZE 2
# define WSZ 1200

/* Maybe use enum for these? */
# define KEY_LEFT 65361
# define KEY_RGHT 65363
# define KEY_DOWN 65364
# define KEY_UP 65362
# define KEY_TILDE 167
# define KEY_ENTER 65293
# define KEY_LEFTSHIFT 65505

# define DEBUG_MW 60
# define X 0
# define Y 1
# define Z 2
# define V3SIZE sizeof(float *) * 3
# include "libft/libft.h"
# if defined(__APPLE__)
#  include <mlx.h>
# elif defined (__unix__)
#  include "mlx/Linux/mlx.h"
# endif
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

typedef struct s_map
{
	float	**points;
	int		length;
	int		width;
}	t_map;

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

typedef struct s_image_info
{
	int	bpp;
	int	size_line;
	int	endian;
}			t_image_info;

typedef struct s_command
{
	char	*str;
	void	(*function)(t_mlx_i *i);
}				t_command;

float	*v3new(float x, float y, float z);
void	v3mul(float matrix[3][3], float *v3);
void	v3mul_list(float matrix[3][3], t_v3list *lst);
void	v3addx_list(int x, t_v3list *lst);
void	v3addy_list(int y, t_v3list *lst);
void	drawstr(t_mlx_i i, char *str, int x, int y);
int		max(int a, int b);

/* COMMANDS */
void		get_commands(t_mlx_i *i);
void		c_readcommands(t_mlx_i *i);
void		c_addbutton(t_mlx_i *i);

void		read_inputmap(char *filename, t_map *map);

/* DRAWING */
void	drawlinefill(t_v3 *points, t_mlx_i i, int c);
void	drawlinec(t_v3 p1, t_v3 p2, t_mlx_i i, int c);
void	drawline_toimage(t_v3 p1, t_v3 p2, char *img, int c);
void	drawline(t_v3 p1, t_v3 p2, t_mlx_i i);
void	drawchar(t_mlx_i i, char c, int x, int y);
void	debug_matrix(float m[3][3], t_mlx_i i);
int		color(char r, char g, char b);

char	*ci_data_adder(t_mlx_i *i, void **imagereturn);

int		convert_cocoakc_to_ascii_global(int kc);

#endif