#include "board.h"
#include "player.h"
#include <iostream>
using namespace std;


int		main(void)
{
	board	board_object;
	player	player_one;
	player	player_two;

	board_object.board_init();
	player_one.init(board_object, 7, 7, 1, 7);
	player_two.init(board_object, 5, 1, 0, 0);

	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			player_two.rook_object.set_available_moves(i, j, false);
		}
	}

	player_two.rook_object.set_is_alive(false);
	player_two.rook_object.set_num_available_moves(0);
	board_object.set_board_state(0, 0, false);
	board_object.set_board_array(0, 0, 'O');
	
	while(true)
	{
		system("cls");
		board_object.board_display();
		cout << endl;

		player_one.check(board_object, player_two);
		cout << "PLAYER ONE" << endl;
		player_one.turn(board_object, player_two);
		player_one.check(board_object, player_two);

		system("cls");
		board_object.board_display();
		cout << endl;

		player_two.check(board_object, player_one);
		cout << "PLAYER TWO" << endl;
		player_two.turn(board_object, player_one);
		player_two.check(board_object, player_one);
	}
	

	system("pause");
	return 0;
}