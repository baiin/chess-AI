#include "player.h"


void	player::init(board& board_object, int start_king_y_coordinate, int start_king_x_coordinate, int start_rook_y_coordinate, int start_rook_x_coordinate)
{
	rook_object.init(board_object, start_rook_y_coordinate, start_rook_x_coordinate);
	king_object.init(board_object, start_king_y_coordinate, start_king_x_coordinate);

	num_available_moves = 0;
	
	for(int i = 0; i < PLAYER_HEIGHT; ++i)
	{
		for(int j = 0; j < PLAYER_WIDTH; ++j)
		{
			available_moves.set_board_state(i, j, false);
		}
	}
}


void	player::check(board& board_object, player& enemy_player)
{
	rook_object.check(board_object, enemy_player);
	king_object.check(board_object, enemy_player);
	king_object.create_king_border(board_object);

	num_available_moves = 0;

	for(int i = 0; i < PLAYER_HEIGHT; ++i)
	{
		for(int j = 0; j < PLAYER_WIDTH; ++j)
		{
			available_moves.set_board_state(i, j, false);
		}
	}

	for(int i = 0; i < PLAYER_HEIGHT; ++i)
	{
		for(int j = 0; j < PLAYER_WIDTH; ++j)
		{
			if(king_object.get_available_moves(i, j) == true)
			{
				available_moves.set_board_state(i, j, true);
				++num_available_moves;
			}
			else if(rook_object.get_available_moves(i, j) == true)
			{
				available_moves.set_board_state(i, j, true);
				++num_available_moves;
			}
		}
	}
}


