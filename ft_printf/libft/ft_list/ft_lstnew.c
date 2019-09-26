/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:42:42 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/02 16:27:40 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list    *ft_lstnew(void const *content, size_t content_size)
{
    t_list    *point;
    
    if (!(point = (t_list*)malloc(sizeof(*point))))
        return (NULL);
    if (!content)
    {
        point->content = NULL;
        point->content_size = 0;
    }
    else
    {
        if (!(point->content = malloc(content_size)))
        {
            free(point);
            return (NULL);
        }
        ft_memcpy(point->content, content, content_size);
        point->content_size = content_size;
    }
    point->next = NULL;
    return (point);
}
