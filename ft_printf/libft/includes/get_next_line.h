/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 12:24:00 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/14 16:24:58 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1

# include <fcntl.h>
# include "libft.h"

# define CHECK(x) if (!x) return (-1);
int	get_next_line(int fd, char **line);
// typedef struct			s_dlist
// {
// 	int					fd;
// 	char				*reste;
// 	struct s_dlist		*next;
// }						t_dlist;

// typedef struct			s_gnl
// {
// 	int					length;
// 	char				*buffer;
// 	t_dlist				*mew;
// 	int					ret;
// }						t_gnl;

// int						get_next_line(const int fd, char **line);
// int						get_next_line_backslash(const int fd, char **line);

#endif
