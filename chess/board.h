#pragma once
#include <iostream>
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
