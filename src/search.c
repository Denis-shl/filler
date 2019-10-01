#include "../includes/filler.h"

extern char			**playing_field;
extern char			**figures_field;
extern char			*player_my;
extern char			*player_en;
extern un_int		start_my_x;
extern un_int		start_my_y;
extern un_int		start_enemy_x;
extern un_int		start_enemy_y;
extern VERTICAL		map_size_y;
extern HORIZONTAL	map_size_x;

int        count_contact(int y, int x)
{
	int 	iooooo;
    int    i;
    int    i2;
    int    o;
    
    i = -1;
    g_piece.nbr_contact = 0;
    while (++i < (int)g_piece.size_y)
    {
        i2 = -1;
        while (++i2 < (int)g_piece.size_x)
            if ((int)figures_field[i][i2] == '*')
            {
                o = 0;
                while (++o < 4)
                    if ((i2 + x + o) < (int)map_size_x && (i2 + x - o) > 0 &&
                        (i + y + o) < (int)map_size_y && (i + y - o) > 0)
                        if (playing_field[i + y][i2 + x + o] == player_en[0] ||
                            playing_field[i + y][i2 + x - o] == player_en[0] ||
                            playing_field[i + y + o][i2 + x] == player_en[0] ||
                            playing_field[i + y - o][i2 + x] == player_en[0])
                            g_piece.nbr_contact += (4 - o);
            }
    }
    return (g_piece.nbr_contact);
}

int		search_2(int nbr_contact)
{
	if (nbr_contact == -1)
		return (0);
	g_piece.final_x = g_piece.tmp_x;
	g_piece.final_x = g_piece.tmp_y;
	ft_printf ("%d %d\n", g_piece.final_x, g_piece.final_y);
	return (1);
}
int		search(void)
{
    int    i;
    int    i2;
    int    nbr_contact_tmp;
    int    nbr_contact;
    
    nbr_contact = -1;
    i = map_size_y - (g_piece.size_y - g_piece.end_y);
    g_piece.tmp_x = 0;
    g_piece.tmp_y = 0;
    while (--i >= 0)
    {
        i2 = map_size_x - (g_piece.size_x - g_piece.end_x);
        while (--i2 >= 0)
            if (placable(i, i2) == 0)
            {
                nbr_contact_tmp = count_contact(i, i2);
                if (nbr_contact_tmp > nbr_contact)
                {
                    nbr_contact = nbr_contact_tmp;
                    g_piece.tmp_x = i2;
                    g_piece.tmp_y = i;
                }
            }
    }
    return (search_2(nbr_contact));
}

int		finding_place_for_figure()
{
	int cont;
	int	ret;

	cont = contact();
	if (cont == 0)
	{
		if (start_my_y < start_enemy_y)
		{
			if (contact_l() == 1)
				return (1);
		}
		else if (start_my_y >= start_enemy_y)
		{
			if (contact_r() == 1)
				return (1) ;
		}
	}
	else
	{
		ret = search();
		if (ret == 0)
			return (1) ;
	}
	return (0);
}
