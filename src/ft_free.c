/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:19:10 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/16 11:19:19 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

extern char	**g_map;
extern char **g_fmap;

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
	if (g_fmap != NULL)
	{
		index = 0;
		while (g_fmap[index] != NULL)
		{
			free(g_fmap[index]);
			index++;
		}
		free(g_fmap);
		g_fmap = NULL;
	}
	return (SUCSES);
}

void	ft_del_char(char *str)
{
	if (str != NULL)
		free(str);
}
