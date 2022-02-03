/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:34:33 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/03 14:51:39 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define FONTSIZE 2
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

enum e_command
{
	CREATE_BUTTON,
	MOVE_BUTTON
};



/*typedef struct s_wincontext
{
	t_v3	v3;
	int		click;
	char	*string;
}				t_wincontext;*/

typedef struct s_mlx_info
{
	void				*mlx;
	void				*win;
	/*t_wincontext		c;*/
	struct s_command	**cmds;
	struct s_command	*curcmd;
}			t_mlx_i;

typedef struct s_command
{
	char	*str;
	void	(*mousefunction)(int button, t_v3 pos, t_mlx_i *i);
	void	(*keyfunction)(int key, t_mlx_i *i);
	//void	(*loopfunction)(int key, t_mlx_i *i);
}				t_command;

void	drawchar(t_mlx_i i, char c, int x, int y);
void	v3mul(float matrix[3][3], t_v3 *v);
void	v3mul_list(float matrix[3][3], t_v3list *lst);
void	v3addx_list(int x, t_v3list *lst);
void	v3addy_list(int y, t_v3list *lst);
void	drawstr(t_mlx_i i, char *str, int x, int y);
int		max(int a, int b);

#endif