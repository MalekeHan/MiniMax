#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* board[3][3];

 
//Function to compare the maximum value between two integers
int findMin(int currentMin, int newMin){
	if(currentMin < newMin){
		return currentMin;
	}
	else{
		return newMin;	
	}
}
//Function to compare the minimum value between two integers
int findMax(int currentMax, int newMax){
	if(currentMax > newMax){
		return currentMax;
	}
	else{
		return newMax;
	}
}

//Initialize the board into its original state with no moves placed yet
void initializeBoard(){
	for(int i =0; i < 3; i++){
		for(int j = 0; j <3; j++){
			board[i][j] = "?";
		}
	}
}

//Function to make and print out the board with the given inputs from the user 
void makeBoard(){

	printf("%s | %s | %s", board[0][0], board[0][1], board[0][2]);
	printf("\n--+---+--\n");
	printf("%s | %s | %s", board[1][0], board[1][1], board[1][2]);
	printf("\n--+---+--\n");
	printf("%s | %s | %s", board[2][0], board[2][1], board[2][2]);
	printf("\n");
}
 
//Function to check if there are still moves availble to for the game to still be played
bool isMovesLeft(char *currentBoard[3][3]){
    for (int i = 0; i<3; i++){
    	for (int j = 0; j<3; j++){
    		if (!strcmp(currentBoard[i][j],"?")){
    			return true;
    		}
    	}
    }
    return false;
}
//Check whether there has been a winner or not in the board as of yet
//This will be used to end the game before all 9 moves are exhausted when the user plays the game against the AI
int checkWinner(){
    //CHECK ROWS
    for(int i = 0; i < 3; i++){
    	if(!strcmp(board[i][0], board[i][1]) && !strcmp(board[i][1], board[i][2])){
    		if(!strcmp(board[i][0], "X")){
    			return 10;
    		}
    		if(!strcmp(board[i][0], "O")){
    			return -10;
    		}
    	}
    }
    //CHECK COLUMNS
    for(int i = 0; i < 3; i++){
        if(!strcmp(board[0][i], board[1][i]) && !strcmp(board[0][i], board[2][i])){
        	if(!strcmp(board[1][i], "X")){
        		return 10;
        	}
        	if(!strcmp(board[1][i], "O")){
        		return -10;
        	}
        }
    }

    if(!strcmp(board[0][0], board[1][1]) && !strcmp(board[0][0], board[0][2])){
    	if(!strcmp(board[0][0], "X")){
    		return 10;
    	}
    	if(!strcmp(board[0][0], "O")){
    		return -10;
    	}
    }

    if(!strcmp(board[0][2], board[1][1]) && !strcmp(board[0][2], board[2][0])){
        if(!strcmp(board[1][1], "X")){
        	return 10;
        }
        if(!strcmp(board[1][1], "O")){
        	return -10;
        }
   }
    
    return 0;
}
//Used to check which symbol won the game
int decideWinner(){
	if(checkWinner() == 10){ //If check winner returns 10, then that means the maximizer(X) won
		printf("X wins");
		return 0;
	}
	else if(checkWinner() == -10){ //If check winner returns -10, then that means the maximizer(O) won
		printf("O wins");
		return 0;
	}
}
 
//Minimax function to dtermine scores based on the placement of the symbol along with how fast the symbol would win the game(depth)
int minimax(char *board[3][3], int depth, bool maximizerTurn){
    int score = checkWinner(board);
 

    if (score == 10 || score == -10){
    	return score;
    }
    
    if (isMovesLeft(board)==false){
    	return 0;
    }
 
    if(maximizerTurn == false){ //Check if it is the maximizer's turn or not
    	int best = 1000000;
   		for (int i = 0; i<3; i++){
    		for (int j = 0; j<3; j++){
    			if (!strcmp(board[i][j], "?")){
    				board[i][j] = "O";
    				best = findMin(best, minimax(board, depth+1, maximizerTurn));
           		    board[i][j] = "?";
         	   }
     	   }
 	    }
 	    return best;
    }
    
    else{
    	int best = -1000000;
    	for (int i = 0; i<3; i++){
    		for (int j = 0; j<3; j++){
      	  		if (!strcmp(board[i][j], "?")){
      	    		board[i][j] = "X";
      	    		best = findMax(best, minimax(board, depth+1, maximizerTurn));
      	   			board[i][j] = "?";
      	 		 }
       		}
     	}
     return best;
   }
}

