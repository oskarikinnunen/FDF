/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:02:57 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/14 21:37:04 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_exit(char *str)
{
	ft_putendl_fd("ERROR: ", 2);
	ft_putendl_fd(str, 2);
	ft_putendl_fd("EXITING PROGRAM", 2);
	//system("leaks FDF");
	exit(0);
}
