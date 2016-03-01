#include "player.h"


void	player::rook::init(board& board_object, int start_rook_y_coordinate, int start_rook_x_coordinate)
{
	srand(time(NULL));

	is_alive = true;
	game_piece = 'R';
	up_moves = 0;
	down_moves = 0;
	right_moves = 0;
	left_moves = 0;
	num_available_moves = 0;
	
	for(int i = 0; i < ROOK_HEIGHT; ++i)
	{
		for(int j = 0; j < ROOK_WIDTH; ++j)
		{
			available_moves.set_board_state(i, j, false);
		}
	}

	x_coordinate = start_rook_x_coordinate;
	y_coordinate = start_rook_y_coordinate;

	while(board_object.get_board_state(y_coordinate, x_coordinate) == true)			// board coordinate is occupied
	{
		x_coordinate = rand() % 7;
		y_coordinate = rand() % 7;
	} 		

	board_object.set_board_state(y_coordinate, x_coordinate, true);					// set this board state to true
	board_object.set_board_array(y_coordinate, x_coordinate, game_piece);			// draw the game piece on the board
}


void	player::rook::check(board& board_object, player enemy_player)
{
	// clear available moves every turn
	up_moves = 0;
	down_moves = 0;
	left_moves = 0;
	right_moves = 0;
	num_available_moves = 0;

	for(int i = 0; i < ROOK_HEIGHT; ++i)
	{
		for(int j = 0; j < ROOK_WIDTH; ++j)
		{
			available_moves.set_board_state(i, j, false);
		}
	}

	if(is_alive == true)
	{
		// check available up-down moves

		// check up moves
		for(int u = y_coordinate - 1; u >= 0; --u)
		{
			if((board_object.get_board_state(u, x_coordinate) == false))	// empty square
			{
				available_moves.set_board_state(u, x_coordinate, true);	// mark this square as an available move
				++num_available_moves;
				++up_moves;
			}
			else if(enemy_player.rook_object.get_x_coordinate() == x_coordinate && enemy_player.rook_object.get_y_coordinate() == u)
			{
				available_moves.set_board_state(u, x_coordinate, true);	// mark this square as an available move
				++num_available_moves;
				++up_moves;
				break;
			}
			else
			{
				break;
			}
		}

		// check down moves
		for(int d = y_coordinate + 1; d < ROOK_HEIGHT; ++d)
		{
			if((board_object.get_board_state(d, x_coordinate) == false))	// empty square
			{
				available_moves.set_board_state(d, x_coordinate, true);	// mark this square as an available move
				++num_available_moves;
				++down_moves;
			}
			else if(enemy_player.rook_object.get_x_coordinate() == x_coordinate && enemy_player.rook_object.get_y_coordinate() == d)
			{
				available_moves.set_board_state(d, x_coordinate, true);	// mark this square as an available move
				++num_available_moves;
				++down_moves;
				break;
			}
			else
			{
				break;
			}
		}

		// check available right-left moves

		// check right moves
		for(int r = x_coordinate + 1; r < ROOK_WIDTH - 1; ++r)
		{
			if((board_object.get_board_state(y_coordinate, r) == false))	// empty square
			{
				available_moves.set_board_state(y_coordinate, r, true);	// mark this square as an available move
				++num_available_moves;
				++right_moves;
			}
			else if(enemy_player.rook_object.get_x_coordinate() == r && enemy_player.rook_object.get_y_coordinate() == y_coordinate)
			{
				available_moves.set_board_state(y_coordinate, r, true);	// mark this square as an available move
				++num_available_moves;
				++right_moves;
				break;
			}
			else
			{
				break;
			}
		}

		// check left moves
		for(int l = x_coordinate - 1; l >= 0; --l)
		{
			if((board_object.get_board_state(y_coordinate, l) == false))	// empty square
			{
				available_moves.set_board_state(y_coordinate, l, true);	// mark this square as an available move
				++num_available_moves;
				++left_moves;
			}
			else if(enemy_player.rook_object.get_x_coordinate() == l && enemy_player.rook_object.get_y_coordinate() == y_coordinate)
			{
				available_moves.set_board_state(y_coordinate, l, true);	// mark this square as an available move
				++num_available_moves;
				++left_moves;
				break;
			}
			else
			{
				break;
			}
		}
	}
}


