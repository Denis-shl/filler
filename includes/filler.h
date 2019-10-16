/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:13:56 by oargrave          #+#    #+#             */
/*   Updated: 2019/10/16 12:49:35 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define FIGURES "Piece"
# define MAPS "Plateau"
# define LEN_MAPS 7
# define LEN_FIGURES 5
# define PLAYER "$$$ exec"
# define LEN_PLAYER 8
# define NAME_PLAYER "oargrave.filler"
# define FAIL -1
# define SUCSES 1
# include "../ft_printf/includes/header.h"

typedef struct	s_piece
{
	int			real_x;
	short		bl_f;
	short		flag;
	int			size_x;
	int			size_y;
	int			tmp_x;
	int			tmp_y;
	int			score;
	int			score2;
	int			tmp_x2;
	int			tmp_y2;
	int			x;
	int			y;
	int			tempj;
	int			tempi;
	int			i;
	int			j;
}				t_piece;
t_piece			g_pi;

void			ft_read_map(void);
int				ft_identify_player(void);
int				ft_free(void);
int				finding_place_for_figure(void);
void			print_result(void);
void			ft_del_char(char *str);
int				read_str(char *str);
void			append_str(char *str, char *buff);
int				ft_lennumb(int num);
void			init_struct();
void			create_heat_map(void);
void			init_heat_map_two(int x, int y);
int				put_index_heat(int x, int y, int *flag);
void			init_heat_map();
int				next_start(int *x, int *y);
void			algol(int x, int y);
int				c_after(int x, int y, int *score);
int				c_before(int x, int y, int *score);

#endif
