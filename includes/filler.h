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

typedef unsigned int	VERTICAL;
typedef unsigned int	HORIZONTAL;
typedef unsigned int	un_int;
/*
**	func read virtual map and tetremins
*/

void	ft_read_map(void);
int		ft_identify_player(char *str);
int		ft_free(void);
void	finding_place_for_figure(void);
void	print_result();
int     contact(void);
int     placable_two(int count, int i, int i2);
int     placable(int i, int i2);
/* new ver*/

int		read_str(char *str);
void	append_str(char *str, char *buff);


typedef struct s_piece
{
	un_int	real_x;
	short	bl_f;
	short	flag;
	un_int	real_y;
	un_int	size_x;
	un_int	size_y;
	un_int	start_x;
	un_int	start_y;
	un_int	end_x;
	un_int	end_y;
	int		final_x;
	int		final_y;
	int		tmp_x;
	int		tmp_y;
	int		nbr_contact;
	int		score;
	int		score2;
	int		tmp_x2;
	int		tmp_y2;
	int		x;
	int		y;
	int		tempj;
	int		tempi;
	int		i;
	int		j;
}t_piece;

t_piece				g_piece;
#endif
