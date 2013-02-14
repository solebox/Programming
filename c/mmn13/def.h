#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* this following struct represents a word the 
	me - a char pointer that points to the word string
	number - the amount of times the word repeats in the given file
	next - the number of the cell in the word array in which the lexicographically next acending word resides 
*/
typedef struct{char *me; int number;int *lines;int next;}Word; 
/* this following struct is the list of all the word structs 
	Word *head - a Word type pointer that points to an array of Word structs mentioned above
	int size - holds the size of the Word struct array 
	int first - the number of the cell in which the lexicographically first word resides */
typedef struct{Word *head; int size;int first;}WordArray;
/*a helper function to create a word struct from a given string and line number
	this function will create the initial word struct to which we will add more
	line numbers as we find the same word once more in the text in a different line using
	another helper function (addLine) that will be descussed about later on
	char * - a pointer to the first char of the string that is in fact the word in the text
	int  - the number of the line it first accures in */
Word createWord(char *,int);
/* another helper function that adds a line to the word struct it is given a pointer to
 * Word * - a pointer to the word struct instance we want to add another line to
 * int - the line number which we will add
 * */
void addLine(Word *,int);
/* the function that simply initiates the WordArray data structure (which ammusingly is a struct :) )
 * sets all values and pointers to their initial values 
 * size = 0
 * first = -1 (NULL is zero so i cant use that sadly , good thing arrays cant do negatives :) not in ansi c at least :P ok they can but not in a good way, going an adress backwards will be aweful i dont like segfaults ) 
 * etc */
void initArray(WordArray *wordArray);
/*adds a word to the word array datastructure 
 * WordArray * - the pointer to the word array we will ad the word to 
 * Word * - the word we will add 
*/
void addWord(WordArray *wordArray,Word *word);
/* gets a filename and a pointer to an int and returns a string of the file content and changes the int it was given to the 
 * size of the given file*/
char *fileToString(int *fs,char **);
/* searches for a word in the WordArray DataStructure and returns its index
 *	char *word -the string feild of the word struct we are looking for 
 *	WordArray *wordArray - the pointer to the word array data structure we are searching in.
 *	return - int - the index in which we can find the Word struct in the WordArray DataStruct.
 * */
int findWordInArray(char *word, WordArray *wordArray);
/*
 * the function that calls all the other needed helper functions to read the file and populates the WordArray dataStruct with all the Words 
 * WordArray * - the pointer to the WordArray DataStruct we are going to populate
 * char **- simply argv 
  */
void populateWordArray(WordArray *wordArray, char **);
/*
 * a function that reads the WordArray DataStructure and outputs the words in it in a lexicographical order 
 * WordArray *wordArray - the pointer to the word array DataStructure*/
void report(WordArray *wordArray);
/*a function that checks to see (together with the file to string function eventually) if the user input from stdin is valid
 *  char ** - argv
 *  int - arc*/
void validate(int,char **);
