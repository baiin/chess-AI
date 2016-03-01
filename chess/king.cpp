#include "player.h"


void	player::king::init(board& board_object, int start_king_y_coordinate, int start_king_x_coordinate)
{
	srand(time(NULL));

	is_alive = true;
	is_checked = false;
	game_piece = 'K';
	up_move = false;
	down_move = false;
	left_move = false;
	right_move = false;
	up_left_move = false;
	up_right_move = false;
	down_left_move = false;
	down_right_move = false;
	num_available_moves = 0;
	
	for(int i = 0; i < KING_HEIGHT; ++i)
	{
		for(int j = 0; j < KING_WIDTH; ++j)
		{
			available_moves.set_board_state(i, j, false);
			king_border.set_board_state(i, j, false);
		}
	}

	x_coordinate = start_king_x_coordinate;
	y_coordinate = start_king_y_coordinate;

	while(board_object.get_board_state(y_coordinate, x_coordinate) == true)			// board coordinate is occupied
	{
		x_coordinate = rand() % 7;
		y_coordinate = rand() % 7;
	} 		

	board_object.set_board_state(y_coordinate, x_coordinate, true);					// set this board state to true
	board_object.set_board_array(y_coordinate, x_coordinate, game_piece);			// draw the game piece on the board
}


void	player::king::check(board& board_object, player enemy_player)
{
	// clear available moves every turn
	up_move = false;
	down_move = false;
	left_move = false;
	right_move = false;
	up_left_move = false;
	up_right_move = false;
	down_left_move = false;
	down_right_move = false;
	num_available_moves = 0;

	for(int i = 0; i < KING_HEIGHT; ++i)
	{
		for(int j = 0; j < KING_WIDTH; ++j)
		{
			available_moves.set_board_state(i, j, false);
			king_border.set_board_state(i, j, false);
		}
	}

	// check left move
	if((x_coordinate - 1 >= 0) && (board_object.get_board_state(y_coordinate, x_coordinate - 1) == false) 
		&& (enemy_player.king_object.get_king_border(y_coordinate, x_coordinate - 1) == false) && (enemy_player.get_available_moves(y_coordinate, x_coordinate - 1) == false))
	{
		// empty square
		available_moves.set_board_state(y_coordinate, x_coordinate - 1, true);	// mark this square as an available move
		++num_available_moves;
		left_move = true;
	}
	else if((x_coordinate - 1 >= 0) && (enemy_player.rook_object.get_y_coordinate() == y_coordinate && enemy_player.rook_object.get_x_coordinate() == x_coordinate - 1))
	{
		available_moves.set_board_state(y_coordinate, x_coordinate - 1, true);	// mark this square as an available move
		++num_available_moves;
		left_move = true;
	}

	// check right move
	if((x_coordinate + 1 < KING_WIDTH - 1) && (board_object.get_board_state(y_coordinate, x_coordinate + 1) == false) 
		&& (enemy_player.king_object.get_king_border(y_coordinate, x_coordinate + 1) == false) && (enemy_player.get_available_moves(y_coordinate, x_coordinate + 1) == false))
	{
		// empty square
		available_moves.set_board_state(y_coordinate, x_coordinate + 1, true);	// mark this square as an available move
		++num_available_moves;
		right_move = true;
	}
	else if((x_coordinate + 1 < KING_WIDTH - 1) && (enemy_player.rook_object.get_y_coordinate() == y_coordinate && enemy_player.rook_object.get_x_coordinate() == x_coordinate + 1))
	{
		available_moves.set_board_state(y_coordinate, x_coordinate + 1, true);	// mark this square as an available move
		++num_available_moves;
		right_move = true;
	}

	// check up move
	if((y_coordinate - 1 >= 0) && (board_object.get_board_state(y_coordinate - 1, x_coordinate) == false) 
		&& (enemy_player.king_object.get_king_border(y_coordinate - 1, x_coordinate) == false) && (enemy_player.get_available_moves(y_coordinate - 1, x_coordinate) == false))
	{
		// empty square
		available_moves.set_board_state(y_coordinate - 1, x_coordinate, true);	// mark this square as an available move
		++num_available_moves;
		up_move = true;
	}
	else if((y_coordinate - 1 >= 0) && (enemy_player.rook_object.get_y_coordinate() == y_coordinate - 1 && enemy_player.rook_object.get_x_coordinate() == x_coordinate))
	{
		available_moves.set_board_state(y_coordinate - 1, x_coordinate, true);	// mark this square as an available move
		++num_available_moves;
		up_move = true;
	}

	// check down move
	if((y_coordinate + 1 < KING_HEIGHT) && (board_object.get_board_state(y_coordinate + 1, x_coordinate) == false) 
		&& (enemy_player.king_object.get_king_border(y_coordinate + 1, x_coordinate) == false) && (enemy_player.get_available_moves(y_coordinate + 1, x_coordinate) == false))
	{
		// empty square
		available_moves.set_board_state(y_coordinate + 1, x_coordinate, true);	// mark this square as an available move
		++num_available_moves;
		down_move = true;
	}
	else if((y_coordinate + 1 < KING_HEIGHT) && (enemy_player.rook_object.get_y_coordinate() == y_coordinate + 1 && enemy_player.rook_object.get_x_coordinate() == x_coordinate))
	{
		available_moves.set_board_state(y_coordinate + 1, x_coordinate, true);	// mark this square as an available move
		++num_available_moves;
		down_move = true;
	}

	// check up-left move
	if((x_coordinate - 1 >= 0) && (y_coordinate - 1 >= 0) && (board_object.get_board_state(y_coordinate - 1, x_coordinate - 1) == false) 
		&& (enemy_player.king_object.get_king_border(y_coordinate - 1, x_coordinate - 1) == false) && (enemy_player.get_available_moves(y_coordinate - 1, x_coordinate - 1) == false))
	{
		available_moves.set_board_state(y_coordinate - 1, x_coordinate - 1, true);	// mark this square as an available move
		++num_available_moves;
		up_left_move = true;
	}
	else if((x_coordinate - 1 >= 0 && y_coordinate - 1 >= 0) && (enemy_player.rook_object.get_y_coordinate() == y_coordinate - 1 && enemy_player.rook_object.get_x_coordinate() == x_coordinate - 1))
	{
		available_moves.set_board_state(y_coordinate - 1, x_coordinate - 1, true);	// mark this square as an available move
		++num_available_moves;
		up_left_move = true;
	}

	// check up-right move
	if((x_coordinate + 1 < KING_WIDTH - 1) && (y_coordinate - 1 >= 0) && (board_object.get_board_state(y_coordinate - 1, x_coordinate + 1) == false) 
		&& (enemy_player.king_object.get_king_border(y_coordinate - 1, x_coordinate + 1) == false) && (enemy_player.get_available_moves(y_coordinate - 1, x_coordinate + 1) == false))
	{
		available_moves.set_board_state(y_coordinate - 1, x_coordinate + 1, true);	// mark this square as an available move
		++num_available_moves;
		up_right_move = true;
	}
	else if((x_coordinate + 1 < KING_WIDTH - 1 && y_coordinate - 1 >= 0) && (enemy_player.rook_object.get_y_coordinate() == y_coordinate - 1 && enemy_player.rook_object.get_x_coordinate() == x_coordinate + 1))
	{
		available_moves.set_board_state(y_coordinate - 1, x_coordinate + 1, true);	// mark this square as an available move
		++num_available_moves;
		up_right_move = true;
	}

	// check down-left move
	if((x_coordinate - 1 >= 0) && (y_coordinate + 1 < KING_HEIGHT) && (board_object.get_board_state(y_coordinate + 1, x_coordinate - 1) == false) 
		&& (enemy_player.king_object.get_king_border(y_coordinate + 1, x_coordinate - 1) == false) && (enemy_player.get_available_moves(y_coordinate + 1, x_coordinate - 1) == false))
	{
		available_moves.set_board_state(y_coordinate + 1, x_coordinate - 1, true);	// mark this square as an available move
		++num_available_moves;
		down_left_move = true;
	}
	else if((x_coordinate - 1 >= 0 && y_coordinate + 1 < KING_HEIGHT) && (enemy_player.rook_object.get_y_coordinate() == y_coordinate + 1 && enemy_player.rook_object.get_x_coordinate() == x_coordinate - 1))
	{
		available_moves.set_board_state(y_coordinate + 1, x_coordinate - 1, true);	// mark this square as an available move
		++num_available_moves;
		down_left_move = true;
	}

	// check down-right move
	if((x_coordinate + 1 < KING_WIDTH - 1) && (y_coordinate + 1 < KING_HEIGHT) && (board_object.get_board_state(y_coordinate + 1, x_coordinate + 1) == false) 
		&& (enemy_player.king_object.get_king_border(y_coordinate + 1, x_coordinate + 1) == false) && (enemy_player.get_available_moves(y_coordinate + 1, x_coordinate + 1) == false))
	{
		available_moves.set_board_state(y_coordinate + 1, x_coordinate + 1, true);	// mark this square as an available move
		++num_available_moves;
		down_right_move = true;
	}
	else if((x_coordinate + 1 < KING_WIDTH - 1 && y_coordinate + 1 < KING_HEIGHT) && (enemy_player.rook_object.get_y_coordinate() == y_coordinate + 1 && enemy_player.rook_object.get_x_coordinate() == x_coordinate + 1))
	{
		available_moves.set_board_state(y_coordinate + 1, x_coordinate + 1, true);	// mark this square as an available move
		++num_available_moves;
		down_right_move = true;
	}
}


