/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_vectors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 05:05:34 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/22 10:27:56 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTORS_H
# define FT_VECTORS_H
# include <string.h>

typedef struct s_vector
{
	void	*buff;
	size_t	alloc;
	size_t	count;
	size_t	content_size;
}	t_vector;

void	*ft_vecnew(size_t size);
void	*ft_vecadd(void **v_address, size_t content);
void	ft_vecfree(void **v_address);

#endif