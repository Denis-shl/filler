/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:19:00 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/16 12:03:41 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

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
