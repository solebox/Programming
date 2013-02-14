#include "def.h"
/* program takes as stdin argument a filename and outputs an index for it*/
int main(int argc, char *argv[]){
	WordArray wordArray;
	validate(argc,argv);
	initArray(&wordArray);
	populateWordArray(&wordArray,argv);
	report(&wordArray);
	return 0;	
}
