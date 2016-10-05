#include "indexer.h"

void writeInfo(char *** table, int * match); //[NROWS][NCOLS][NCHARS]
char *** table;
int match[MATCHCOUNT];

void extractInfo(char * fileName){
	FILE * inF;
	char *pch;
	char * line; //MAXLENGHT
		/*#rows/cols/letters, maxlenght(line)*/
	int nr, nc ,nl ,mxLn, flag; 

	/*MEM ALLOC*/
	table = (char***) malloc (sizeof(char) * NROWS);
	if (table==NULL) {
		printf("out of memory\n");
		exit(EXIT_FAILURE);
	}
	for(nr=0; nr<NROWS; nr++){
		table[nr] = (char**) malloc(sizeof(char) * NCOLS);
		if (table[nr]==NULL) {
		printf("out of memory\n");
		exit(EXIT_FAILURE);
		}
	}
	for(nr=0; nr<NROWS; nr++){
		for(nc=0; nc<NCOLS; nc++){
			table[nr][nc] = (char*) malloc(sizeof(char) * NCHARS);
			if (table[nr][nc]==NULL) {
			printf("out of memory\n");
			exit(EXIT_FAILURE);
			}
		}
	}
	line = (char*) malloc(sizeof(char) * MAXLENGHT);
	if (line==NULL) {
			printf("out of memory\n");
			exit(EXIT_FAILURE);
	}
	if((inF = fopen(fileName, "r"))==NULL)
	printf("out of memory\n");

	for(nr=0; nr<NROWS; nr++){
		flag = -1;
		/*Every line of 13 rows must end on '\0'*/
		fgets(line,MAXLENGHT,inF);
		pch = strchr(line,'\n');
		if(pch) *pch = '\0';
		else puts("Error 001");
	
		for(mxLn=nc=nl=0; mxLn<MAXLENGHT && nc<NCOLS; mxLn++){ 	
			/*	flag(quotations in cell tell to ignore next comma)*/
			if (line[mxLn]=='"') {
				flag *= -1;
				continue;
			}
			else if (line[mxLn]==',' && flag<0){ 
				table[nr][nc][nl] = '\0'; 
				nc++; 
				nl=0; 
				continue;
			}
			table[nr][nc][nl] = line[mxLn];
			nl++;
		}
	}
	fclose(inF);
}

int validateInput(char * userInput){
	//mc = matchCount, ws = words, wls = wordsLetters
	int nr, nc, nl, mc, ws, ws2, wls; 
	char * ch;
	char words[10][20];
	
	for(mc =0; mc<MATCHCOUNT; mc++) match[mc]=0; //init

	for (nr=mc=0; nr<NROWS; nr++){
		for(nc=0; nc<NCOLS; nc++){
			//regular operation when one word per cell
			if(!strncmp(userInput, table[nr][nc], sizeof(userInput))){
				match[mc++]=nr;
				continue;
			}
			//if cell has space, means has words
			ch = strchr(table[nr][nc],' ');
			if(ch) {
				//Split into words
				for (nl=ws=wls=0; nl<strlen(table[nr][nc]); nl++){
					words[ws][wls]=table[nr][nc][nl];
					wls++;
					if (table[nr][nc][nl]==' '){
						words[ws][wls] = '\0';
						ws++;
						wls=0;
					}
				}
				//Strncmp the found words
				for(ws2=0; ws2<ws; ws2++){
					if(!strncmp(userInput, words[ws2], sizeof(userInput)))
					match[mc++]=nr;
				}
			}
		}
		if (mc==MATCHCOUNT) break;
	}
	if (mc>0) return 1;
	else return 0;
}


void processInput(char * userInput){
	writeInfo(table, match);
}

