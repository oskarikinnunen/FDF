/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 19:37:23 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/19 16:13:12 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
LINE 27: If s_buf->size is 0, make it BUFF_SIZE + 1,
		 otherwise multiply it by 2
*/

static int	append_to_buff(t_buffer **s_buf, char *str, size_t len)
{
	char		*cpy;

	cpy = NULL;
	if ((*s_buf)->read + len + 1 > (*s_buf)->size)
	{
		(*s_buf)->size = ((*s_buf)->size == 0) * (BUFF_SIZE + 1)
			+ (*s_buf)->size * 2;
		if ((*s_buf)->string != NULL)
		{
			cpy = ft_strdup((*s_buf)->string);
			if (cpy == NULL)
				return (-1);
			ft_strdel(&((*s_buf)->string));
		}
		(*s_buf)->string = (char *)ft_memalloc((*s_buf)->size);
		if ((*s_buf)->string == NULL)
			return (-1);
		if (cpy != NULL)
			ft_memcpy((*s_buf)->string, cpy, (*s_buf)->size / 2);
		ft_strdel(&cpy);
	}
	ft_memcpy((*s_buf)->string + (*s_buf)->read, str, len);
	(*s_buf)->read += len - 1;
	return (1);
}

static int	read_into_static(const int fd, t_buffer **s_buf)
{
	char		buf[BUFF_SIZE + 1];
	int			res;

	res = read(fd, buf, BUFF_SIZE);
	while (res > 0)
	{
		buf[res] = '\0';
		if (append_to_buff(s_buf, buf, res + 1) == -1)
			return (-1);
		if (ft_strchr(buf, '\n') != NULL)
			return (res);
		res = read(fd, buf, BUFF_SIZE);
	}
	return (res);
}

static void	read_into_line(t_buffer **s_buf, char **buffer, char **line)
{
	size_t	end;
	size_t	len;

	end = 0;
	while ((*buffer)[end] != '\n' && (*buffer)[end])
		end++;
	*line = ft_strsub(*buffer, 0, end);
	if ((*buffer)[end] == '\n')
	{
		len = (*s_buf)->read - end - 1;
		ft_memmove(*buffer, *buffer + end + 1, len + 1);
		(*s_buf)->read = len;
		if (*(*s_buf)->string == '\0')
		{
			ft_strdel(buffer);
			ft_memdel((void **)s_buf);
		}
	}
	else
	{
		ft_strdel(buffer);
		ft_memdel((void **)s_buf);
	}
}

int	ft_get_next_line(const int fd, char **line)
{
	static t_buffer	*buffers[4096];
	int				res;

	if (line == NULL || fd < 0 || BUFF_SIZE < 1 || fd >= 4096)
		return (-1);
	if (buffers[fd] == NULL)
	{
		buffers[fd] = (t_buffer *)ft_memalloc(sizeof(t_buffer));
		if (buffers[fd] == NULL)
			return (-1);
		buffers[fd]->string = NULL;
	}
	res = read_into_static(fd, &(buffers[fd]));
	if (res < 0)
		return (-1);
	if (buffers[fd]->string == NULL && res == 0)
		return (0);
	read_into_line(&(buffers[fd]), &(buffers[fd]->string), line);
	return (1);
}
