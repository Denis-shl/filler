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

char	**ft_read_map(void);
void	ft_identify_player(const char *str);
int		ft_free(void);
void	finding_place_for_figure(void);

typedef struct s_coord
{
	int			x;
	int			 y;
}	t_cord;

#endif
