/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:34:33 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/04 22:25:03 by okinnune         ###   ########.fr       */
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
#  define ANIM_SCALE 0.04
# endif

/* REMOVE! */
# include <stdio.h>
# include <assert.h>

/*	KEYCODES FOR LINUX*/
# define KEY_LEFT 65361
# define KEY_RGHT 65363
# define KEY_DOWN 65364
# define KEY_UP 65362
# define KEY_Z 122
# define KEY_X 120
# define KEY_ESC 53
/*	OTHER DEFINES	*/
# define Z_CLRMASK 0xFF
# define Z_HGHTMASK 0xFF00
# define Z_CLRMUL 1
# define Z_SCALE 0.05
//# define GLOBAL_Z 
# define USAGE_MSG "ARROW KEYS = ROTATE VIEW, Z/X = INCREASE Z DEPTH"
# define WSZ 720
# define IMAGE_Y 50
/* Max number of points the map can have */
# define MAPSIZE_MAX 64000
# define INT_MAX 2147483647
# define PI 3.14159265359
# define TRI_RES 512
# define X 0
# define Y 1
# define Z 2

/*	STRUCTS */
typedef struct s_map
{
	float	**points;
	int		length;
	int		z_extreme;
	int		width;
}	t_map;

typedef struct s_tri_map
{
	float	***tri_list;
	int		tri_count;
	int		dimensions[2];
	int		z_extreme;
}	t_tri_map;

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
	int		*depthlayer;
	long	*tri_64s;
	float	scaler;
	int		tri_count;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image_info;

# ifdef EXTRA

typedef struct s_mlx_info
{
	void				*mlx;
	void				*win;
	double				x_angle;
	double				y_angle;
	double				z_scale;
	t_image_info		*img;
	t_tri_map			*tri_maps;f
	//t_map				*maps;
	int					wireframe_toggle;
	struct timeval		t1;
	double				time;
}	t_mlx_i;
# else

typedef struct s_mlx_info
{
	void				*mlx;
	void				*win;
	double				x_angle;
	double				y_angle;
	double				z_scale;
	t_image_info		*img;
	t_tri_map			*maps;
	int					wireframe_toggle;
}	t_mlx_i;
# endif

/* TODO: Name */
void	map_to_tri_map(t_map *map, t_tri_map *trimap);

/* LOOPS.C */
int		loop(void *p);
int		key_loop(int keycode, void *p);

/* VECTORS.C */
float	*v3new(float x, float y, float z);
void	v3add(float *v3, float *add);
void	v3mul(float matrix[3][3], float *v3);
void	v3listmul(float matrix[3][3], float **v3s, int len);
void	v3listadd(float **v3s, float *add, int len);

/*	FILE_MAPPING */
void	read_inputmap(char *filename, t_tri_map *map);
void	read_mapnode(int fd, char *buf, int *result, int negative_flag);

/* BRESENHAM.C */
void	populate_bresenham(t_bresenham *b, int *from, int *to);
void	step_bresenham(t_bresenham *b, int target[3]);
void	step_bresenham_x(t_bresenham *b, int target[3]);
void	step_bresenham_y(t_bresenham *b, int target[3]);

/* MATRICES.C */
void	scale_with_size_matrix(t_tri_map *map, double z_scale);
void	scale_with_x_matrix(t_tri_map *map, double angle);
void	scale_with_y_matrix(t_tri_map *map, double angle);
void	scale_with_global_z(t_map *map);

/* MAP_OPERATIONS.C */
void	animate_map(t_map *map, double time);
void	preprocess_map(t_tri_map *map, t_mlx_i i);
void	cpy_map(t_tri_map *src, t_tri_map *dst);

/* DRAWING.C */
void	draw_line_img(int *i1, int *i2, char *addr, t_image_info img);
void	fill_tri(int tris[3][3], char *addr, t_image_info img);

/* THREADING.C */
void	draw_img_from_tri64s(t_image_info img);
void	draw_img_from_trimap(t_tri_map map, t_image_info img);

/* Z_BUFFER.C */
void	apply_z_from_depth(t_tri_map *map, int *depthlayer);
void	depth_save(t_tri_map *map, t_image_info *img, int shift);
int		calc_face_color(int *depthlayer, int index, int width);

/* SORTING.C */
void		sort_tris(int tris[3][3]);
void		sorted_tri64s(t_tri_map *map, t_tri_map *orig, t_image_info *img);

/* FREEDOM.C */
void	free_maps(t_map *map);

#endif