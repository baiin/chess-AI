#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "board.h"
#include "player.h"
using namespace std;

class player_y
{
private:
	static const int	KING_WIDTH = 9;
	static const int	KING_HEIGHT = 8;

	class king
	{
	public:
		void	init(board& board_object, int start_king_y_coordinate, int start_king_x_coordinate);
		void	check(board& board_object, player enemy_player);
		bool	move(board& board_object, player& enemy_player, int new_y_coordinate, int new_x_coordinate);
		void	create_king_border(board& board_object);
		bool	get_is_checked(void) {return is_checked;}
		void	set_is_checked(bool bool_value) {is_checked = bool_value;}
		bool	get_available_moves(int y_coordinate, int x_coordinate);
		bool	get_king_border(int y_coordinate, int x_coordinate);
		int		get_x_coordinate(void) {return x_coordinate;}
		int		get_y_coordinate(void) {return y_coordinate;}
		int		get_num_available_moves(void) {return num_available_moves;}
		bool	test_for_check(board& board_object, player enemy_player, int new_y_coordinate, int new_x_coordinate);
		void	get_available_check_moves(board& board_object, player enemy_player, int y_coordinate, int x_coordinate);

		bool	up_move;
		bool	down_move;
		bool	left_move;
		bool	right_move;
		bool	up_left_move;
		bool	up_right_move;
		bool	down_left_move;
		bool	down_right_move;

	private:
		char	game_piece;
		int		x_coordinate;
		int		y_coordinate;
		int		num_available_moves;
		board	available_moves;
		board	king_border;
		bool	is_checked;
		bool	is_alive;
	};

	board	available_moves;
	int		num_available_moves;
	int		start_x;
	int		stary_y;

public:
	void	init(board& board_object, int start_king_y_coordinate, int start_king_x_coordinate);
	void	check(board& board_object, player& enemy_player);
	void	turn(board& board_object, player& enemy_player);
	bool	get_available_moves(int y_coordinate, int x_coordinate);
	int		get_num_available_moves(void) {return num_available_moves;}
	void	evaulate_moves(char game_piece, board& board_object, player& enemy_player);

	king	king_object;
};

