/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:23:38 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/17 11:32:14 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <pthread.h>

void	*thread_bzero(void *args)
{
	t_thread_args t_arg;

	t_arg = *(t_thread_args *)args;
	ft_bzero(t_arg.addr, t_arg.count);
	return (NULL);
}