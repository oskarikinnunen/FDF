/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VECTEST.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 06:22:15 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/22 10:44:11 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "libft_vectors.h"
#include <stdlib.h>
#include <string.h>

int main() {
	// Write C code here
	printf("Hello world");

    char    *vec = ft_vecnew(sizeof(char));
    printf("size of content SHOULD be %lu \n", sizeof(int));
    ft_vecadd((void **)&vec, 123);
    printf("content 0 of vector %i \n", vec[0]);
	//ft_vecadd((void **)&vec, 125);
	printf("AA content 0 of vector %i \n", vec[0]);
	//printf("AA content 1 of vector %i \n", vec[1]);
	ft_vecadd((void **)&vec, 2);
	//ft_vecadd((void **)&vec, 127);
	//ft_vecadd((void **)&vec, 199);
	//printf("AAA content 0 of vector %i \n", vec[0]);
	//printf("AAA content 1 of vector %i \n", vec[1]);
	//printf("AAA content 2 of vector %i \n", vec[2]);
	//printf("AAA content 3 of vector %i \n", vec[3]);
	//printf("AAA content 4 of vector %i \n", vec[4]);
	ft_vecfree((void**)&vec);
	//free(vec);
	system("leaks a.out");
	return 0;
}