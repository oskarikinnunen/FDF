/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:34:33 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/25 14:32:12 by okinnune         ###   ########.fr       */
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

/* REMOVE! */
# include <stdio.h>

/*	KEYCODES */
# define KEY_LEFT 65361
# define KEY_RGHT 65363
# define KEY_DOWN 65364
# define KEY_UP 65362
# define KEY_ESC 53
/*	OTHER DEFINES	*/
# define Z_CLRMASK 0xFF
# define Z_HGHTMASK 0xFF00
# define Z_CLRMUL 1
# define Z_SCALE 0.05
# define USAGE_MSG "ARROW KEYS = ROTATE VIEW"
# define IMAGE_Y 50
# define WSZ 500
/* Max number of points the map can have */
# define MAPSIZE_MAX 100000
# define INT_MAX 2147483647
# define PI 3.14159265359
# define X 0
# define Y 1
# define Z 2

/*	STRUCTS */
typedef struct s_map
{
	float	**points;
	int		tri_count;
	int		length;
	int		width;
}	t_map;

typedef struct s_bresenham
{
	int	diff[3];
	int	add[3];
	int	local[3];
	int	error;
}	t_bresenham;

typedef struct s_image_info
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	long	*tri_64s;
	int		*depthlayer;
}	t_image_info;

typedef struct s_draw_args
{
//	char			*addr;
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

/*	FILE_MAPPING */
void	read_inputmap(char *filename, t_map *map);
void	read_mapnode(int fd, char *buf, int *result, int negative_flag);

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
void	threads_start(t_map map, t_image_info img, int corecount, void (*func)(void *));
void	*draw_map(void *args);
void	*draw_map_from_tri64s(void *draw_args);

/* Z_BUFFER.C */
void	collect_face_z_pass(float **v3, int i3[4][3], int width);
void	depth_save(t_map *map, t_image_info *img, int mask);
int		calc_face_color(int *depthlayer, int index, int width);

/* SORTING.C */
void		sort_tris(int tris[3][3]);
long int	*sorted_tri64s(t_map *map, t_image_info *img);

/* FREEDOM.C */
void	free_maps(t_map *map);

#endif