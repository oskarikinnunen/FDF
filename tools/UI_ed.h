/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI_ed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 19:55:46 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/08 20:03:37 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_ED_H
# define UI_ED_H

# if defined(__APPLE__)
#  include <mlx.h>
# elif defined (__unix__)
#  include "../mlx/Linux/mlx.h"
# endif

# define WSZ 1200

typedef struct s_mlx_info
{
	void				*mlx;
	void				*win;
	void				*img;
}			t_mlx_i;

#endif