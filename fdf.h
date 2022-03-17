/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:34:33 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/17 08:34:49 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
/*	INCLUDES */
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
/*	KEYCODES */
# define KEY_LEFT 65361
# define KEY_RGHT 65363
# define KEY_DOWN 65364
# define KEY_UP 65362
# define KEY_TILDE 167
# define KEY_ESC 53
# define KEY_ENTER 65293
# define KEY_LEFTSHIFT 65505
/*	OTHER DEFINES	*/
# define WSZ 720
# define X 0
# define Y 1
# define Z 2

/*	STRUCTS */
typedef struct s_map
{
	float	**points;
	int		length;
	int		width;
}	t_map;

typedef struct s_bresenham
{
	int	diff[2];
	int	add[2];
	int	local[3];
	int	error;
}	t_bresenham;

typedef struct s_image_info
{
	void	*ptr;
	int		bpp;
	int		size_line;
	int		endian;
	int		*z_values;
}	t_image_info;

typedef struct s_mlx_info
{
	void				*mlx;
	void				*win;
	struct timeval		t1;
	int					tick;
	double				time;
	double				p_time;
	double				x_angle;
	double				y_angle;
	t_image_info		*img;
	t_map				*maps;
}	t_mlx_i;

/* VECTORS.C */
float	*v3new(float x, float y, float z);
void	v3mul(float matrix[3][3], float *v3);
void	v3listmul(float matrix[3][3], float **v3s, int len);
void	v3listadd(float **v3s, float *add, int len);
void	read_inputmap(char *filename, t_map *map);

/* BRESENHAM.C */
void	pop_bresenham(t_bresenham *b, int *from, int *to);
void	step_bresenham(t_bresenham *b, int target[3]);
void	step_bresenham_x(t_bresenham *b, int target[3]);
void	step_bresenham_y(t_bresenham *b, int target[3]);

/* MATRICES.C */
void	setmatrix_scale(float matrix[3][3]);
void	setmatrix_iso_x(float matrix[3][3], double angle);
void	setmatrix_iso_y(float matrix[3][3], double angle);

/* MAP_OPERATIONS.C */
void	map_animate(t_map *map, double time);
void	map_preprocess(t_map *map, t_mlx_i i);
void	map_to_image(char *da, t_map map, t_image_info img);
void	map_cpy(t_map *src, t_map *dst);

/* DRAWING.C */
void	draw_line_img(int *i1, int *i2, char *addr, t_image_info img);
void	fill_tri(int tris[3][3], char *addr, t_image_info img);

/* Z_BUFFER.C */
void	save_z(t_map *map, t_image_info *info, int index);

/* SORTING.C */
void	sort_tris(int tris[3][3]);

/* FREEDOM.C */
void	free_map(t_map *map);

#endif