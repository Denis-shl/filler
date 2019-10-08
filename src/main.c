#include "../includes/filler.h"

void	init_struct()
{
	g_piece.end_x = 0;
	g_piece.end_y = 0;
	g_piece.real_x = 0;
	g_piece.real_y = 0;
	g_piece.size_x = 0;
	g_piece.size_y = 0;
	g_piece.start_x = 0;
	g_piece.start_y = 0;
	g_piece.nbr_contact = 0;
	g_piece.tmp_x = 0;
	g_piece.tmp_y = 0;
	g_piece.flag = 0;
}

int		main (int argc, char **argv)
{
	char **map;

	init_struct();
	map = ft_read_map();
	argc = 1;
	return (0);
}
