/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:04:33 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/19 17:24:12 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 8
# include	<unistd.h>
# include	<stdlib.h>
# include	"libft.h"

int			ft_get_next_line(const int fd, char **line);

/* 't_buffer->read' represents the read string length,
not size of the buffer including null terminator */

typedef struct s_buffer
{
	char		*string;
	size_t		size;
	size_t		read;
}	t_buffer;

#endif