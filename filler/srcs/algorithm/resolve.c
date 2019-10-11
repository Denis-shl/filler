/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oargrave <oargrave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 17:27:23 by mdubus            #+#    #+#             */
/*   Updated: 2019/10/10 17:44:55 by oargrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static void	get_score(t_filler *f, int score)
{
	if (f->is_zero == 1)
	{
		if ((score <= f->score && score > 0) || (score > 0 && f->score == 0))
		{
			f->score = score;
			f->tempx = f->x - f->i;
			f->tempy = f->y - f->j;
		}
		else
		{
			f->score2 = score;
			f->tempx2 = f->x - f->i;
			f->tempy2 = f->y - f->j;
		}
	}
	else
	{
		if (score < f->score || f->score == 0)
		{
			f->score = score;
			f->score2 = score;
			f->tempx2 = f->x - f->i;
			f->tempy2 = f->y - f->j;
		}
	}
}

static void	foreach_star(t_filler *f)
{
	int	score;

	score = 0;
	int index = 0;
	f->i = 0;
	f->j = 0;
	while ((index = search_next_star(f, &f->i, &f->j)) == 1)
	{
		score = 0;
		f->startx = f->i;
		f->starty = f->j;
		if (count_before(f, f->j, f->i, &score) == 0 &&
				count_after(f, f->j, f->i, &score) == 0)
		{
			get_score(f, score);
		}
	}
	if (f->score == 0)
	{
		f->score = f->score2;
		f->tempx = f->tempx2;
		f->tempy = f->tempy2;
	}
}

static void	search_after_zero(t_filler *f)
{
	f->is_zero = 0;
	while (f->y < f->h_board)
	{
		while (f->x < f->w_board)
		{
			if (f->hmap[f->y][f->x] > 0)
				f->is_zero = 1;
			f->x++;
		}
		f->x = 0;
		f->y++;
	}
	f->x = 0;
	f->y = 0;
}

void		t_printf (t_filler *f)
{
	// printf ("\ntab\n");
	// for (int i = 0; f->tab[i]; i++)
	// 	printf ("%s\n", f->tab[i]);
	printf ("\nmap\n");
	for (int i = 0; f->map[i]; i++)
		printf ("%s\n", f->map[i]);
	printf ("\npiece\n");
	for (int i = 0; f->piece[i]; i++)
		printf ("%s\n", f->piece[i]);
	printf ("\nhmap\n");
	for (int i = 0; i < f->h_board; i++)
	{
		for(int j = 0; j < f->w_board; j++)
			printf ("%d", f->hmap[i][j]);
		printf ("\n");
	}
	printf ("letter-me%c\n", f->letter_me);
	printf ("letter-ennemy%c\n", f->letter_ennemy);
	printf ("is_zero = %d\n", f->is_zero);
	printf ("w_board = %d\n", f->w_board);
	printf ("h_board = %d\n", f->h_board);
	printf ("w_piece = %d\n", f->w_piece);
	printf ("h_piece = %d\n", f->h_piece);
	printf ("x = %d\n", f->x);
	printf ("y = %d\n", f->y);
	printf ("nb_max = %d\n", f->nb_max);
	printf ("tempx = %d\n", f->tempx);
	printf ("tempy = %d\n", f->tempy);
	printf ("tempi = %d\n", f->tempi);
	printf ("tempj = %d\n", f->tempj);
	printf ("score = %d\n", f->score);
	printf ("i = %d\n", f->i);
	printf ("j = %d\n", f->j);
	printf ("startx = %d\n", f->startx);
	printf ("starty = %d\n", f->starty);
	printf ("flag_star = %d\n", f->flag_star);
	printf ("score2 = %d\n", f->score2);
	printf ("tempx2 = %d\n", f->tempx2);
	printf ("tempy2 = %d\n", f->tempy2);
	
	
}

void		resolve(t_filler *f)
{
	f->y = 0;
	f->x = 0;
	f->score = 0;
	f->tempx = 0;
	f->tempy = 0;
	f->score2 = 0;
	f->tempx2 = 0;
	f->tempy2 = 0;
	// t_printf(f);
	search_after_zero(f);
	while (f->y < f->h_board)
	{
		// printf ("g_piece.x = {%d}\n", f->x);
		// printf ("g_piece.y = {%d}\n", f->y);
		while (f->x < f->w_board)
		{
			if (f->hmap[f->y][f->x] == ME)
			{
				foreach_star(f);
			}
			f->x++;
		}
		f->x = 0;
		f->y++;
	}
}
