#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day3.h"

void day3(int argc, char* arr[]){
	char** strarr = malloc(8 * (argc - 1)); //arr of char pointers (strings)
	char** secarr;

	int count = (argc - 1); //num of elements in secarr
	int secarrlen = 0; //incremention only
	int strarrlen = argc - 1; //strarrlen is prev len, will lag behind secarrlen slightly

	for(int i = 0; i < argc - 1; i++){ // initializes strarr with argv values
		strarr[i] = arr[i + 1];
	}

	for(int i = 0; i < 12; i++){ //should loop 12 times for each bit
		int onecount = 0;
		int zerocount = 0;

		for(int j = 0; j < count; j++){ //finds total ones and total 0s in each bit place
			if(strarr[j][i] == '1'){
				onecount++;
			} else {
				zerocount++;
			}
		}
		if(onecount > zerocount || onecount == zerocount){
			//get all ones
			count = onecount; //set count to num of elements in array
			secarr = malloc(count * 8); //giving secarr min memory needed to store all elements

			for(int j = 0; j < strarrlen; j++){
				if(strarr[j][i] == '1'){
					secarr[secarrlen] = strarr[j];
					secarrlen++; //secarrlen is just to increment for next space in secarr
				}
			}

		} else { //with 0 as biggest
			count = zerocount; //set count to num of elements in array
			secarr = malloc(count * 8); //giving secarr min memory needed to store all elements

			for(int j = 0; j < strarrlen; j++){
				if(strarr[j][i] == '0'){
					secarr[secarrlen] = strarr[j];
					secarrlen++;
				}
			}
		}

		strarrlen = count; //strarr will be smaller now so strarrlen must be the same len

		strarr = realloc(strarr, 8 * count); //shrinks strarr to hold same num as secarr

		for(int j = 0; j < count; j++){ //copying secarr to strarr
			strarr[j] = secarr[j];
		}

		secarrlen = 0; //reset incrementation
		free(secarr); //free secarr so that it can be ready for next loop

		if(count == 1){
			break;
		}
	}

	printf("oxygen scrubber rating: %s\n", strarr[0]);
	free(strarr);
	char** coarr = malloc(8 * (argc - 1)); //arr of char pointers (strings)
	char** thirarr = malloc(8 * (argc - 1));

	int thircount = (argc - 1); //num of elements in secarr
	int thirarrlen = 0; //incremention only
	int coarrlen = argc - 1; //strarrlen is prev len, will lag behind secarrlen slightly

	for(int i = 0; i < argc - 1; i++){ // initializes strarr with argv values
		coarr[i] = arr[i + 1];
	}
//
	for(int i = 0; i < 12; i++){ //should loop 12 times for each bit
		int onecount = 0;
		int zerocount = 0;

		for(int j = 0; j < thircount; j++){ //finds total ones and total 0s in each bit place
			if(coarr[j][i] == '1'){
				onecount++;
			} else {
				zerocount++;
			}
		}
		if(zerocount == 0 || onecount == 0){
			for(int j = 0; j < coarrlen; j++){
					thirarr[j] = coarr[j];
			}
		} else if(onecount > zerocount || onecount == zerocount){
			//get all ones
			thircount = zerocount; //set count to num of elements in array
			thirarr = realloc(thirarr, thircount * 8); //giving secarr min memory needed to store all elements

			for(int j = 0; j < coarrlen; j++){
				if(coarr[j][i] == '0'){
					thirarr[thirarrlen] = coarr[j];
					thirarrlen++; //secarrlen is just to increment for next space in secarr
				}
			}
		} else { //with 0 as biggest
			thircount = onecount; //set count to num of elements in array
			thirarr = realloc(thirarr, thircount * 8); //giving secarr min memory needed to store all elements

			for(int j = 0; j < coarrlen; j++){
				if(coarr[j][i] == '1'){
					thirarr[thirarrlen] = coarr[j];
					thirarrlen++;
				}
			}
		}

		coarrlen = thircount; //strarr will be smaller now so strarrlen must be the same len

		coarr = realloc(coarr, 8 * thircount); //shrinks strarr to hold same num as secarr

		for(int j = 0; j < thircount; j++){ //copying secarr to strarr
			coarr[j] = thirarr[j];
		}
		thirarrlen = 0; //reset incrementation
//		free(thirarr); //free secarr so that it can be ready for next loop

		if(thircount == 1){
			break;
		}
	}
	printf("carbon scrubber rating: %s", coarr[0]);
	free(coarr);
}
