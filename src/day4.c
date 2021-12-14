#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day4.h"

void day4(int argc, char* argv[]){
	//board size is (argc - 2) / 25
	//argc size is 1 + 25 * num of boards
	char** boardarr = malloc(8 * 25);
	char markarr[25];
	char* input = malloc(strlen(argv[1]) + 1);
	char* check = malloc(8);
	int firstprev = 100;
	int lastprev = 0;
	int firstindex;
	int lastindex;
	int stepnum;

	for(int i = 2; i < argc; i = i + 25){ //for every grid
		strcpy(input, argv[1]);
		for(int j = 0; j < 25; j++){
			boardarr[j] = argv[i + j];
			markarr[j] = ' ';
		}

		stepnum = checkBoard(boardarr, markarr, input, &check);

		if(firstprev > stepnum){
			firstindex = (i + 23) / 25;
			firstprev = stepnum;
		}
		if(lastprev < stepnum){
			lastindex = (i + 23) / 25;
			lastprev = stepnum;
		}
	}

	printf("first board to win: %i, with %i moves\n", firstindex, firstprev);
	printf("last board to win: %i, with %i moves\n", lastindex, lastprev);

	for(int i = 0; i < 25; i++){
		boardarr[i] = argv[(firstindex * 25 - 23) + i];
	}
	strcpy(input, argv[1]);
	checkBoard(boardarr, markarr, input, &check);
	int sc = score(boardarr, markarr, check);
	printf("score of first board to win: %i\n", sc);

	for(int i = 0; i < 25; i++){
		boardarr[i] = argv[(lastindex * 25 - 23) + i];
	}
	strcpy(input, argv[1]);
	checkBoard(boardarr, markarr, input, &check);
	sc = score(boardarr, markarr, check);
	printf("score of last board to win: %i", sc);

	free(boardarr);
	free(input);
}

int checkBoard(char** board, char* checkboard, char* in, char** copy){
	for(int j = 0; j < 25; j++){
		checkboard[j] = ' ';
	}
	char* check;
	check = strtok(in, ",");
	int counter = 0;
	int steps = 0;

	while (check != NULL) {
		steps++;
		//check is equal to first input here
		for(int j = 0; j < 25; j++){
			if(strcmp(check, board[j]) == 0){
				checkboard[j] = 'x';
			}

			for(int k = 0; k < 5; k++){
				for(int l = 0; l < 5; l++){
					if(checkboard[(k * 5) + l] == 'x'){
						counter++;
					}
					if(counter == 5){
						break;
					}
				}
				if(counter == 5){
					break;
				}
				counter = 0;

				for(int l = 0; l < 5; l++){
					if(checkboard[k + (5 * l)] == 'x'){
						counter++;
					}
					if(counter == 5){
						break;
					}
				}
				if(counter == 5){
					break;
				}
				counter = 0;
			}
			if(counter == 5){
				break;
			}
		}
		if(counter == 5){
			break;
		}
		check = strtok(NULL, ",");
	}
	strcpy(*copy, check);
	return steps;
}

int score(char** board, char* checkboard, char* last){
	int score = 0;
	char *ptr;

	for(int i = 0; i < 25; i++){
		if(checkboard[i] == ' '){
			score = score + (int)strtol(board[i], &ptr, 10);
		}
	}
	score = score * strtol(last, &ptr, 10);
	return score;
}