bool	player::king::move(board& board_object, player& enemy_player, int new_y_coordinate, int new_x_coordinate)
{
	if(available_moves.get_board_state(new_y_coordinate,new_x_coordinate) == true)	// this is an available move
	{
		if(enemy_player.rook_object.get_y_coordinate() == new_y_coordinate && enemy_player.rook_object.get_x_coordinate() == new_x_coordinate)
		{
			board_object.set_board_state(y_coordinate, x_coordinate, false);			// empty the current square

			// update board array
			board_object.set_board_array(y_coordinate, x_coordinate, 'O');
			board_object.set_board_array(new_y_coordinate, new_x_coordinate, game_piece);

			// delete enemy piece from board
			enemy_player.rook_object.set_is_alive(false);

			for(int i = 0; i < KING_HEIGHT; ++i)
			{
				for(int j = 0; j < KING_WIDTH; ++j)
				{
					enemy_player.rook_object.set_available_moves(i, j, false);
				}
			}

			enemy_player.rook_object.set_num_available_moves(0);

			// update rook coordinates
			x_coordinate = new_x_coordinate;
			y_coordinate = new_y_coordinate;
		}	
		else
		{
			// update board state
			board_object.set_board_state(y_coordinate, x_coordinate, false);			// empty the current square
			board_object.set_board_state(new_y_coordinate, new_x_coordinate, true);		// place the rook in the new coordinate

			// update board array
			board_object.set_board_array(y_coordinate, x_coordinate, 'O');
			board_object.set_board_array(new_y_coordinate, new_x_coordinate, game_piece);

			// update king coordinates
			x_coordinate = new_x_coordinate;
			y_coordinate = new_y_coordinate;
		}
	}	
	else
	{
		return false;
	}

	return true;
}


