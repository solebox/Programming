#include "def.h"
/*a helper function to create a word struct from a given string and line number
	this function will create the initial word struct to which we will add more
	line numbers as we find the same word once more in the text in a different line using
	another helper function (addLine) that will be descussed about later on
	char * - a pointer to the first char of the string that is in fact the word in the text
	int  - the number of the line it first accures in */
Word createWord(char *word_s, int line_number){
  int *lines;
  Word word;
  lines = malloc(sizeof(int));
  lines[0] = line_number;
  word.me = word_s;
  word.number = 1;
  word.lines = lines;
	word.next = -1;
  return word;
}
/* another helper function that adds a line to the word struct it is given a pointer to
 * Word * - a pointer to the word struct instance we want to add another line to
 * int - the line number which we will add
 * */
void addLine(Word *word,int line_number){
    word -> number++;
    word -> lines = (int *)realloc((void *)word -> lines, sizeof(int)*(word -> number));
    word -> lines[word -> number-1] = line_number;
}

/*adds a word to the word array datastructure 
 * WordArray * - the pointer to the word array we will ad the word to 
 * Word * - the word we will add 
*/
void addWord(WordArray *wordArray,Word *newWord){
  Word *firstWord = NULL,*jmpWord = NULL;
	int jmp = -1,bjmp = -1;
	wordArray -> size++;
  wordArray -> head = realloc(wordArray -> head,sizeof(Word)*(wordArray -> size));
  wordArray -> head[wordArray -> size - 1] = *newWord;
  newWord = &(wordArray -> head[wordArray -> size - 1]);
	if (wordArray -> size == 1)
		wordArray -> first = 0;
	else{
				firstWord = &(wordArray -> head[wordArray -> first]);
				if (strcmp(newWord -> me,firstWord -> me) < 0){
					newWord -> next = wordArray -> first;
					wordArray -> first = wordArray -> size -1;
				}else{
					jmp = wordArray -> first;
					jmpWord = &(wordArray -> head[jmp]);
					while (jmp != -1 && strcmp(newWord -> me, jmpWord -> me) >= 0){
						jmpWord = &(wordArray -> head[jmp]);
						bjmp = jmp;
						jmp = jmpWord -> next;	
					}
					jmpWord = &(wordArray -> head[bjmp]);
					newWord -> next = jmpWord -> next;
					jmpWord -> next = wordArray -> size -1;
				}
	}
}
/* the function that simply initiates the WordArray data structure (which ammusingly is a struct :) )
 * sets all values and pointers to their initial values 
 * size = 0
 * first = -1 
 * etc */
void initArray(WordArray *wordArray){
    wordArray -> size = 0;
    wordArray -> head = malloc(sizeof(Word));
		wordArray -> first = -1;
}

/* searches for a word in the WordArray DataStructure and returns its index
 *	char *word -the string feild of the word struct we are looking for 
 *	WordArray *wordArray - the pointer to the word array data structure we are searching in.
 *	return - int - the index in which we can find the Word struct in the WordArray DataStruct.
 * */
int findWordInArray(char *word, WordArray *wordArray){
	int i;
	for (i = 0; i < wordArray -> size;i++){
		if (!(strcmp(word,(wordArray -> head[i].me))))
			return i;
	}
	return -1;
}
/* gets a filename and a pointer to an int and returns a string of the file content and changes the int it was given to the 
 * size of the given file*/
char *fileToString(int *fs,char *argv[]){
  FILE *file;
  long fSize;
  char *buff;
  size_t result;
  file = fopen(argv[1],"r");
  if (!file) {
		fputs("File error, did you check if it exists?",stderr); 
		exit(1);
	}

  fseek(file,0,SEEK_END);
  fSize = ftell(file);
  rewind(file);

  buff = (char *)malloc(sizeof(char)*fSize);
  if (!buff) {
		fputs("Memory error",stderr); 
		exit(2);
	}

  result = fread(buff,1,fSize,file);
  if (result != fSize) {
		fputs("Reading error",stderr); 
		exit(3);
	}
  fclose(file);
	*fs = result;
  return buff;
}

/*
 * the function that calls all the other needed helper functions to read the file and populates the WordArray dataStruct with all the Words 
 * WordArray * - the pointer to the WordArray DataStruct we are going to populate
 * char **- simply argv 
  */
void populateWordArray(WordArray *wordArray,char *argv[]){
	Word word2;
	int fstr_size,i,j,wordIndex;
	char *fstr,**lineArray,*pch,*word_s;
	
	fstr = fileToString(&fstr_size,argv); /*file spilled into string fstr*/
	lineArray = malloc(sizeof(char *));
	pch = strtok(fstr,"\n"); /*lets take it line by line shall we*/
	for (i = 0;pch != NULL ;i++){
			lineArray = realloc(lineArray,(i+1)*sizeof(char *));
			lineArray[i] = pch;
			pch = strtok(NULL,"\n");
	}
	for (j = 0; j < i;j++){
    word_s = strtok(lineArray[j]," ");
		while (word_s != NULL){
			if ((wordIndex = findWordInArray(word_s,wordArray)) == -1){
				word2 = createWord(word_s,j+1); /*btw -1 means we didnt find it*/
				addWord(wordArray,&word2); /* look at my words my words are amazing*/
			}else{
				addLine(&(wordArray -> head[wordIndex]),j+1); 
			} /*j's get +1 because humans dont count lines the right way :)*/
			word_s = strtok(NULL," ");
		}	
	}
	free(lineArray);
}
/*
 * a function that reads the WordArray DataStructure and outputs the words in it in a lexicographical order 
 * WordArray *wordArray - the pointer to the word array DataStructure*/
void report(WordArray *wordArray){
	int i,j;
	Word word;
	for (i = wordArray -> first; i != -1; i = word.next){
		word = wordArray -> head[i];
		if (word.number <= 1)
			printf("%s appears in line: %d\n",word.me,word.lines[word.number-1]);
		else{
			printf("%s appears in lines: ",word.me);
			for (j = 0; j < ((word.number)-1); j++)
				printf("%d,",word.lines[j]);
			printf("%d\n",word.lines[j]);
		}
	}
	for (i=0;i<wordArray -> size;i++){
		free(wordArray -> head[i].lines);
	}
	free(wordArray -> head);
}
/*a function that checks to see (together with the file to string function eventually) if the user input from stdin is valid
 *  char ** - argv
 *  int - arc*/
void validate(int argc,char *argv[]){
	if (argc <= 1){
		fprintf(stderr,"%s\n","Error: too little arguments, please enter filename");
		fprintf(stderr, "%s %s %s\n","correct format: ",argv[0]," filename.txt");
		exit(4);
	}
	if (argc > 2){
		fprintf(stderr,"%s\n","Error: too many arguments, please enter filename");
		exit(4);
	}
}
