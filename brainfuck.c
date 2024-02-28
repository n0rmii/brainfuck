#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	FILE *inptr = stdin;
	FILE *outptr = stdout;
	char fullinst[256];
	for(int i=1; i<argc-1; i++){
		if(strcmp(argv[1], "-i")){
			inptr = fopen(argv[i+1], "r");
		}
		else if(strcmp(argv[1], "-o")){
			outptr = fopen(argv[i+1], "w");
		}
	}
	fgets(fullinst, 256, inptr);
	printf("\nfull: \n%s\n", fullinst);
	char *data = calloc(0xff, sizeof(char));
	unsigned char dptr = 0;
	int iptr = 0;
	char inst = fullinst[0];
	int nest = 0;
	while(inst){
		//printf("data: %c, dptr: %d, inst: %c, iptr: %d\n", data[dptr], dptr, inst, iptr);
		switch (inst){
			case '>':
				dptr++;
				break;
			case '<':
				dptr--;
				break;
			case '+':
				data[dptr]++;
				break;
			case '-':
				data[dptr]--;
				break;
			case '.':
				fprintf(outptr, "%c", data[dptr]);
				break;
			case ',':
				scanf(" %c", &data[dptr]);
				break;
			case '[':
				if(!data[dptr]){
					while(fullinst[++iptr] != ']' || nest){
						if(fullinst[iptr] == '['){
							nest++;
						}
						else if(fullinst[iptr] == ']'){
							nest--;
						}
					}
				}
				break;
			case ']':
				if(data[dptr]){
					while(fullinst[--iptr] != '[' || nest){ //fix nested loops
						if(fullinst[iptr] == ']'){
							nest++;
						}
						else if(fullinst[iptr] == '['){
							nest--;
						}
					}
				}
		}
		inst = fullinst[++iptr];
	}
	fclose(inptr);
	fclose(outptr);
	return 0;
}
