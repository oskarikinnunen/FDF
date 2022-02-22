/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 07:01:46 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/22 10:40:49 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vectors.h"
#include "libft.h"
#include <stdio.h>

//return ((t_vector *)(&((char *)v_address)[-80]));
t_vector	*vecdata(void *v_address)
{
	return ((t_vector *)(v_address - 80));
}

t_vector	*ft_vec_realloc(t_vector *data)
{
	t_vector	*new;
	//t_vector	*dref;

	new = (t_vector *)malloc(sizeof(t_vector));
	
	new->buff = malloc(data->alloc);
	//printf("LOCATION OF BUFF %lu\n location of new t_vector %lu\n", (size_t)new->buff, (size_t)new);
	new->alloc = data->alloc * 2;
	new->content_size = data->content_size;
	new->count = data->count;
	//printf("Allocating size for vec: %lu\n", data->alloc * 2);
	//printf("Allocating... count %lu\n", new->count);
	ft_memcpy(new->buff, data->buff, new->count * new->content_size);
	free(data->buff);
	free(data);
	return (new);
}

void	*ft_vecadd(void **v_address, size_t content)
{
	t_vector		*data;
	t_vector		**fr;
	void			*temp;
	unsigned int	sc;

	data = vecdata(*v_address);
	fr = &data;
	//printf("first data  at the start of add: %i\n", ((int *)data->buff)[0]);
	printf("ADDRESS     at the start of add: %lu\n", (size_t)data);
	printf("ADDRESSvadd at the start of add: %lu\n", (size_t)*v_address);
	printf("data->alloc at the start of add: %lu\n", data->alloc);
	printf("data->count at the start of add: %lu\n", data->count);
	printf("needed size at the start of add: %lu\n", (data->count + 1) * data->content_size);
	printf("contentsize at the start of add: %lu\n\n", data->content_size);
	if (data->alloc < (data->count + 1) * data->content_size)
	{
		temp = ft_memdup(*v_address, data->content_size * data->count);
		
		*v_address = ft_vecnew(data->alloc * 2);
		ft_memcpy(*v_address, temp, (int)data->count);
		
		free(temp);

		vecdata(*v_address)->alloc = data->alloc * 2;
		vecdata(*v_address)->content_size = 1;
		vecdata(*v_address)->count = data->count;
		free(*fr);
		data = vecdata(*v_address);
		//data = ft_vec_realloc(data);
		//*v_address = data->buff;
	}
	//data = vecdata(*v_address);
	sc = 0;
	
	ft_memcpy(*v_address + data->count, &content, data->content_size);
	/*while (sc < data->content_size)
	{
		((char *)(*v_address))[sc
			+ (vecdata(*v_address)->count)] = ((char *)&content)[sc];
		sc++;
	}*/
	vecdata(*v_address)->count += 1;
	/*printf("end of add alloc %lu \n", vecdata(*v_address)->alloc);
	printf("end of add count %lu \n", vecdata(*v_address)->count);
	printf("ADDRESS     at the END of add: %lu\n", (size_t)data);
	printf("ADDRESSvadd at the END of add: %lu\n\nXXXX\n", (size_t)*v_address);*/
	//*v_address = data->buff;
	return (NULL);
}

void	ft_vecfree(void **v_address)
{
	/*t_vector		**fr;
	t_vector		*f;

	f = vecdata(*v_address);
	fr = &f;
	free(*fr);*/
	printf("address %lu\n", (size_t)v_address);
	//free(*v_address);
	free((t_vector *)vecdata(*v_address));
}
