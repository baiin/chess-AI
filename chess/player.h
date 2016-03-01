#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "board.h"
using namespace std;

const int	PLAYER_WIDTH = 9;
const int	PLAYER_HEIGHT = 8;

class player
{
private:
	static const int	ROOK_WIDTH = 9;
	static const int	ROOK_HEIGHT = 8;

	class rook
	{
	public:
		void	init(board& board_object, int start_rook_y_coordinate, int start_rook_x_coordinate);
		void	check(board& board_object, player enemy_player);
		bool	move(board& board_object, player& enemy_player, int new_y_coordinate, int new_x_coordinate);
		bool	get_available_moves(int y_coordinate, int x_coordinate);
		int		get_x_coordinate(void) {return x_coordinate;}
		int		get_y_coordinate(void) {return y_coordinate;}
		int		get_num_available_moves(void) {return num_available_moves;}
		bool	get_is_alive(void) {return is_alive;}
		void	set_is_alive(bool new_is_alive_status) {is_alive = new_is_alive_status;}
		void	set_available_moves(int y_coordinate, int x_coordinate, bool bool_value) {available_moves.set_board_state(y_coordinate, x_coordinate, bool_value);}
		void	set_num_available_moves(int new_num_moves) {num_available_moves = new_num_moves;}
		void	evaluate_moves(board& board_object, player& enemy_player);
		bool	test_for_check(board& board_object, player& enemy_player, int new_y_coordinate, int new_x_coordinate, char direction);
		int		get_ai_x(void) {return ai_x;}
		int		get_ai_y(void) {return ai_y;}
		bool	temp_move(board& board_object, player& enemy_player, int new_y_coordinate, int new_x_coordinate);
		void	temp_check(board& board_object, player enemy_player);

		int		up_moves;
		int		down_moves;
		int		left_moves;
		int		right_moves;

	private:
		int		ai_x;
		int		ai_y;
		char	game_piece;
		int		x_coordinate;
		int		y_coordinate;
		int		num_available_moves;
		board	available_moves;
		bool	is_alive;
	};

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
		bool	temp_move(board& board_object, player& enemy_player, int new_y_coordinate, int new_x_coordinate);

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
	int		ai_x;
	int		ai_y;

public:
	void	init(board& board_object, int start_king_y_coordinate, int start_king_x_coordinate, int start_rook_y_coordinate, int start_rook_x_coordinate);
	void	check(board& board_object, player& enemy_player);
	void	turn(board& board_object, player& enemy_player);
	bool	get_available_moves(int y_coordinate, int x_coordinate);
	int		get_num_available_moves(void) {return num_available_moves;}
	int		evaulate_moves(char game_piece, board& board_object, player& enemy_player);
	void	defense_move(board& board_object, player& enemy_player);

	king	king_object;
	rook	rook_object;
};