struct opponentMove{
    int row;
    int col;
};
 
// This will return the best possible move for the player
struct opponentMove minimizerMove(char *board[3][3]) {
//	int max =  minimax(board, 0, true);
//	int min = max;  
    int optimalValue = 1000000;
    
    struct  opponentMove moveForO;
    moveForO.row = -1;
    moveForO.col = -1;

 
    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
        	if (!strcmp(board[i][j],"?")){
                board[i][j] = "O";
                int moveVal = minimax(board, 0, true); 
                board[i][j] = "?";
                if (moveVal < optimalValue){
                    moveForO.row = i;
                    moveForO.col = j;
                    optimalValue = moveVal;
                }
            }
        }
    }
    
    return moveForO;
}

struct opponentMove maximizerMove(char *board[3][3]){
	 int optimalValue = -1000000;
	 struct  opponentMove moveForO;
	 moveForO.row = -1;
	 moveForO.col = -1;
	 
	for (int i = 0; i<3; i++){
		for (int j = 0; j<3; j++){
			if (!strcmp(board[i][j],"?")){
				board[i][j] = "X";
				int moveVal = minimax(board, 0, false); 
				board[i][j] = "?";
				if (moveVal > optimalValue){
				moveForO.row = i;
				moveForO.col = j;
	    	    optimalValue  = moveVal;
	    	    }
	    	 }
	    }
	}
	 return moveForO;
	    	 
}

void playerTurn(){
	int row;
	int col;
	scanf("%d", &row);
	scanf("%d", &col);
	while(row < 0 || row > 2 || col < 0 || col > 2){
		printf("Invalid input\nInput move again: ");
		scanf("%d", &row);
		scanf("%d", &col);
		if(row >= 0 && row <= 2 && col >= 0 && col <= 2 ){
			break;
		}
	}
	if(!strcmp(board[row][col], "?")){
		board[row][col] = "X";
		}
	}

//Check if the amount of X on the board is equal to the amount of Os if so then it is X's turn 
//otherwise O's turn
 

int main(int argc, char *argv[]){

	if(argc > 2){
		char* pos1 = argv[1];
	    char* pos2 = argv[2];
	    char* pos3 = argv[3];
	    char* pos4 = argv[4];
	    char* pos5 = argv[5];
	    char* pos6 = argv[6];
	    char* pos7 = argv[7];
	    char* pos8 = argv[8];
	    char* pos9 = argv[9];

	    board[0][0] = pos1;
	    board[0][1] = pos2;
	    board[0][2] = pos3;
	    board[1][0] = pos4;
	    board[1][1] = pos5;
	    board[1][2] = pos6;
	    board[2][0] = pos7;
	    board[2][1] = pos8;
	    board[2][2] = pos9;
	    makeBoard();
	    //Check amount of X to Os here and call the correct function!
	    
		int count1 = 0;
		int count2 = 0;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(!strcmp(board[i][j], "X")){
					count1 += 1;
				}
				if(!strcmp(board[i][j], "O")){
					count2 += 1;
				}
			}
		}
		if(count1 == count2){
			struct opponentMove bestMove =	minimizerMove(board);
			printf("O: %d %d\n\n", bestMove.row, bestMove.col );
		}

		else{
			struct opponentMove bestMove = maximizerMove(board);
			printf("O: %d %d\n\n", bestMove.row, bestMove.col );
		}
	    
	    
		return 0;
	}
	if(argc == 1){
	  board[0][0] = "?";
	  board[0][1] = "?";
	  board[0][2] = "?";
	  board[1][0] = "?";
	  board[1][1] = "?";
	  board[1][2] = "?";
	  board[2][0] = "?";
	  board[2][1] = "?";
	  board[2][2] = "?";
	  int count = 1;
	  while(count <= 9){

	  	if(count > 9){
	  		printf("DRAW!");
	  		return 0;
	  	}
	  
	    if(checkWinner() == -10){
	    	makeBoard();
	    	printf("\nO WINS!\n");
	    	return 0;
	    }
		
	    
	 	if(checkWinner() == 10){
	 		makeBoard();
	  		printf("\nX WINS!\n");
	  		return 0;
	  	}
	  	if(count % 2 == 0){
	  		struct opponentMove computermove = minimizerMove(board);
			board[computermove.row][computermove.col] = "O";
			count++;
		}
		else{
			makeBoard();
			printf("X: ");
			playerTurn();
			count++;
		}	
	}
}
    
    return 0;
}