bool	player::king::temp_move(board& board_object, player& enemy_player, int new_y_coordinate, int new_x_coordinate)
{
	if(available_moves.get_board_state(new_y_coordinate,new_x_coordinate) == true)	// this is an available move
	{
		if(enemy_player.rook_object.get_y_coordinate() == new_y_coordinate && enemy_player.rook_object.get_x_coordinate() == new_x_coordinate)
		{
			// this square contains an enemy rook piece

			board_object.set_board_state(y_coordinate, x_coordinate, false);			// empty the current square
			board_object.set_board_state(new_y_coordinate, new_x_coordinate, true);		// place the rook in the new coordinate

			// update board array
			board_object.set_board_array(y_coordinate, x_coordinate, 'O');
			board_object.set_board_array(new_y_coordinate, new_x_coordinate, game_piece);

			// update rook coordinates
			x_coordinate = new_x_coordinate;
			y_coordinate = new_y_coordinate;

		}
		else if(enemy_player.king_object.get_y_coordinate() == new_y_coordinate && enemy_player.king_object.get_x_coordinate() == new_x_coordinate)
		{
			// this square contains an enemy king piece
		}

		else
		{
			// update board state
			board_object.set_board_state(y_coordinate, x_coordinate, false);			// empty the current square
			board_object.set_board_state(new_y_coordinate, new_x_coordinate, true);		// place the rook in the new coordinate

			// update board array
			if(enemy_player.rook_object.get_y_coordinate() == y_coordinate && enemy_player.rook_object.get_x_coordinate() == x_coordinate)
			{
				board_object.set_board_array(y_coordinate, x_coordinate, 'R');
			}
			else
			{
				board_object.set_board_array(y_coordinate, x_coordinate, 'O');
			}

			
			board_object.set_board_array(new_y_coordinate, new_x_coordinate, game_piece);

			// update rook coordinates
			x_coordinate = new_x_coordinate;
			y_coordinate = new_y_coordinate;
		}
	}
	else
	{
		return false;
	}

	return true;
}


