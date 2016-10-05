
/*
- Enumerated types for the first row (row descriptions)
- The program runs on DOS and takes commands for performing the tasks	
- Ignore rid of first column (sort order is relative to exercise)
- Everything will be stored as text
- 2 commas together means empty field
- Program is divided in 2 parts. One for extracting csv info and save in binary to file and another for sorting data
*/

#include "indexer.h"

void extractInfo(char * fileName);
int validateInput(char * userInput);
void processInput(void);

int main(int argc, char ** argv){
	char * userInput ;	
	char * ch;

	if (argc<2||argc>2) puts("Error: no Arguments or too many!");
	extractInfo(argv[1]);
	
	userInput = (char*) malloc (50 * sizeof(char));
	if (userInput==NULL) {
		printf("out of memory\n");
		exit(EXIT_FAILURE);
	}
	ch = (char*) malloc(1 *sizeof(char) );
	if (userInput==NULL) {
		printf("out of memory\n");
		exit(EXIT_FAILURE);
	}

	while(1){
		puts("");
		puts("Write a keyword to search: ");
		fseek(stdin,0,SEEK_END);
		
		while(fgets(userInput,sizeof(userInput), stdin)){
			ch=strchr(userInput, '\n');
			if(ch) ch='\0';
			else if (!ch) fseek(stdin, 0, SEEK_END);

			if(validateInput(userInput)) break;
			puts("Input not found on this file. Try again:");
		}
		processInput();
	}
	free(userInput);
	free(ch);
	getchar();
}

