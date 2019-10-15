# ifndef FILLER_H
# define FILLER_H
/*
** Define map
*/
# define FIGURES "Piece"
# define MAPS "Plateau"
# define LEN_MAPS 7
# define LEN_FIGURES 5
# define PLAYER "$$$ exec"
# define LEN_PLAYER 8
# define NAME_PLAYER "oargrave.filler"
/*
* Define ERROR
*/
# define FAIL -1
# define SUCSES 1
# include "../ft_printf/includes/header.h"

/*
*define types
*/

typedef unsigned int VERTICAL;
typedef unsigned int HORIZONTAL;
typedef unsigned int un_int;
/*
** func read virtual map and tetremins
*/

void    ft_read_map(void);
int     ft_identify_player(char *str);
int     ft_free(void);
int     finding_place_for_figure(void);
void    print_result();
int     contact(void);
int     placable_two(int count, int i, int i2);
int     placable(int i, int i2);
/* new ver*/

int     read_str(char *str);
void    append_str(char *str, char *buff);
int     ft_lennumb(int num);
void    init_struct();
void	create_heat_map(void);
void	init_heat_map_two(int x, int y);
int		put_index_heat(int x, int y, int *flag);
void	init_heat_map();

typedef struct s_piece
{
int real_x;
short bl_f;
short flag;
int real_y;
int size_x;
int size_y;
int start_x;
int start_y;
int end_x;
int end_y;
int final_x;
int final_y;
int tmp_x;
int tmp_y;
int nbr_contact;
int score;
int score2;
int tmp_x2;
int tmp_y2;
int x;
int y;
int tempj;
int tempi;
int i;
int j;
}t_piece;

t_piece g_piece;
#endif