void	player::turn(board& board_object, player& enemy_player)
{
	bool	turn = false;
	char	game_piece;
	int		x_coordinate;
	int		y_coordinate;

	enemy_player.king_object.create_king_border(board_object);
	king_object.check(board_object, enemy_player);
	if(king_object.test_for_check(board_object, enemy_player, king_object.get_y_coordinate(), king_object.get_x_coordinate()) == true)
	{
		king_object.get_available_check_moves(board_object, enemy_player, king_object.get_y_coordinate(), king_object.get_x_coordinate());

		if(king_object.get_num_available_moves() > 0)
		{
			cout << "CHECK" << endl;
			king_object.set_is_checked(true);
		}
		else
		{
			cout << "CHECKMATE" << endl;
			system("pause");
			return;
		}
	}
	else
	{
		king_object.set_is_checked(false);
	}

	if(king_object.get_is_checked() == true)
	{
		king_object.get_available_check_moves(board_object, enemy_player, king_object.get_y_coordinate(), king_object.get_x_coordinate());
	}

	num_available_moves = 0;
	num_available_moves += rook_object.get_num_available_moves();
	num_available_moves += king_object.get_num_available_moves();
	enemy_player.king_object.check(board_object, enemy_player);
	enemy_player.king_object.create_king_border(board_object);
	king_object.check(board_object, enemy_player);
	king_object.create_king_border(board_object);

	do
	{

		if(king_object.get_is_checked() == true)
		{
			game_piece = 'K';
		}
		else
		{
			cout << "AVAILABLE MOVES: " << num_available_moves << endl;
			system("pause");

			/*cout << "WHICH GAME PIECE: ";
			cin  >> game_piece;
			game_piece = toupper(game_piece);*/

			enemy_player.king_object.create_king_border(board_object);
			king_object.check(board_object, enemy_player);
			king_object.get_available_check_moves(board_object, enemy_player, king_object.get_y_coordinate(), king_object.get_x_coordinate());
			rook_object.check(board_object, enemy_player);

			int		king_moves_rook = evaulate_moves('R', board_object, enemy_player);
			int		king_moves_king = evaulate_moves('K', board_object, enemy_player);
			
			if(king_moves_rook < king_moves_king)
			{
				game_piece = 'R';
			}
			else
			{

				if(enemy_player.king_object.get_king_border(rook_object.get_y_coordinate(), rook_object.get_x_coordinate()) == true && rook_object.get_is_alive() == true)
				{
					game_piece = 'R';
				}
				else
				{
					game_piece = 'K';
				}
			}
		}

		if(game_piece == 'K')
		{
			do
			{
				enemy_player.king_object.create_king_border(board_object);
				king_object.check(board_object, enemy_player);
				king_object.get_available_check_moves(board_object, enemy_player, king_object.get_y_coordinate(), king_object.get_x_coordinate());
				
				if(rook_object.get_is_alive() == true)
				{
					evaulate_moves(game_piece, board_object, enemy_player);
				}
				else
				{
					defense_move(board_object, enemy_player);
				}

				cout << "K: [" << king_object.get_y_coordinate() << " , " << king_object.get_x_coordinate() << "]" << endl;
				cout << "AVAILABLE MOVES: " << king_object.get_num_available_moves() << endl;
				
				x_coordinate = ai_x;
				y_coordinate = ai_y;
				
				if(king_object.get_available_moves(y_coordinate, x_coordinate) == false)
				{
					cout << "INVALID MOVE: TRY AGAIN" << endl;
				}

				if(king_object.test_for_check(board_object, enemy_player, y_coordinate, x_coordinate) == true)
				{
					cout << "CHECK MOVE: TRY AGAIN" << endl;
				}

			} while((king_object.get_available_moves(y_coordinate, x_coordinate) == false) || (king_object.test_for_check(board_object, enemy_player, y_coordinate, x_coordinate) == true));

			king_object.move(board_object, enemy_player, y_coordinate, x_coordinate);
			king_object.check(board_object, enemy_player);
			king_object.create_king_border(board_object);

			turn = true;
		}
		else if(game_piece == 'R')
		{
			if(rook_object.get_is_alive() == true)
			{
				do
				{
					enemy_player.king_object.create_king_border(board_object);
					rook_object.check(board_object, enemy_player);
					//rook_object.evaluate_moves(board_object, enemy_player);
					
					if(rook_object.get_num_available_moves() > 0)
					{
						evaulate_moves(game_piece, board_object, enemy_player);
					}
					else
					{
						cout << "ROOK NO AVAILABLE MOVES" << endl;
					}

					cout << "R: [" << rook_object.get_y_coordinate() << " , " << rook_object.get_x_coordinate() << "]" << endl;
					cout << "AVAILABLE MOVES: " << rook_object.get_num_available_moves() << endl;
					//cout << "PREFERRED MOVE: " << "[" << rook_object.get_ai_y() << " , " << rook_object.get_ai_x() << "]" << endl;
					cout << "LEFT MOVES: " << rook_object.left_moves << endl;
					cout << "RIGHT MOVES: " << rook_object.right_moves << endl;
					cout << "UP MOVES: " << rook_object.up_moves << endl;
					cout << "DOWN MOVES: " << rook_object.down_moves << endl;
					/*cout << "Y-COORD: ";
					cin  >> y_coordinate;
					cout << "X-COORD: ";
					cin  >> x_coordinate;*/

					x_coordinate = ai_x;
					y_coordinate = ai_y;

					if(rook_object.get_available_moves(y_coordinate, x_coordinate) == false)
					{
						cout << "INVALID MOVE: TRY AGAIN" << endl;
						cout << endl;
					}
				} while(rook_object.get_available_moves(y_coordinate, x_coordinate) == false);

				rook_object.move(board_object, enemy_player, y_coordinate, x_coordinate);
				rook_object.check(board_object, enemy_player);


				turn = true;
			}
			else
			{
				cout << "ROOK IS ALREADY CAPTURED" << endl;
			}
		}
	} while(turn == false);
}


bool	player::get_available_moves(int y_coordinate, int x_coordinate)
{
	return available_moves.get_board_state(y_coordinate, x_coordinate);
}


