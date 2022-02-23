/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cocoaconvert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:03:46 by okinnune          #+#    #+#             */
/*   Updated: 2022/02/23 06:50:09 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*static int	readchart(char *chart)
{
	int	fd;

	fd = open("cocoatable");
	if (fd < 0)
	{
		ft_putstr("cocoatable file not found!\n");
		return 0;
	}
	read(fd, 1000, chart);
}*/

/* Norminette no likey, fix... */
char	global_cocoa[34][2][6] = 
{
	{"A", "0"},
	{"B", "11"},
	{"C", "8"},
	{"D", "2"},
	{"E", "14"},
	{"F", "3"},
	{"G", "5"},
	{"H", "4"},
	{"I", "34"},
	{"J", "38"},
	{"K", "40"},
	{"L", "37"},
	{"M", "46"},
	{"N", "45"},
	{"O", "31"},
	{"P", "35"},
	{"Q", "12"},
	{"R", "15"},
	{"S", "1"},
	{"T", "17"},
	{"U", "32"},
	{"V", "9"},
	{"W", "13"},
	{"X", "7"},
	{"Y", "16"},
	{"Z", "6"},
	{"65288", "51"}, //RETURN
	{"65293", "36"}, //ENTER
	{"65505", "257"}, //SHIFT
	{"65362", "126"}, //UP
	{"65364", "125"}, //DOWN
	{"65361", "123"}, //LEFT
	{"65363", "124"}, //RIGHT
	{"167", "10"} //TILDE
};

int	convert_cocoakc_to_ascii_global(int kc)
{
	int		i;
	char	*istr;

	i = 0;
	istr = ft_itoa(kc);
	while (i < 34 && istr != NULL)
	{
		if (ft_strcmp(istr, global_cocoa[i][1]) == 0)
		{
			if (i < 26)
				kc = *(global_cocoa[i][0]);
			else
				kc = ft_atoi(global_cocoa[i][0]);
			ft_strdel(&istr);
		}
		i++;
	}
	if (istr != NULL)
		ft_strdel(&istr);
	return (kc);
}

/* scrapped for now lulz
int	convert_cocoakc_to_ascii(int kc)
{
	static char	chart[1000];
	char		*head;
	char		*istr;

	if (chart == NULL)
	{
		if (readchart(&chart) == 0)
			return (kc);
	}
	head = chart;
	istr = ft_itoa(kc);
	while (ft_strchr(head, '\n') != NULL)
	{
		// locate substring "line", get length of current head until the strchr occurence of newline
		ft_substr(head - ft_strchr(head, '\n'))
		ft_s
		head = ft_strchr(head, '\n')
	}

} */
