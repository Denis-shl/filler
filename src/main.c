/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:19:00 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/16 15:50:15 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

extern int		g_size_y;
extern int		g_size_x;
extern char		**g_map;

void	init_struct(void)
{
	g_pi.bl_f = 0;
	g_pi.flag = 0;
	g_pi.size_x = 0;
	g_pi.size_y = 0;
	g_pi.tmp_x = 0;
	g_pi.tmp_y = 0;
	g_pi.score = 0;
	g_pi.score2 = 0;
	g_pi.tmp_x2 = 0;
	g_pi.tmp_y2 = 0;
	g_pi.x = 0;
	g_pi.y = 0;
	g_pi.tempj = 0;
	g_pi.tempi = 0;
	g_pi.i = -1;
	g_pi.j = 0;
}

int		check_map(void)
{
	int		index;
	int		jindex;

	index = 0;
	while (g_size_y > index)
	{
		jindex = 0;
		while (jindex < g_size_x)
		{
			if (g_map[index][jindex] != '.' && g_map[index][jindex] != 'X'
			&& g_map[index][jindex] != 'x' && g_map[index][jindex] != 'o' &&
			g_map[index][jindex] != 'O')
				return (-1);
			jindex++;
		}
		index++;
	}
	return (1);
}

void	append_str(char *str, char *buff)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	str[i] = buff[0];
	str[i + 1] = '\0';
}

int		read_str(char *str)
{
	char	buff[1];

	while (1)
	{
		read(0, buff, 1);
		if (buff[0] == '\0')
			return (-1);
		append_str(str, buff);
		if (buff[0] == '\n')
			return (0);
	}
}

int		main(void)
{
	init_struct();
	ft_read_map();
	return (0);
}
