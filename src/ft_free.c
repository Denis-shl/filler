#include "../includes/filler.h"

extern char	**playing_field;
extern char **figures_field;

int		ft_free()
{
	un_int index;

	if (playing_field != NULL)
	{
		index = 0;
		while (playing_field[index] != NULL)
		{
			free(playing_field[index]);
			index++;
		}
		free(playing_field);
		playing_field = NULL;
	}
	if (figures_field != NULL)
	{
		index = 0;
		while (figures_field[index] != NULL)
		{
			free(figures_field[index]);
			index++;
		}
		free(figures_field);
		figures_field = NULL;
	}
	return (SUCSES);
}
