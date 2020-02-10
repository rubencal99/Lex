// Name: Ruben Calderon
// CruzID: rucalder
// Assignment Name: pa1


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

int main(int argc, char* argv[]){
	
	if(argc != 3){
		fprintf(stderr, "%s\n", "Error: Incorrect amount of command line arguments when calling Lex.");
		exit(1);
	}
	int n = 0;
	FILE *in;
	FILE *out;
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in == NULL){
		fprintf(stderr, "%s\n", "Error: input file not found.");
		exit(1);
	}
	char temp[256];
	while(fgets(temp, 256, in) != NULL ){
		n++;
	}
	
	char** str = calloc(n, sizeof(char*)*n);
	
	for(int i = 0; i< n; i++){
		str[i] = malloc(sizeof(char)*256);
	}

	rewind(in); //fseek(in, 0, SEEK_SET)

	int count = 0;
	while(fgets(temp, 256, in) != NULL){
		strcpy(str[count], temp);
		count++;
	}
	
	//fprintf(out, "%d\n", n);
	/*for(int i = 0; i < n; i++){
		fprintf(out, "%s", str[i]);
	}*/

	List list = newList();
	for(int i = 0; i < n; i++){
		if(i == 0){
			prepend(list, i);
			moveBack(list);
		}
		else{
			while(index(list) >= 0){
				if(strcmp(str[get(list)], str[i]) > 0){
					if(index(list) == 0){
						insertBefore(list, i);
						moveFront(list);
						movePrev(list);
					}
					movePrev(list);
				}
				else{
					insertAfter(list, i);
					moveFront(list);
					movePrev(list);
				}
			}
			moveBack(list);
		}
	}
		
	//printList(out, list);			
	
	moveFront(list);
	while(index(list) >= 0){
		char* final = str[get(list)];
		fprintf(out, "%s", final);
		moveNext(list);
	}

	for(int i = 0; i< n; i++){
        	free(str[i]);
	}
	
	free(str);
	clear(list);
	freeList(&list);

	fclose(in);
	fclose(out);
	return 0;		
}	
