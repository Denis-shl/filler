#include "../includes/filler.h"

char	*player_my = NULL;
char	*player_en = NULL;
char	play_one[] = "Oo";
char	play_two[] = "Xx";
extern FILE *g_fd;

int	ft_identify_player(char *str)
{
	char			*str_name;
	int				s_read;
/*
**  $$$ exec p2
**  01234567890
*/ 
	if ((s_read = get_next_line(0, &str)) != 1)
		return (0);
	fprintf (g_fd, "gnl  %s\n", str);
	if (ft_strstr(str, PLAYER) != NULL && ft_strstr(str, NAME_PLAYER) != NULL)
	{
		str_name = str + 10;
		if (str_name[0] == '1')
		{
			player_my = play_one;
			player_en = play_two;
			fprintf (g_fd, "player my %s\n", player_my);
			fprintf (g_fd, "player en %s\n", player_en);
		}
		else if(str_name[0] == '2')
		{
			player_my = play_two;
			player_en = play_one;
			fprintf (g_fd, "player my %s\n", player_my);
			fprintf (g_fd, "player en %s\n", player_en);
		}
		else 
			return (0);
	}
	else
		return (0);
	return (1);
}

// # -------------- VM  version 1.1 ------------- #
// #                                              #
// # 42 / filler VM Developped by: Hcao - Abanlin #
// #                                              #
// # -------------------------------------------- #
// launched players/carli.filler
// $$$ exec p1 : [players/carli.filler]
// launched ../../oargrave.filler
// $$$ exec p2 : [../../oargrave.filler]
// Plateau 15 17: