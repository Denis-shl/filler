/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:18:57 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/16 12:19:05 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

char		**g_map = NULL;
char		**g_fmap = NULL;
short		**g_hmap = NULL;
extern char	*g_play_my;
extern char *g_play_en;
int			g_size_y;
int			g_size_x;

void	put_index(void)
{
	int		x;
	int		y;
	int		flag;

	flag = 1;
	while (flag == 1)
	{
		y = 0;
		flag = 0;
		while (y < g_size_y)
		{
			x = 0;
			while (x < g_size_x)
			{
				put_index_heat(x, y, &flag);
				x++;
			}
			y++;
		}
	}
}

void	size_figr(char *str)
{
	char	*size_map;
	int		y;
	int		x;
	int		index;

	index = 0;
	size_map = (char *)str + (LEN_FIGURES + 1);
	y = ft_atoi(size_map);
	size_map += ft_lennumb(y) + 1;
	x = ft_atoi(size_map);
	g_fmap = (char **)malloc((y + 1) * (sizeof(char *)));
	g_fmap[y] = NULL;
	while (index < y)
	{
		g_fmap[index] = (char *)malloc((x + 1) * (sizeof(char)));
		index++;
	}
	g_pi.size_x = x;
	g_pi.size_y = y;
}

int		map_figr(char *str, int *index, int *jindex)
{
	if (str && str[0] == '0')
		ft_strcpy(g_map[++(*jindex)], str + 4);
	else if (str && ft_strstr(str, FIGURES) != NULL)
		size_figr(str);
	else if (str && (str[0] == '.' || str[0] == '*'))
	{
		ft_strcpy(g_fmap[++(*index)], str);
		if ((*index) == g_pi.size_y - 1)
		{
			free(str);
			return (1);
		}
	}
	return (0);
}

int		map_and_figr(void)
{
	char			*str;
	int				index;
	int				jindex;
	int				status;

	index = -1;
	jindex = -1;
	str = ft_strnew(1024);
	while (1)
	{
		ft_bzero(str, 1024);
		read_str(str);
		if (str == NULL || str[0] == '\0' || str[0] == '\n')
		{
			ft_del_char(str);
			return (-1);
		}
		status = map_figr(str, &index, &jindex);
		if (status == 1)
			return (1);
	}
	return (0);
}

void	ft_read_map(void)
{
	if (ft_identify_player() == 0)
		return ;
	while (1)
	{
		if (map_and_figr() == 1)
		{
			create_heat_map();
			init_heat_map();
			put_index();
			finding_place_for_figure();
			ft_putnbr(g_pi.tmp_y);
			ft_putchar(' ');
			ft_putnbr(g_pi.tmp_x);
			ft_putchar('\n');
		}
		else
		{
			ft_free();
			return ;
		}
	}
}