bool	player::king::get_available_moves(int y_coordinate, int x_coordinate)
{
	return available_moves.get_board_state(y_coordinate, x_coordinate);
}


bool	player::king::get_king_border(int y_coordinate, int x_coordinate)
{
	return king_border.get_board_state(y_coordinate, x_coordinate);
}


void	player::king::create_king_border(board& board_object)
{
	for(int i = 0; i < KING_HEIGHT; ++i)
	{
		for(int j = 0; j < KING_WIDTH; ++j)
		{
			king_border.set_board_state(i, j - 1, false);
		}
	}

	// check left move
	if((x_coordinate - 1 >= 0))
	{
		// empty square
		king_border.set_board_state(y_coordinate, x_coordinate - 1, true);
	}

	// check right move
	if((x_coordinate + 1 < KING_WIDTH - 1))
	{
		// empty square
		king_border.set_board_state(y_coordinate, x_coordinate + 1, true);
	}

	// check up move
	if((y_coordinate - 1 >= 0))
	{
		// empty square
		king_border.set_board_state(y_coordinate - 1, x_coordinate, true);
	}

	// check down move
	if((y_coordinate + 1 < KING_HEIGHT))
	{
		// empty square
		king_border.set_board_state(y_coordinate + 1, x_coordinate, true);
	}

	// check up-left move
	if((x_coordinate - 1 >= 0) && (y_coordinate - 1 >= 0))
	{
		king_border.set_board_state(y_coordinate - 1, x_coordinate - 1, true);
	}

	// check up-right move
	if((x_coordinate + 1 < KING_WIDTH - 1) && (y_coordinate - 1 >= 0))
	{
		king_border.set_board_state(y_coordinate - 1, x_coordinate + 1, true);
	}

	// check down-left move
	if((x_coordinate - 1 >= 0) && (y_coordinate + 1 < KING_HEIGHT))
	{
		king_border.set_board_state(y_coordinate + 1, x_coordinate - 1, true);
	}

	// check down-right move
	if((x_coordinate + 1 < KING_WIDTH - 1) && (y_coordinate + 1 < KING_HEIGHT))
	{
		king_border.set_board_state(y_coordinate + 1, x_coordinate + 1, true);
	}
}


