#include "board.h"


void	board::board_init()
{
	char	temp_board_array[BOARD_HEIGHT][BOARD_WIDTH] = {	{"OOOOOOOO"},
															{"OOOOOOOO"},
															{"OOOOOOOO"},
															{"OOOOOOOO"},
															{"OOOOOOOO"},
															{"OOOOOOOO"},
															{"OOOOOOOO"},
															{"OOOOOOOO"}	};

	for(int i = 0; i < BOARD_HEIGHT; ++i)
	{
		for(int j = 0; j < BOARD_WIDTH; ++j)
		{
			board_array[i][j] = temp_board_array[i][j];
			board_state[i][j] = false;						// board coordinate is empty
		}
	}
}


void	board::board_display()
{
	for(int i = 0; i < BOARD_HEIGHT; ++i)
	{
		for(int j = 0; j < BOARD_WIDTH; ++j)
		{
			cout << board_array[i][j] << " ";
		}

		cout << endl;
	}
}


void	board::board_update_game_state()
{
	for(int i = 0; i < BOARD_HEIGHT; ++i)
	{
		for(int j = 0; j < BOARD_WIDTH; ++j)
		{
			// coordinate does not have a game piece
			if(board_array[i][j] == 'X' || board_array[i][j] == 'O')
			{
				board_state[i][j] = false;
			}
			else
			{
				board_state[i][j] = true;
			}
		}
	}
}


char	board::get_board_array(int y_coordinate, int x_coordinate)
{
	return board_array[y_coordinate][x_coordinate];
}


void	board::set_board_array(int y_coordinate, int x_coordinate, char char_value)
{
	board_array[y_coordinate][x_coordinate] = char_value;
}


bool	board::get_board_state(int y_coordinate, int x_coordinate)
{
	return board_state[y_coordinate][x_coordinate];
}


void	board::set_board_state(int y_coordinate, int x_coordinate, bool bool_value)
{
	board_state[y_coordinate][x_coordinate] = bool_value;
}