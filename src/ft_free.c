/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:19:10 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/16 16:32:58 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

extern char		**g_map;
extern char		**g_fmap;
extern short	**g_hmap;
extern int		g_size_y;
extern int		g_size_x;

int		ft_free(void)
{
	int			index;

	if (g_map != NULL)
	{
		index = 0;
		while (g_map[index] != NULL)
		{
			free(g_map[index]);
			index++;
		}
		free(g_map);
		g_map = NULL;
	}
	del_hmap();
	del_figure();
	return (SUCSES);
}

void	del_hmap(void)
{
	int index;

	index = 0;
	if (g_hmap != NULL)
	{
		while (index < g_size_y)
		{
			free(g_hmap[index]);
			index++;
		}
		free(g_hmap);
		g_hmap = NULL;
	}
}

void	del_figure(void)
{
	int index;

	index = 0;
	if (g_fmap != NULL)
	{
		while (index < g_pi.size_y)
		{
			free(g_fmap[index]);
			index++;
		}
		free(g_fmap);
		g_fmap = NULL;
	}
}

int		ft_del_char(char *str)
{
	if (str != NULL)
		free(str);
	str = NULL;
	return (1);
}
