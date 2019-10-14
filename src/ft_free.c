#include "../includes/filler.h"

extern char	**playing_field;
extern char **figures_field;
extern short		**heat_map;
extern VERTICAL		map_size_y;
extern HORIZONTAL	map_size_x;
int		ft_free()
{
	int index;
	int jindex;

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
	if (heat_map != NULL)
	{
		index = 0;
		while (index < map_size_y)
		{
			free(heat_map[index]);
			index++;
		}
	}
	return (SUCSES);
}
