/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:18:52 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/16 12:19:05 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

char				*g_play_my = NULL;
char				*g_play_en = NULL;
char				g_play_one[] = "Oo";
char				g_play_two[] = "Xx";
extern char			**g_map;
extern int			g_size_y;
extern int			g_size_x;

int		ft_lennumb(int num)
{
	int		len;

	len = 0;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

void	size_map(char *str)
{
	char	*size_map;
	int		y;
	int		x;
	int		index;

	index = 0;
	size_map = (char *)str + (LEN_MAPS + 1);
	y = ft_atoi(size_map);
	size_map += ft_lennumb(y) + 1;
	x = ft_atoi(size_map);
	g_map = (char **)malloc((y + 1) * (sizeof(char *)));
	g_map[y] = NULL;
	while (index < y)
	{
		g_map[index] = (char *)malloc((x + 1) * (sizeof(char)));
		index++;
	}
	g_size_x = x;
	g_size_y = y;
}

void	name_game(char *str)
{
	char *str_name;

	str_name = NULL;
	str_name = str + 10;
	if (str_name[0] == '1')
	{
		g_play_my = g_play_one;
		g_play_en = g_play_two;
	}
	else if (str_name[0] == '2')
	{
		g_play_my = g_play_two;
		g_play_en = g_play_one;
	}
}

int		ft_identify_player(void)
{
	char	*str;

	if (!(str = ft_strnew(1024)))
		return (0);
	while (1)
	{
		ft_bzero(str, 1024);
		read_str(str);
		if (ft_strstr(str, PLAYER) != NULL &&
				ft_strstr(str, NAME_PLAYER) != NULL)
			name_game(str);
		if (ft_strstr(str, MAPS) != NULL)
		{
			size_map(str);
			ft_del_char(str);
			return (1);
		}
	}
	return (0);
}