bool	player::king::test_for_check(board& board_object, player enemy_player, int y_coord, int x_coord)
{
	bool	checked = false;

	int		store_x_coordinate = x_coord;
	int		store_y_coordinate = y_coord;

	// remove the king from the current square
	board_object.set_board_state(store_y_coordinate, store_x_coordinate, false);
	board_object.set_board_array(store_y_coordinate, store_x_coordinate, 'O');

	// re-establish enemy available moves
	enemy_player.check(board_object, enemy_player);
	
	// test if new coordinates lie in the enemies available move
	if(enemy_player.get_available_moves(y_coord, x_coord) == true)
	{
		// king is checked in this move
		checked = true;
	}
	else
	{
		checked = false;
	}

	// re-place the king in the previous square
	board_object.set_board_state(store_y_coordinate, store_x_coordinate, true);
	board_object.set_board_array(store_y_coordinate, store_x_coordinate, 'K');
	
	// re-establish enemy available moves
	enemy_player.check(board_object, enemy_player);

	return checked;
}


void	player::king::get_available_check_moves(board& board_object, player enemy_player, int y_coordinate, int x_coordinate)
{
	// check left move
	if((available_moves.get_board_state(y_coordinate, x_coordinate - 1) == true) && (test_for_check(board_object, enemy_player, y_coordinate, x_coordinate - 1) == true))
	{
		available_moves.set_board_state(y_coordinate, x_coordinate - 1, false);
		--num_available_moves;
		left_move = false;
	}

	// check right move
	if((available_moves.get_board_state(y_coordinate, x_coordinate + 1) == true) && (test_for_check(board_object, enemy_player, y_coordinate, x_coordinate + 1) == true))
	{
		available_moves.set_board_state(y_coordinate, x_coordinate + 1, false);
		--num_available_moves;
		right_move = false;
	}

	// check up move
	if((available_moves.get_board_state(y_coordinate - 1, x_coordinate) == true) && (test_for_check(board_object, enemy_player, y_coordinate - 1, x_coordinate) == true))
	{
		available_moves.set_board_state(y_coordinate - 1, x_coordinate, false);
		--num_available_moves;
		up_move = false;
	}

	// check down move
	if((available_moves.get_board_state(y_coordinate + 1, x_coordinate) == true) && (test_for_check(board_object, enemy_player, y_coordinate + 1, x_coordinate) == true))
	{
		available_moves.set_board_state(y_coordinate + 1, x_coordinate, false);
		--num_available_moves;
		down_move = false;
	}

	// check up-left move
	if((available_moves.get_board_state(y_coordinate - 1, x_coordinate - 1) == true) && (test_for_check(board_object, enemy_player, y_coordinate - 1, x_coordinate - 1) == true))
	{
		available_moves.set_board_state(y_coordinate - 1, x_coordinate - 1, false);
		--num_available_moves;
		up_left_move = false;
	}

	// check up-right move
	if((available_moves.get_board_state(y_coordinate - 1, x_coordinate + 1) == true) && (test_for_check(board_object, enemy_player, y_coordinate - 1, x_coordinate + 1) == true))
	{
		available_moves.set_board_state(y_coordinate - 1, x_coordinate + 1, false);
		--num_available_moves;
		up_right_move = false;
	}

	// check down-left move
	if((available_moves.get_board_state(y_coordinate + 1, x_coordinate - 1) == true) && (test_for_check(board_object, enemy_player, y_coordinate + 1, x_coordinate - 1) == true))
	{
		available_moves.set_board_state(y_coordinate + 1, x_coordinate - 1, false);
		--num_available_moves;
		down_left_move = false;
	}

	// check down-right move
	if((available_moves.get_board_state(y_coordinate + 1, x_coordinate + 1) == true) && (test_for_check(board_object, enemy_player, y_coordinate + 1, x_coordinate + 1) == true))
	{
		available_moves.set_board_state(y_coordinate + 1, x_coordinate + 1, false);
		--num_available_moves;
		down_right_move = false;
	}
}