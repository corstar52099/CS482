#include <iostream>
#include <fstream>

//prototypes
int load_board(std::string, int[][3]);
int save_board(std::string, int[][3]);
int make_move(int[][3]);
//end prototypes

int main(int argc, char *argv[]){
    std::string filename = argv[1];


    return 0;
}

//returns 0 if file loaded OK, returns -1 if file does not exist
int load_board(std::string filename, int board[][3]){
    std::ifstream infile;
    infile.open(filename);
    if (!infile.is_open()){
        return 0;
    }
    infile.close();
}

//returns 0 if file loaded OK, returns -1 if file does not exist
int save_board(std::string filename, int board[][3]){
    std::ofstream infile;
    infile.open(filename);
    if (!infile.is_open()){
        return 0;
    }
    infile.close();
}

//returns the number of steps it took to choose the best move
//returns 1 by default, and 0 if no moves are made
int make_move(int board[][3]){
    //testing best possible moves
    int score = 0;
    for (int i=0; i < 3; i++){
        for(int k = 0; k < 3; k++){
            if(board[i][k] == 0){
                board[i][k] = -1;
                score = minimax(board);
            }
        }
    }
}

//implements the minimax algorithm
int minimax (int board[][3]){
    //recursivly move through the board finding the scores
    return 1;
}

//prints the board with it being known that -1 is 0 and 1 is x and 0 is empty
void printBoard(int board[][3]){

}