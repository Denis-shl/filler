/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 12:11:10 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/11 16:20:07 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

#include <stdio.h>

int		line_verif(char **line, char **tmp, int res, char **str)
{
	*str = NULL;
	if (res == 0 && ft_strlen(*tmp) > 0)
	{
		*line = *tmp;
		*tmp = NULL;
		return (1);
	}
	return (res);
}

char	*read_line(char *tmp)
{
	int		t;
	char	*line;

	t = 0;
	while (tmp[t] != '\n')
		t++;
	line = (char *)malloc((t + 1) * sizeof(char));
	line = ft_strncpy(line, tmp, t);
	line[t] = '\0';
	return (line);
}

char	*cpycat(char *s1, char *s2)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_memalloc(ft_strlen(s1) + ft_strlen(s2));
	s1 ? tmp = ft_strcpy(tmp, s1) : NULL;
	s1 ? tmp = ft_strncat(tmp, s2, ft_strlen(s2)) : NULL;
	return (tmp);
}

int		get_next_line(int const fd, char **line)
{
	static char		*str = NULL;
	int				res;
	char			*buf;
	char			*tmp;

	if (fd < 0 || !line || BUFF_SIZE < 1 || BUFF_SIZE > 10000000)
		return (-1);
	buf = ft_strnew(BUFF_SIZE + 1);
	if (str == NULL)
		str = ft_memalloc(BUFF_SIZE);
	tmp = ft_strncpy(ft_memalloc(BUFF_SIZE), str, BUFF_SIZE);
	while (!(ft_strchr(tmp, '\n')))
	{
		if ((res = read(fd, buf, BUFF_SIZE)) < 1)
			return (line_verif(line, &tmp, res, &str));
		buf[res] = '\0';
		tmp = cpycat(tmp, buf);
	}
	*line = read_line(tmp);
	if (ft_strchr(tmp, '\n'))
		str = ft_strncpy(str, ft_strchr(tmp, '\n') + 1, BUFF_SIZE);
	free(tmp);
	free(buf);
	return (1);
}




// t_list    *ft_get(t_list **file, int fd)
// {
//     t_list        *tmp;
    
//     tmp = *file;
//     while (tmp)
//     {
//         if ((int)tmp->content_size == fd)
//             return (tmp);
//         tmp = tmp->next;
//     }
//     if (!tmp)
//         tmp = ft_lstnew("", fd);
//     ft_lstadd(file, tmp);
//     tmp = *file;
//     return (tmp);
// }

// char    *ft_get_next(char **line, t_list *point)
// {
//     size_t            i;
//     char            *del;
    
//     if (ft_strchr((char *)point->content, '\n'))
//     {
//         *line = ft_strsub((char *)point->content, 0,\
//                           ft_strchr((char *)point->content, '\n')\
//                           - (char *)point->content);
//         i = ft_strchr((char *)point->content, '\n') - (char *)point->content;
//         del = point->content;
//         if (i < ft_strlen((char *)point->content))
//             point->content = ft_strdup(point->content + i + 1);
//         free(del);
//     }
//     else
//     {
//         i = ft_strlen(point->content);
//         del = point->content;
//         *line = ft_strncpy(ft_strnew(i), (char *)point->content, i);
//         point->content = ft_strdup(point->content + i);
//         free(del);
//     }
//     return (*line);
// }

// int        get_next_line(const int fd, char **line)
// {
//     char            *buf;
//     int                i;
//     static t_list    *file;
//     t_list            *point;
//     char            *del;
    
//     if (!(buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
//         return (-1);
//     if (fd < 0 || BUFF_SIZE < 0 || read(fd, buf, 0))
//         return (-1);
//     point = ft_get(&file, fd);
//     while ((i = read(fd, buf, BUFF_SIZE)))
//     {
//         buf[i] = '\0';
//         del = point->content;
//         point->content = ft_strjoin((char *)point->content, buf);
//         free(del);
//         if (ft_strchr(buf, '\n'))
//             break ;
//     }
//     free(buf);
//     if (i < BUFF_SIZE && !ft_strlen((char *)point->content))
//         return (0);
//     *line = ft_get_next(line, point);
//     return (1);
// }
