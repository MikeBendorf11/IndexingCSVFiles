#include "indexer.h"

void writeInfo(char *** table, int * match){
	int nr, nc ,nl, mc;
	FILE * outF;

	if((outF=fopen("userRequests.dat", "a"))==NULL)
		puts("Error creating file");

	/*Print match to STDOUT*/
	for(nc=0; nc<NCOLS;nc++)
		// First line with labels only
		printf("%4.4s ", table[0][nc]); 
	puts("");
	for(mc=0; match[mc]>0; mc++){
		//skip any duplicate matches
		if(mc>0 && match[mc]==match[mc-1]) continue;
		for(nc=0; nc<NCOLS;nc++)
			printf("%4.4s ", table[match[mc]][nc]);
		puts("");
	}
	//PRINT TO FILE
	fputs("\n", outF);
	for(nc=0; nc<NCOLS;nc++)
		fprintf(outF, "%10.10s ", table[0][nc]);
	fputs("\n", outF);
	for(mc=0; match[mc]>0; mc++){
		if(mc>0 && match[mc]==match[mc-1]) continue;
		for(nc=0; nc<NCOLS;nc++)
			fprintf(outF, "%10.10s ", table[match[mc]][nc]);
	fputs("\n", outF);
	}

	fclose(outF);
}

/*print ALL
for(nr=0; nr<NROWS; nr++){
	puts("");
	for(nc=0; nc<NCOLS;nc++)
		printf("%4.4s ", table[nr][nc]);
	puts("");
}*/