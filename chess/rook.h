#pragma once
#include "board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int	ROOK_WIDTH = 9;
const int	ROOK_HEIGHT = 8;

class rook
{
public:
	void	init(board& board_object);
	void	check(board& board_object);
	bool	move(board& board_object, int new_y_coordinate, int new_x_coordinate);
	bool	get_available_moves(int y_coordinate, int x_coordinate);
	int		get_x_coordinate(void) {return x_coordinate;}
	int		get_y_coordinate(void) {return y_coordinate;}
	int		get_num_available_moves(void) {return num_available_moves;}

	int		up_moves;
	int		down_moves;
	int		left_moves;
	int		right_moves;

private:
	char	game_piece;
	int		x_coordinate;
	int		y_coordinate;
	int		num_available_moves;
	board	available_moves;
};

