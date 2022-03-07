/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:34:33 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/07 17:14:12 by okinnune         ###   ########.fr       */
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
# include <sys/time.h>
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

typedef struct s_image_info
{
	void	*ptr;
	int		bpp;
	int		size_line;
	int		endian;
}			t_image_info;

typedef struct s_mlx_info
{
	void				*mlx;
	void				*win;
	struct timeval		t1;
	double				time;
	double				p_time;
	t_image_info		*img;
	t_map				*map;
}			t_mlx_i;

typedef struct s_command
{
	char	*str;
	void	(*function)(t_mlx_i *i);
}				t_command;

float	*v3new(float x, float y, float z);
void	v3mul(float matrix[3][3], float *v3);
void	v3listmul(float matrix[3][3], float **v3s, int len);
void	v3listadd(float **v3s, float *add, int len);
int		*v3_int(float	*v3);
void	v3_int_block(float	*v3, int *i3);
void	read_inputmap(char *filename, t_map *map);

/* DRAWING */
void	draw_line(int *i1, int *i2, t_mlx_i i, int c);
void	draw_line_img(int *i1, int *i2, char *adder, t_image_info i, int color);
int		color(char r, char g, char b);

char	*ci_data_adder(t_mlx_i *i, void **imagereturn);

int		convert_cocoakc_to_ascii_global(int kc);

#endif