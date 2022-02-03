/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 06:53:22 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/03 12:15:54 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init(char font[1200])
{
	int	fd;
	int	ret;

	//printf("init called");
	if (*font == '\0')
	{
		printf("open called");
		fd = open("font", O_RDONLY);
		ft_bzero(font, 1200);
		ret = read(fd, font, 1200);
	}
}

char	*fontchar(char font[1200], char c)
{
	int		nlcount;
	char	*result;

	nlcount = 0;
	if (ft_isalpha(c))
	{
		//printf("is alpha %c\n", c);
		c = ft_toupper(c);
		result = font;
		while(nlcount < (c - 'A') * 6)
		{
			result = ft_strchr(result+1, '\n');
			nlcount++;
		}
	}
	else
	{
		if (c == ' ')
			return (NULL);
		result = ft_strchr(font, c);
		if (result == NULL)
		{
			//printf("assigning error char for %c\n", c);
			result = ft_strchr(font, 'e');
			//printf("assigned error char for %c\n", c);
		} else
		{
			//printf("found nonalpha char %c in index %li\n", c, (result - font));
		}
		
	}
	return (result);
}

void	drawstr(t_mlx_i i, char *str, int x, int y)
{
	while (*str)
	{
		drawchar(i, *str, x, y);
		x += FONTSIZE * 6;
		str++;
	}
}

void	drawchar(t_mlx_i i, char c, int x, int y)
{
	static	char font[1200];
	int		nlcount;
	char	*fchar;

	init(font);
	fchar = fontchar(font, c);
	if (fchar == NULL)
		return ;
	nlcount = 0;
	int ogx = x;
	x = 0;
	while(nlcount < 6)
	{
		while (*(fchar) != '\n')
		{
			if (*fchar == 'X')
			{
				int drw = 0;
				int drw2 = 0;
				while (drw++ <= (FONTSIZE / 2))
				{
					while (drw2++ <= (FONTSIZE / 2))
						mlx_pixel_put(i.mlx, i.win, ogx + (x * FONTSIZE) + drw2, (y + (nlcount * FONTSIZE) + drw), INT_MAX);
					drw2 = 0;
				}
			}
			fchar++;
			x++;
		}
		nlcount++;
		fchar++;
		x = 0;
	}
}