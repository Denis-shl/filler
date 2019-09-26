#include "../includes/filler.h"

extern char	**playing_field;
int		ft_free()
{
	un_int index;

	index = 0;
	while (playing_field[index] != NULL)
	{
		free(playing_field[index]);
		index++;
	}
	free(playing_field);
	playing_field = NULL;
	return (SUCSES);
}
