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
	int prev = 0;
	int index;
	int b = 0;

	for(int i = 2; i < argc; i = i + 25){ //for every grid
		printf("i: %i\n", (i + 23) / 25);
		strcpy(input, argv[1]);
		for(int j = 0; j < 25; j++){
			boardarr[j] = argv[i + j];
			markarr[j] = ' ';
		}

		int stepnum = checkBoard(boardarr, markarr, input, &check);


		printf("num steps: %i\n", stepnum);

		if(prev == 0){
			prev = stepnum;
		} else if(prev > stepnum){
			index = (i + 23) / 25;
			prev = stepnum;
		}
	}

	for(int i = 0; i < 25; i++){
		boardarr[i] = argv[(index * 25 - 23) + i];
	}
	strcpy(input, argv[1]);
	printf("\n");
	printf("\n");

	checkBoard(boardarr, markarr, input, &check);
	for(int i = 0; i < 25; i++){
		printf("%s ", boardarr[i]);
	}
	printf("\n");
	printf("%s ",check);

	int sc = score(boardarr, markarr, check);
	printf("score: %i", sc);

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
	printf("score: %i\n", score);
	score = score * strtol(last, &ptr, 10);
	return score;
}
