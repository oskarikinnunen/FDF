/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:34:33 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/19 00:05:58 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
/*	INCLUDES */
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>

# ifdef EXTRA
#  include <sys/time.h>
#  include <pthread.h>
#  define ANIM_SCALE 0.04
# endif

# include <stdio.h>
/*	KEYCODES */
# define KEY_LEFT 65361
# define KEY_RGHT 65363
# define KEY_DOWN 65364
# define KEY_UP 65362
# define KEY_ESC 53
/*	OTHER DEFINES	*/
# define Z_CLRMASK 0X7F
# define Z_CLRMUL 2

# define IMAGE_Y 50
# define WSZ 720
# define INT_MAX 2147483647
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
	int		*depthlayer;
}	t_image_info;

typedef struct s_draw_args
{
	char			*addr;
	t_map			map;
	t_image_info	img;
	int				start;
	int				stop;
}	t_draw_args;

# ifdef EXTRA

typedef struct s_mlx_info
{
	void				*mlx;
	void				*win;
	double				time;
	double				x_angle;
	double				y_angle;
	t_image_info		*img;
	t_map				*maps;
	struct timeval		t1;
	int					threads;
}	t_mlx_i;
# else

typedef struct s_mlx_info
{
	void				*mlx;
	void				*win;
	double				x_angle;
	double				y_angle;
	t_image_info		*img;
	t_map				*maps;
	int					wireframe_toggle;
}	t_mlx_i;
# endif

/* LOOPS.C */
int		loop(void *p);
int		key_loop(int keycode, void *p);

/* VECTORS.C */
float	*v3new(float x, float y, float z);
void	v3mul(float matrix[3][3], float *v3);
void	v3listmul(float matrix[3][3], float **v3s, int len);
void	v3listadd(float **v3s, float *add, int len);
void	read_inputmap(char *filename, t_map *map);

/* BRESENHAM.C */
void	populate_bresenham(t_bresenham *b, int *from, int *to);
void	step_bresenham(t_bresenham *b, int target[3]);
void	step_bresenham_x(t_bresenham *b, int target[3]);
void	step_bresenham_y(t_bresenham *b, int target[3]);

/* MATRICES.C */
void	scale_with_size_matrix(t_map *map);
void	scale_with_x_matrix(t_map *map, double angle);
void	scale_with_y_matrix(t_map *map, double angle);

/* MAP_OPERATIONS.C */
void	collect_square(float **v3, int i3[4][3], int width, int z);
void	animate_map(t_map *map, double time);
void	preprocess_map(t_map *map, t_mlx_i i);
void	cpy_map(t_map *src, t_map *dst);

/* DRAWING.C */
void	draw_line_img(int *i1, int *i2, char *addr, t_image_info img);
void	fill_tri(int tris[3][3], char *addr, t_image_info img);

/* THREADING.C */
void	threads_start(t_map map, t_image_info img, char *addr, int corecount);
void	*drawmap(void *args);

/* Z_BUFFER.C */
void	save_z(t_map *map, t_image_info *info);

/* SORTING.C */
void	sort_tris(int tris[3][3]);

/* FREEDOM.C */
void	free_map(t_map *map);

#endif