#include <iostream>
#include <tictac_support.h>

int main( int argc, char* argv[] )
{
	//std::cout << "gets here";
	int board[3][3], move[3][3];

	// load in current board state
	//std::cout << "and here1";
	load_board( argv[1], board );

	// make move // gets here
	//std::cout << "and here2";
	make_move( board );
	
	// save board state
	//std::cout << "and here3";
	save_board( argv[2], board );

	return 0;
}
