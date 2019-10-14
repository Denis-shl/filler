/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 12:11:10 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/14 16:54:52 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

#include <stdio.h>

// int		ft_strclen(const char *s, char c)
// {
// 	int		i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// static void	mew_lst(t_dlist **mew, int fd)
// {
// 	*mew = (t_dlist *)malloc(sizeof(**mew));
// 	(*mew)->reste = ft_strnew(0);
// 	(*mew)->fd = fd;
// 	(*mew)->next = NULL;
// }

// static void	multi_fd_gnl(t_dlist **mew, t_dlist **mew2, int fd)
// {
// 	static t_dlist	*begin;

// 	if (begin)
// 	{
// 		*mew = begin;
// 		while (*mew != NULL)
// 		{
// 			if ((*mew)->fd == fd)
// 				break ;
// 			*mew2 = *mew;
// 			*mew = (*mew)->next;
// 		}
// 		if (*mew == NULL)
// 		{
// 			mew_lst(mew, fd);
// 			(*mew2)->next = *mew;
// 		}
// 	}
// 	else
// 	{
// 		mew_lst(mew, fd);
// 		begin = *mew;
// 	}
// }

// static int	backslash_in_buffer(char *buffer, int length, t_dlist **mew,
// 			char **line)
// {
// 	char	*temp;
// 	size_t	n;

// 	n = 0;
// 	temp = NULL;
// 	if (buffer[0] == '\0')
// 		return (-1);
// 	buffer[length] = '\0';
// 	if ((*mew)->reste == NULL)
// 		(*mew)->reste = ft_strdup("");
// 	if (ft_strchr(buffer, '\n'))
// 	{
// 		n = (size_t)ft_strclen(buffer, '\n');
// 		buffer[n] = '\0';
// 		*line = ft_strjoin((*mew)->reste, buffer);
// 		*line = ft_strjoin(*line, "\n");
// 		free((*mew)->reste);
// 		(*mew)->reste = ft_strdup(&buffer[n + 1]);
// 		free(buffer);
// 		return (1);
// 	}
// 	temp = (*mew)->reste;
// 	(*mew)->reste = ft_strjoin((*mew)->reste, buffer);
// 	free(temp);
// 	return (0);
// }

// static int	backslash_in_rest(int fd, char **line, t_dlist **mew, char **buffer)
// {
// 	size_t		n;
// 	char		*temp;
// 	t_dlist		*mew2;

// 	temp = NULL;
// 	mew2 = NULL;
// 	*line = NULL;
// 	multi_fd_gnl(mew, &mew2, fd);
// 	*buffer = ft_strnew(BUFF_SIZE);
// 	if ((*mew)->reste && ft_strchr((*mew)->reste, '\n'))
// 	{
// 		n = (size_t)ft_strclen((*mew)->reste, '\n');
// 		(*mew)->reste[n] = '\0';
// 		*line = ft_strdup((*mew)->reste);
// 		*line = ft_strjoin(*line, "\n");
// 		temp = (*mew)->reste;
// 		(*mew)->reste = ft_strdup(&(*mew)->reste[n + 1]);
// 		free(temp);
// 		return (1);
// 	}
// 	return (0);
// }

// int			get_next_line_backslash(const int fd, char **line)
// {
// 	t_gnl			gnl;

// 	gnl.length = 0;
// 	gnl.ret = -1;
// 	if (fd < 0 || BUFF_SIZE < 1 || !line)
// 		return (-1);
// 	if ((backslash_in_rest(fd, line, &gnl.mew, &gnl.buffer)) == 1)
// 		return (1);
// 	while ((gnl.length = (int)read(fd, gnl.buffer, BUFF_SIZE)) > 0)
// 	{
// 		gnl.ret = backslash_in_buffer(gnl.buffer, gnl.length, &gnl.mew, line);
// 		if (gnl.ret == 1 || gnl.ret == -1)
// 			return (gnl.ret);
// 	}
// 	if (gnl.length < 0 ||
// 			((gnl.mew->reste && (*line = ft_strdup(gnl.mew->reste)) == NULL)))
// 		return (-1);
// 	free(gnl.mew->reste);
// 	free(gnl.buffer);
// 	gnl.buffer = NULL;
// 	gnl.mew->reste = NULL;
// 	if (gnl.length == 0 && *line && (*line)[0] != '\0')
// 		return (1);
// 	return (0);
// }




t_list    *ft_get(t_list **file, int fd)
{
    t_list        *tmp;
    
    tmp = *file;
    while (tmp)
    {
        if ((int)tmp->content_size == fd)
            return (tmp);
        tmp = tmp->next;
    }
    if (!tmp)
        tmp = ft_lstnew("", fd);
    ft_lstadd(file, tmp);
    tmp = *file;
    return (tmp);
}

char    *ft_get_next(char **line, t_list *point)
{
    size_t            i;
    char            *del;
    
    if (ft_strchr((char *)point->content, '\n'))
    {
        *line = ft_strsub((char *)point->content, 0,\
                          ft_strchr((char *)point->content, '\n')\
                          - (char *)point->content);
        i = ft_strchr((char *)point->content, '\n') - (char *)point->content;
        del = point->content;
        if (i < ft_strlen((char *)point->content))
            point->content = ft_strdup(point->content + i + 1);
        free(del);
    }
    else
    {
        i = ft_strlen(point->content);
        del = point->content;
        *line = ft_strncpy(ft_strnew(i), (char *)point->content, i);
        point->content = ft_strdup(point->content + i);
        free(del);
    }
    return (*line);
}

int        get_next_line(const int fd, char **line)
{
    char			*buf;
    int                i;
    static t_list    *file;
    t_list            *point;
    char            *del;
    
    if (!(buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
        return (-1);
    if (fd < 0 || BUFF_SIZE < 0 || read(fd, buf, 0))
        return (-1);
    point = ft_get(&file, fd);
    while ((i = read(fd, buf, BUFF_SIZE)))
    {
        buf[i] = '\0';
        del = point->content;
        point->content = ft_strjoin((char *)point->content, buf);
        free(del);
        if (ft_strchr(buf, '\n'))
            break ;
    }
    free(buf);
    if (i < BUFF_SIZE && !ft_strlen((char *)point->content))
        return (0);
    *line = ft_get_next(line, point);
    return (1);
}
