#include <tictac_support.h>
#include <iostream>
std::pair<int,int> bestMove(int [][3], bool, long&);
int minimax (int [][3], int, bool, long&);
int checkwinner(int [][3]);
bool ismovesLeft(int [][3]);
int min (int score, int test){return (score<test)?score:test;}
int max (int score, int test){return (score>test)?score:test;}
void printBoard(int board[][3]);
//protopes

//end prototypes

/**
	make_move: takes a board state and makes a legal 
	(hopefully optimal) move

	args:
		int [][3] board: 3x3 array of ints representing the 
		board state. The values of board are altered based
		on the move
			0: empty
			1: x
		 -1: o
		
	returns (int):
		the number of steps it took to choose the best move
		(current implementation returns 1 by default, 0 if no move made)
**/
int make_move( int board[][3] )
{

	std::pair<int,int> move;
	long num_steps = 0;

    //printing the board to the console before the move is made
	std::cout << "board before move: " << std::endl;
	printBoard(board);

    //find the best move
	move = bestMove(board, false, num_steps);


    //exit if the game is over
    if(!ismovesLeft(board) || (checkwinner(board) != 0)){
        std::cout << "No moves can be made, the game is over" << std::endl;
        return 0;
    }
    //actually make the move that is found
    board[move.first][move.second] = -1;

    //print the board after the move is made
	std::cout << "board after move (" << num_steps << " steps):" << std::endl;
	printBoard(board);
	return 1;
}
std::pair<int,int> bestMove(int board[][3], bool minmax, long& numsteps){
    std::pair<int, int> bestIndecies;
    bestIndecies.first = 3;
    bestIndecies.second = 3;
    int score = 0;
    int bestscore = 0;

    //case to do nothing if the game is over
    if(!ismovesLeft(board) || (checkwinner(board) != 0)){
        return bestIndecies;
    }

    //traverse the board searching for moves
    for (int i = 0; i < 3; i++){
        for(int k = 0; k < 3; k++){
            if(board[i][k] == 0){
                //if its maxamizing
                if(minmax){
                    //do move
                    board[i][k] = 1;
					numsteps++;

                    //get score of that move
                    score = minimax(board, 0, false, numsteps);

                    //undo move
                    board[i][k] = 0;

                    //if it is a new best score, adapt
                    if(score >= bestscore){
                        bestscore = score;
                        bestIndecies.first=i;
                        bestIndecies.second=k;
                    }
                }
                //if its minimizing
                else{
                    //do move
                    board[i][k] = -1;
					numsteps++;

                    //get score of that move 
                    score = minimax(board, 0, true, numsteps);

                    //undo move
                    board[i][k] = 0;

                    //if it is a new best score, adapt
                    if(score <= bestscore){
                        bestscore = score;
                        bestIndecies.first=i;
                        bestIndecies.second=k;
                    }
                }
            }
        }
    }
    return bestIndecies;
}
//implements the minimax algorithm
int minimax (int board[][3], int depth, bool minmax, long& numsteps){

    //set the score to to the value of checkwinner
    int score = checkwinner(board);
    if(score != 0){
        return score;
    }
    if(!ismovesLeft(board)){
        return 0;
    }
    if(minmax){
        for (int i=0; i < 3; i++){
            for(int k = 0; k < 3; k++){
                if(board[i][k] == 0){
                    //do move
                    board[i][k] = 1;
					numsteps++;
                    //maxamizng score
                    score = max(score, minimax(board, depth + 1, false, numsteps));
                    
                    //undomove
                    board[i][k] = 0;
                }
            }
        }
    }
    else{
        for (int i=0; i < 3; i++){
            for(int k = 0; k < 3; k++){
                if(board[i][k] == 0){
                    //do move
                    board[i][k] = -1;
					numsteps++;
                    //minimizing score
                    score = min(score, minimax(board, depth + 1, true, numsteps));

                    //undo move
                    board[i][k] = 0;
                }
            }
        }
    }   
    return score;
}

/*returns a pair of int and bool, the int is 
  the score, the bool is if there was a winner*/
int checkwinner(int board[][3]){

    //check rows first
    for (int row =0; row < 3; row++){
        if((board[row][0] == board[row][1]) && (board[row][1] == board[row][2])){
                if (board[row][0] == 0){
                    continue;
                }
                return board[row][1];
        }
    }      
    //check cols next next
    for (int col =0; col < 3; col++){
         if((board[0][col] == board[1][col]) && (board[1][col] == board[2][col])){
                if (board[0][col] != 0){
                    return board[0][col] ;
                }
             }
    }
    //check diagonal 1
    if((board[0][0] == board[1][1]) && (board[1][1] == board[2][2])){
        if (board[0][0] != 0){
            return board[1][1];
        }
    }
    //check diagonal 2
    if((board[0][2] == board[1][1]) && (board[1][1] == board[2][0])){
        if (board[0][3] != 0){
            return board[1][1];
        }
    }
    return 0;   
}

//checks if the game is over
bool ismovesLeft(int board[][3]){
    for (int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            if(board[i][j] == 0){
                return true;
            }
        }
    }
    return false;
}

//prints the board with it being known that -1 is 0 and 1 is x and 0 is empty
void printBoard(int board[][3]){
    std::cout << "----------" << std::endl;
    for(int i = 0; i < 3 ; i++){
        for(int k = 0; k < 3; k++){
            if(board[i][k] == 0){
                std::cout << " _ ";
            }
            if(board[i][k] == -1){
                std::cout << " o ";
            }
            if(board[i][k] == 1){
                std::cout << " x ";
            }
            //std::cout << board[i][k];
        }
        std::cout << std::endl;
    }
     std::cout << "----------" << std::endl;
}

