#include "../includes/filler.h"

void	init_struct()
{
	g_piece.real_x = 0;
	g_piece.bl_f = 0;
	g_piece.flag = 0;
	g_piece.real_y = 0;
	g_piece.size_x = 0;
	g_piece.size_y = 0;
	g_piece.start_x = 0;
	g_piece.start_y = 0;
	g_piece.end_x = 0;
	g_piece.end_y = 0;
	g_piece.final_x = 0;
	g_piece.final_y = 0;
	g_piece.tmp_x = 0;
	g_piece.tmp_y = 0;
	g_piece.nbr_contact = 0;
	g_piece.score = 0;
	g_piece.score2 = 0;
	g_piece.tmp_x2 = 0;
	g_piece.tmp_y2 = 0;
	g_piece.x = 0;
	g_piece.y = 0;
	g_piece.tempj = 0;
	g_piece.tempi = 0;
	g_piece.i = -1;
	g_piece.j = 0;
}

int		main (int argc, char **argv)
{
	init_struct();
	ft_read_map();
	argc = 1;
	return (0);
}
