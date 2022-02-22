/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 04:11:27 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/22 08:55:40 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vectors.h"
#include "libft.h"
#include <stdio.h>

//Allocates a new vector!
void	*ft_vecnew(size_t size)
{
	t_vector	*vecptr;

	vecptr = (t_vector *)malloc(sizeof(t_vector));
	//printf("location of vecptr malloc %lu \n", (size_t)vecptr);
	vecptr->content_size = size;
	vecptr->buff = ft_memalloc(size);
	vecptr->alloc = size;
	vecptr->count = 0;
	return (vecptr->buff);
}
