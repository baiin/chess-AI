#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int	BOARD_WIDTH = 9;
const int	BOARD_HEIGHT = 8;

class board
{
public:
	void	board_init();
	void	board_display();
	void	board_update_game_state();
	char	get_board_array(int y_coordinate, int x_coordinate);
	void	set_board_array(int y_coordinate, int x_coordinate, char char_value);
	bool	get_board_state(int y_coordinate, int x_coordinate);
	void	set_board_state(int y_coordinate, int x_coordinate, bool bool_value);

private:
	char	board_array[BOARD_HEIGHT][BOARD_WIDTH];
	bool	board_state[BOARD_HEIGHT][BOARD_WIDTH];
};


const int	PLAYER_WIDTH = 9;
const int	PLAYER_HEIGHT = 8;

class player
{
public:
	void	init(board& board_object);
	void	check(board& board_object, player enemy_player);
	void	turn(board& board_object);
	bool	get_available_moves(int y_coordinate, int x_coordinate);
	int		get_num_available_moves(void) {return num_available_moves;}
	
private:
	king	king_object;
	rook	rook_object;
	board	available_moves;
	int		num_available_moves;
};


const int	ROOK_WIDTH = 9;
const int	ROOK_HEIGHT = 8;

class rook
{
public:
	void	init(board& board_object);
	void	check(board& board_object, player enemy_player);
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


const int	KING_WIDTH = 9;
const int	KING_HEIGHT = 8;

class king
{
public:
	void	init(board& board_object);
	void	check(board& board_object, player enemy_player);
	bool	move(board& board_object, int new_y_coordinate, int new_x_coordinate);
	bool	get_available_moves(int y_coordinate, int x_coordinate);
	int		get_x_coordinate(void) {return x_coordinate;}
	int		get_y_coordinate(void) {return y_coordinate;}
	int		get_num_available_moves(void) {return num_available_moves;}

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
};


