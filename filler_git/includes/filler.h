/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 04:11:00 by lcharvol          #+#    #+#             */
/*   Updated: 2019/09/29 21:29:42 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "mlx/mlx.h"
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "../includes/filler.h"
# include "../libft/libft.h"

typedef struct		s_map
{
	char			**map;
	int				player;
	int				map_size_x;
	int				map_size_y;
	char			*en;
	int				pos_enemy_x;
	int				pos_enemy_y;
	int				my_pos_x;
	int				my_pos_y;
	int				first_x;
	int				first_y;
	char			*me;
	void			*win;
	void			*mlx;
	void			*img;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	char			*ret;
}					t_map;

typedef struct		s_piece
{
	int				tmp_x;
	int				tmp_y;
	int				nbr_contact;
	int				contact;
	int				final_x;
	int				final_y;
	char			**piece; // фигура которую надо поставить
	int				size_x;
	int				size_y;
	int				real_size_x;
	int				real_size_y;
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
}					t_piece;

int					algo2_2(t_map *map, t_piece *p);
int					algo1_2(t_map *map, t_piece *p);
int					algo3_2(int nbr_contact, t_piece *p, t_map *map);
int					is_placable2(t_piece *p, int count, int i, int i2);
void				get_contact(t_piece *p, t_map *map);
int					count_contact(t_map *map, t_piece *p, int y, int x);
int					algo3(t_map *map, t_piece *p);
int					last_try(t_map *map, t_piece *p);
void				print_result(t_piece *p, t_map *map);
int					algo2(t_map *map, t_piece *p);
int					algo1(t_map *map, t_piece *p);
int					is_placable(int i, int i2, t_map *map, t_piece *p);
void				wich_player(t_map *map);
void				get_real_piece_size(t_piece *p);
void				get_piece(t_piece *p);
void				get_piece_size(char *line, t_piece *p);
int					last_try(t_map *map, t_piece *p);
void				wich_player(t_map *map);
void				print_result(t_piece *p, t_map *map);
void				verif(t_map *map, t_piece *p);
void				get_player(t_map *map);
int					play(t_map *map, t_piece *p);
int					is_number(char c);
int					get_the_ret(t_map *map, t_piece *p);

#endif
