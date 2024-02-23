#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char fullinst[100];
	scanf(" %s", fullinst);
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
				printf("%c ", data[dptr]);
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
				break;
			default:
				break;
		}
		inst = fullinst[++iptr];
	}
	return 0;
}
