#include "../includes/filler.h"

char	*player_my = NULL;
char	*player_en = NULL;
char	play_one[] = "Oo";
char	play_two[] = "Xx";

int	ft_identify_player(char *str)
{
	char			*str_name;
	int				s_read;
/*
**  $$$ exec p2
**  01234567890
*/ 
	if (!(str = ft_strnew(1024)))
		return (0);
	// if ((s_read = get_next_line(0, &str)) != 1)
	// 	return (0);
	if (ft_strstr(str, PLAYER) != NULL && ft_strstr(str, NAME_PLAYER) != NULL)
	{
		str_name = str + 10;
		if (str_name[0] == '1')
		{
			player_my = play_one;
			player_en = play_two;
		}
		else if(str_name[0] == '2')
		{
			player_my = play_two;
			player_en = play_one;
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