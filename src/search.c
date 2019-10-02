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
extern short		**heat_map;


void        blank_field()
{
    un_int      x;
    un_int      y;

    g_piece.bl_f = 0;
    x = 0;
    y = 0;
    while (y < map_size_y)
    {
        x = 0;
        while (x < map_size_x)
        {
            if (heat_map[y][x] > 0)
            {
                g_piece.bl_f = 1;
                return ;
            }
            x++;
        }
        y++;
    }
}

int         flag_start(un_int *x, un_int *y)
{
    if (g_piece.flag == 1)
    {
        g_piece.flag = 0;
        if (*x + 1 < g_piece.size_x)
            (*x)++;
        else if (*y + 1 < g_piece.size_y)
        {
            *x = 0;
            (*y)++;
        }
        else 
            return (0);
    }
    return (1);
}

int         next_start(un_int *x, un_int *y)
{
    if (flag_start(x, y) == 0)
        return (0);
    if (*x == 0 && *y == 0 && figures_field[*y][*x] == '*')
    {
        g_piece.flag = 1;
        return (1);
    }
    else
    {
        while (*y < g_piece.size_y)
        {
            *x = 0;
            while (*x < g_piece.size_x)
            {
                if (figures_field[*y][*x] == '*')
                {
                    g_piece.flag = 1;
                    return (1);
                }
                (*x)++;
            }
            (*y)++;
        }
    }
    return (0);

}
int         count_score(int x, int y, int *score)
{
    if ()
    return (0);
}

int         c_before(int x, int y, un_int *score)
{
    g_piece.final_x = x;
    g_piece.final_y = y;

    while (y >= 0)
    {
        while (x >= 0)
        {
            if (figures_field[y][x] == '*')
            {
                if (count_score(y, x, score) == 1)
                    return (1);
            }
            x--;
        }
        x = g_piece.size_x - 1;
        y--;
    }
    return (0);
}

int         c_after(int x,  int y, un_int *score)
{
    g_piece.final_x = x;
    g_piece.final_y = y;
    
    while (y < g_piece.size_y)
    {
        x = 0;
        while (x < g_piece.size_x)
        {
            if (figures_field[y][x] == '*')
            {
                if (count_score(x, y, score) == 1)
                    return (1);
            }
            x++;
        }
        y++;
    }
    return (0);
}

void        get_score(un_int *score)
{
    if (g_piece.bl_f == 1)
    {
        if ((score > 0))// || (;)) //fix
        {
            g_piece.score = score;
            g_piece.final_x = 
        }
    }
}

void        algol(un_int x, un_int y)
{
    un_int i;
    un_int j;
    un_int score;

    i = 0;
    j = 0;

    while (next_start(&i, &j) == 1)
    {
        score = 0;
        g_piece.start_x = i;
        g_piece.start_y = j;
        if((c_before(i, j, &score)) == 0 && (c_after(i, j, &score)== 0))
        {
            get_score(score);
        }
    }

}
void		finding_place_for_figure()
{
	un_int x;
	un_int y;


    y = 0;
    blank_field();
    while (y < map_size_y)
    {
        x = 0;
        while (x < map_size_x)
        {
            if(heat_map[y][x] == -2)
            {
                algol(x, y);
            }
            x++;
        }
        y++;
    }
}