int		player::evaulate_moves(char game_piece, board& board_object, player& enemy_player)
{
	int		king_moves;

	if(game_piece == 'R')
	{
		// compare available moves to this number to determine if it is better move
		enemy_player.king_object.check(board_object, *this);
		enemy_player.king_object.create_king_border(board_object);
		king_moves = enemy_player.king_object.get_num_available_moves();
		int		best_y = rook_object.get_y_coordinate();
		int		best_x = rook_object.get_x_coordinate();

		for(int i = 0; i < PLAYER_HEIGHT; ++i)
		{
			for(int j = 0; j < PLAYER_WIDTH; ++j)
			{
				if(rook_object.get_available_moves(i, j) == true)	// square is one of rook available moves
				{
					// check if move is within enemy king border
					if(enemy_player.king_object.get_king_border(i, j) == false) // square is not in enemy king border
					{
						// see how many available moves king will have if rook moved here
						int		temp_x = rook_object.get_x_coordinate();
						int		temp_y = rook_object.get_y_coordinate();

						rook_object.temp_move(board_object, enemy_player, i, j);	// temporarily move rook to new square
						rook_object.check(board_object, enemy_player);	// update available moves 
						check(board_object, enemy_player);

						// count how many moves king has 
						enemy_player.king_object.check(board_object, *this);
						enemy_player.king_object.create_king_border(board_object);

						int		enemy_king_moves = enemy_player.king_object.get_num_available_moves();
						
						if(king_moves >= enemy_king_moves)
						{
							king_moves = enemy_king_moves;
							best_y = i;
							best_x = j;
						}

						rook_object.temp_move(board_object, enemy_player, temp_y, temp_x);	// move the rook back to original square
						rook_object.check(board_object, enemy_player);	// update available moves
						enemy_player.king_object.check(board_object, *this);	// update enemy king's moves
						enemy_player.king_object.create_king_border(board_object);
					}
				}
			}
		}

		ai_x = best_x;
		ai_y = best_y;
	}
	else if(game_piece == 'K')
	{
		enemy_player.king_object.check(board_object, *this);
		enemy_player.king_object.create_king_border(board_object);
		king_moves = enemy_player.king_object.get_num_available_moves();
		int		best_y;
		int		best_x;

		for(int i = 0; i < PLAYER_HEIGHT; ++i)
		{
			for(int j = 0; j < PLAYER_WIDTH; ++j)
			{
				if(king_object.get_available_moves(i, j) == true)	// square is one of rook available moves
				{
					if(enemy_player.king_object.get_king_border(i, j) == false) // square is not in enemy king border
					{
						best_y = i;
						best_x = j;
					}
				}
			}
		}

		for(int i = 0; i < PLAYER_HEIGHT; ++i)
		{
			for(int j = 0; j < PLAYER_WIDTH; ++j)
			{
				if(king_object.get_available_moves(i, j) == true)	// square is one of rook available moves
				{
					if(enemy_player.king_object.get_king_border(i, j) == false) // square is not in enemy king border
					{
						// see how many available moves king will have if rook moved here
						int		temp_x = king_object.get_x_coordinate();
						int		temp_y = king_object.get_y_coordinate();

						king_object.temp_move(board_object, enemy_player, i, j);	// temporarily move rook to new square
						king_object.check(board_object, enemy_player);	// update available moves 
						check(board_object, enemy_player);

						// count how many moves king has 
						enemy_player.king_object.check(board_object, *this);
						enemy_player.king_object.create_king_border(board_object);

						int		enemy_king_moves = enemy_player.king_object.get_num_available_moves();
						
						if(king_moves >= enemy_king_moves)
						{
							king_moves = enemy_king_moves;
							best_y = i;
							best_x = j;
						}

						king_object.temp_move(board_object, enemy_player, temp_y, temp_x);	// move the rook back to original square
						king_object.check(board_object, enemy_player);	// update available moves
						enemy_player.king_object.check(board_object, *this);	// update enemy king's moves
						enemy_player.king_object.create_king_border(board_object);
					}
				}
			}
		}

		ai_x = best_x;
		ai_y = best_y;
	}

	return king_moves;
}


void	player::defense_move(board& board_object, player& enemy_player)
{
	enemy_player.king_object.check(board_object, *this);
	enemy_player.king_object.create_king_border(board_object);
	int		king_moves = king_object.get_num_available_moves();
	int		best_y = king_object.get_y_coordinate();
	int		best_x = king_object.get_x_coordinate();

	for(int i = 0; i < PLAYER_HEIGHT; ++i)
	{
		for(int j = 0; j < PLAYER_WIDTH; ++j)
		{
			if(king_object.get_available_moves(i, j) == true)	// square is one of rook available moves
			{
				if(enemy_player.king_object.get_king_border(i, j) == false) // square is not in enemy king border
				{
					// see how many available moves king will have if rook moved here
					int		temp_x = king_object.get_x_coordinate();
					int		temp_y = king_object.get_y_coordinate();

					king_object.temp_move(board_object, enemy_player, i, j);	// temporarily move rook to new square
					king_object.check(board_object, enemy_player);	// update available moves 
					check(board_object, enemy_player);

					// count how many moves king has 

					int		enemy_king_moves = king_object.get_num_available_moves();
						
					if(king_moves <= enemy_king_moves)
					{
						king_moves = enemy_king_moves;
						best_y = i;
						best_x = j;
					}

					king_object.move(board_object, enemy_player, temp_y, temp_x);	// move the rook back to original square
					king_object.check(board_object, enemy_player);	// update available moves
					enemy_player.king_object.check(board_object, *this);	// update enemy king's moves
					enemy_player.king_object.create_king_border(board_object);
				}
			}
		}
	}

	ai_x = best_x;
	ai_y = best_y;
}