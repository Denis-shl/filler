#include "../includes/filler.h"

extern char            **playing_field;
extern char            **figures_field;
extern char            *player_my;
extern char            *player_en;
extern un_int        start_my_x;
extern un_int        start_my_y;
extern un_int        start_enemy_x;
extern un_int        start_enemy_y;
extern VERTICAL        map_size_y;
extern HORIZONTAL    map_size_x;

int        contact(void)
{
    un_int i;
    un_int j;
    
    i = 2;
    while (++i < map_size_y - 3)
    {
        j = 2;
        while (++j < map_size_x - 3)
            if (playing_field[i][j] == player_my[0] ||
                playing_field[i][j] ==  player_my[1])
                if (playing_field[i][j + 3] == player_en[0]
                    || playing_field[i][j - 3]
                    == player_en[0]
                    || playing_field[i + 3][j] == player_en[0]
                    || playing_field[i - 3][j]
                    == player_en[0]
                    || playing_field[i][j + 3] == player_en[1]
                    || playing_field[i][j - 3]
                    == player_en[1]
                    || playing_field[i + 3][j] == player_en[1]
                    || playing_field[i - 3][j]
                    == player_en[1])
                    return (1) ;
    }
    return (0);
}

int     placable_two(int count, int i, int i2)
{
    if (count == 1)
    {
        g_piece.final_x = i2;
        g_piece.final_y = i;
        return (0);
    }
    return (1);
}

int        placable(int i, int i2)
{
    int j;
    int j2;
    int count;
    
    j = -1;
    count = 0;
    if (i + g_piece.size_y > map_size_y || i2 + g_piece.size_x > map_size_x)
    {
         printf ("vse ok");
        return (1);
    }
    while (++j <= ((int)g_piece.size_y - 1))
    {
        j2 = -1;
        while (++j2 <= ((int)g_piece.size_x - 1))
        {
            if (figures_field[j][j2] == '*' && (playing_field[i + j][i2 + j2] ==
                                                player_en[0] || playing_field[i + j][i2 + j2] ==
                                                player_en[1]))
                return (1);
            if (figures_field[j][j2] == '*' && (playing_field[i + j][i2 + j2] ==
                                                player_my[0] || playing_field[i + j][i2 + j2] == player_my[0] - 32))
                {
                    printf ("count ++\n");
                    count++;
                }
        }
    } 
    if (placable_two(count, i, i2) == 0)
    {
        return (0);
    }
    return (1);
}


int        contact_l()
{
    int i;
    int j;
    int ret;
    
    i = map_size_x - 1;
    g_piece.final_x = 0;
    g_piece.final_y = 0;
    ret = 0;
    while (i > 0)
    {
        j = map_size_x - 1;
        while (j > 0)
        {
            ret = placable(i, j);
            if (ret == 0)
            {
                return (0);
            }
        }
    }
    return (1);
}

int        contact_r()
{
    
    int i;
    int j;
    int ret;
    
    i = -1;
    g_piece.final_x = 0;
    g_piece.final_y = 0;
    ret = 0;
    printf ("%d\n", map_size_y);
    printf ("%d\n", map_size_x);
    while (++i < map_size_y - 1)
    {
        j = -1;
        while (++j < map_size_x - 1)
        {
            ft_printf("{%d} {%d}", i, j);
            ret = placable(i, j);
            ft_printf (" {%d}\n", ret);
            if (ret == 0)
            {
                //  for(int  i = 0; playing_field[i]; i++)
                // printf ("%s\n", playing_field[i]);
                return (0);
            }
        }
    }
    return (1);
}
