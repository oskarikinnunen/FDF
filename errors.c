/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:02:57 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/06 17:21:41 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_exit(char *str)
{
	ft_putendl_fd("ERROR: ", 2);
	ft_putendl_fd(str, 2);
	ft_putendl_fd("EXITING PROGRAM", 2);
	exit(-1);
}
