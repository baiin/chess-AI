#include "player_y.h"


void	player_y::init(board& board_object, int start_king_y_coordinate, int start_king_x_coordinate)
{
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


void	player_y::check(board& board_object, player& enemy_player)
{
	king_object.check(board_object, enemy_player);

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
		}
	}
}


void	player_y::turn(board& board_object, player& enemy_player)
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

	do
	{

		if(king_object.get_is_checked() == true)
		{
			game_piece = 'K';
		}
		else
		{
			cout << "AVAILABLE MOVES: " << num_available_moves << endl;
			cout << "WHICH GAME PIECE: ";
			cin  >> game_piece;

			game_piece = toupper(game_piece);
		}

		if(game_piece == 'K')
		{
			do
			{
				enemy_player.king_object.create_king_border(board_object);
				king_object.check(board_object, enemy_player);
				king_object.get_available_check_moves(board_object, enemy_player, king_object.get_y_coordinate(), king_object.get_x_coordinate());
				cout << "K: [" << king_object.get_y_coordinate() << " , " << king_object.get_x_coordinate() << "]" << endl;
				cout << "AVAILABLE MOVES: " << king_object.get_num_available_moves() << endl;
				cout << "Y-COORD: ";
				cin  >> y_coordinate;
				cout << "X-COORD: ";
				cin  >> x_coordinate;

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
			
		}
	} while(turn == false);
}


bool	player_y::get_available_moves(int y_coordinate, int x_coordinate)
{
	return available_moves.get_board_state(y_coordinate, x_coordinate);
}


void	player_y::evaulate_moves(char game_piece, board& board_object, player& enemy_player)
{
	
}