bool	player::rook::move(board& board_object, player& enemy_player, int new_y_coordinate, int new_x_coordinate)
{
	if(available_moves.get_board_state(new_y_coordinate,new_x_coordinate) == true)	// this is an available move
	{
		if(enemy_player.rook_object.get_y_coordinate() == new_y_coordinate && enemy_player.rook_object.get_x_coordinate() == new_x_coordinate)
		{
			// this square contains an enemy rook piece

			board_object.set_board_state(y_coordinate, x_coordinate, false);			// empty the current square

			// update board array
			board_object.set_board_array(y_coordinate, x_coordinate, 'O');
			board_object.set_board_array(new_y_coordinate, new_x_coordinate, game_piece);

			// delete enemy piece from board
			enemy_player.rook_object.set_is_alive(false);

			for(int i = 0; i < ROOK_HEIGHT; ++i)
			{
				for(int j = 0; j < ROOK_WIDTH; ++j)
				{
					enemy_player.rook_object.available_moves.set_board_state(i, j, false);
				}
			}

			enemy_player.rook_object.num_available_moves = 0;

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
			board_object.set_board_array(y_coordinate, x_coordinate, 'O');
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


bool	player::rook::get_available_moves(int y_coordinate, int x_coordinate)
{
	return available_moves.get_board_state(y_coordinate, x_coordinate);
}


void	player::rook::evaluate_moves(board& board_object, player& enemy_player)
{
	char	direction = NULL;
	ai_x = x_coordinate;
	ai_y = y_coordinate;

	// get enemy king coordinates
	int		enemy_king_x_coord = enemy_player.king_object.get_x_coordinate();
	int		enemy_king_y_coord = enemy_player.king_object.get_y_coordinate();

	for(int i = 0; i < ROOK_HEIGHT; ++i)
	{
		for(int j = 0; j < ROOK_WIDTH; ++j)
		{
			// test all squares the rook is able to move to
			if(get_available_moves(i, j) == true)
			{
				// test if check is possible
				if(i == enemy_king_y_coord)
				{
					if(x_coordinate < enemy_king_x_coord)
					{
						direction = 'R';				// test available moves right of this square
					}
					else
					{
						direction = 'L';				// test available moves left of this square
					}

					// check is possible from this square
					if(test_for_check(board_object, enemy_player, i, j, direction) == true)
					{
						// perform this move
						ai_x = j;
						ai_y = i;
						return;
					}
				}
				else if(j == enemy_king_x_coord)
				{
					if(y_coordinate < enemy_king_y_coord)
					{
						direction = 'D';				// test available moves right of this square
					}
					else
					{
						direction = 'U';				// test available moves left of this square
					}

					// check is possible from this square
					if(test_for_check(board_object, enemy_player, i, j, direction) == true)
					{
						// perform this move
						ai_x = j;
						ai_y = i;
						return;
					}
				}
			}
		}
	}
}


bool	player::rook::test_for_check(board& board_object, player& enemy_player, int new_y_coordinate, int new_x_coordinate, char direction)
{
	// get enemy king coordinates
	int		enemy_king_x_coord = enemy_player.king_object.get_x_coordinate();
	int		enemy_king_y_coord = enemy_player.king_object.get_y_coordinate();

	bool	checked = false;

	if(direction == 'U')
	{
		// check up moves
		for(int u = new_y_coordinate - 1; u >= 0; --u)
		{
			if((board_object.get_board_state(u, new_x_coordinate) == false))	// empty square
			{
				// do nothing
			}
			else if(enemy_player.king_object.get_x_coordinate() == new_x_coordinate && enemy_player.king_object.get_y_coordinate() == u)
			{
				checked = true;
				break;
			}
		}
	}
	else if(direction == 'D')
	{
		// check down moves
		for(int d = new_y_coordinate + 1; d < ROOK_HEIGHT; ++d)
		{
			if((board_object.get_board_state(d, new_x_coordinate) == false))	// empty square
			{
				// do nothing
			}
			else if(enemy_player.king_object.get_x_coordinate() == new_x_coordinate && enemy_player.king_object.get_y_coordinate() == d)
			{
				checked = true;
				break;
			}
		}
	}
	else if(direction == 'R')
	{
		// check right moves
		for(int r = new_x_coordinate + 1; r < ROOK_WIDTH - 1; ++r)
		{
			if((board_object.get_board_state(new_y_coordinate, r) == false))	// empty square
			{
				// do nothing
			}
			else if(enemy_player.king_object.get_x_coordinate() == r && enemy_player.king_object.get_y_coordinate() == new_y_coordinate)
			{
				checked = true;
				break;
			}
		}
	}
	else if(direction == 'L')
	{
		// check left moves
		for(int l = new_x_coordinate - 1; l >= 0; --l)
		{
			if((board_object.get_board_state(new_y_coordinate, l) == false))	// empty square
			{
				// do nothing
			}
			else if(enemy_player.king_object.get_x_coordinate() == l && enemy_player.king_object.get_y_coordinate() == new_y_coordinate)
			{
				checked = true;
				break;
			}
		}
	}

	return checked;
}


bool	player::rook::temp_move(board& board_object, player& enemy_player, int new_y_coordinate, int new_x_coordinate)
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


void	player::rook::temp_check(board& board_object, player enemy_player)
{
	// clear available moves every turn
	up_moves = 0;
	down_moves = 0;
	left_moves = 0;
	right_moves = 0;
	num_available_moves = 0;

	for(int i = 0; i < ROOK_HEIGHT; ++i)
	{
		for(int j = 0; j < ROOK_WIDTH; ++j)
		{
			available_moves.set_board_state(i, j, false);
		}
	}

	if(is_alive == true)
	{
		// check available up-down moves

		// check up moves
		for(int u = y_coordinate - 1; u >= 0; --u)
		{
			if((board_object.get_board_state(u, x_coordinate) == false) && (enemy_player.king_object.get_king_border(u, x_coordinate) == false))	// empty square
			{
				available_moves.set_board_state(u, x_coordinate, true);	// mark this square as an available move
				++num_available_moves;
				++up_moves;
			}
			else if((enemy_player.rook_object.get_x_coordinate() == x_coordinate && enemy_player.rook_object.get_y_coordinate() == u) && (enemy_player.king_object.get_king_border(u, x_coordinate) == false))
			{
				available_moves.set_board_state(u, x_coordinate, true);	// mark this square as an available move
				++num_available_moves;
				++up_moves;
				break;
			}
			else
			{
				break;
			}
		}

		// check down moves
		for(int d = y_coordinate + 1; d < ROOK_HEIGHT; ++d)
		{
			if((board_object.get_board_state(d, x_coordinate) == false) && (enemy_player.king_object.get_king_border(d, x_coordinate) == false))	// empty square
			{
				available_moves.set_board_state(d, x_coordinate, true);	// mark this square as an available move
				++num_available_moves;
				++down_moves;
			}
			else if((enemy_player.rook_object.get_x_coordinate() == x_coordinate && enemy_player.rook_object.get_y_coordinate() == d) && (enemy_player.king_object.get_king_border(d, x_coordinate) == false))
			{
				available_moves.set_board_state(d, x_coordinate, true);	// mark this square as an available move
				++num_available_moves;
				++down_moves;
				break;
			}
			else
			{
				break;
			}
		}

		// check available right-left moves

		// check right moves
		for(int r = x_coordinate + 1; r < ROOK_WIDTH - 1; ++r)
		{
			if((board_object.get_board_state(y_coordinate, r) == false) && (enemy_player.king_object.get_king_border(y_coordinate, r) == false))	// empty square
			{
				available_moves.set_board_state(y_coordinate, r, true);	// mark this square as an available move
				++num_available_moves;
				++right_moves;
			}
			else if((enemy_player.rook_object.get_x_coordinate() == r && enemy_player.rook_object.get_y_coordinate() == y_coordinate) && (enemy_player.king_object.get_king_border(y_coordinate, r) == false))
			{
				available_moves.set_board_state(y_coordinate, r, true);	// mark this square as an available move
				++num_available_moves;
				++right_moves;
				break;
			}
			else
			{
				break;
			}
		}

		// check left moves
		for(int l = x_coordinate - 1; l >= 0; --l)
		{
			if((board_object.get_board_state(y_coordinate, l) == false) && (enemy_player.king_object.get_king_border(y_coordinate, l) == false))	// empty square
			{
				available_moves.set_board_state(y_coordinate, l, true);	// mark this square as an available move
				++num_available_moves;
				++left_moves;
			}
			else if((enemy_player.rook_object.get_x_coordinate() == l && enemy_player.rook_object.get_y_coordinate() == y_coordinate) && (enemy_player.king_object.get_king_border(y_coordinate, l) == false))
			{
				available_moves.set_board_state(y_coordinate, l, true);	// mark this square as an available move
				++num_available_moves;
				++left_moves;
				break;
			}
			else
			{
				break;
			}
		}
	}
}