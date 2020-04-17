////////////////////////////////////////////
////    Team: Monica Heim
////	Machine: Linux-18
////	Programming Assignment 2
////	CSCE 321 - Operating Systems
////	10/7/19
////	Fall 2019
////	C. Lauter
////////////////////////////////////////////
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define tbuffer 1024 

/*
  Program: tail
  Description: This program has the options of (1) running without a filename
		argument, (2) with a filename argument, (3) with the -n [num] option,
		(4) or a combination of the filename and -n options.
  Execution:
	- (1): this program copies the last 10 lines of the input it
		receives on standard input (stdin) to standard output (stdout)
		and disregards any other lines seen on input.
	- (2): this program reads from the file designated by the
		filename argument.
	- (3): this program replaces the number of 10 lines by the
		appropriate amount specified by [num]
	- (4): this program combines the two options and uses it in any
		reasonable order
*/

char* sbuffer(char row[], int n){
	char *saved = (char*) malloc(n*sizeof(char));
	if (NULL == saved){
		exit(1);
	}
	for(int i=0; i<n-1; i++)
            saved[i] = row[i];

	return saved;
}

int comparrison(const char *first_string, const char *second_string){
	while(*first_string){
		if (*first_string != *second_string)
			break;

		first_string++;
		second_string++;
	}
	return *(const unsigned char*)first_string - *(const unsigned char*)second_string;
}

int conv(char *base){
	int number = 0;
	for(int i = 0; base[i] != '\0'; i++)
		number = number * 10 + base[i] - '0';

	return number;
}

typedef struct _str
{
	int ptrs;
	char *ptr;
} str;

//int lengthofs (char* letters)
//{
//	size_t count;
//	char *t;
//
//	count=0;
//	for (t=letters; *t!='\0';t++)
//{
//	c++;
//}
//	
//	return count;
//}

void filer(int pipe, int row_read) {
	int col = 0;
	int size = 0;
	int cread;
	char line[tbuffer];
	str addressp[row_read];

	do {
		char value = 0;
		cread = read(pipe, &value, 1);
		line[size] = value;
		size++;
		if(value == '\n') {
			if(col<row_read){
				addressp[col].ptr = sbuffer(line, size+1);
				addressp[col].ptrs = size;
				size = 0;
				col++;
			}
			else if (col==row_read) {
				free(addressp[0].ptr);
				for(int i = 0; i < row_read-1; i++){
					addressp[i].ptr = addressp[i+1].ptr;
					addressp[i].ptrs = addressp[i+1].ptrs;
				}
				addressp[row_read-1].ptr = sbuffer(line, size+1);
				addressp[row_read-1].ptrs = size;
				size = 0;
			}
		}
		else if((value == '\0')&&(size!=1)){
			if(col<row_read){
				addressp[col].ptr = sbuffer(line, size+1);
				addressp[col].ptrs = size;
				col++;
				size = 0;
				break;
			}
			else if (col==row_read) {
				free(addressp[0].ptr);
				for(int i = 0; i < row_read-1; i++){
					addressp[i].ptr = addressp[i+1].ptr;
					addressp[i].ptrs = addressp[i+1].ptrs;
				}
				addressp[row_read-1].ptr = sbuffer(line, size+1);
				addressp[row_read-1].ptrs = size;
				size = 0;
				break;
			}
		}
		else if((value == '\0')&&(size==1))
			break;
	}
	while (cread != 0);
	for(int i = 0; i < col; i ++){
		write(STDOUT_FILENO, addressp[i].ptr, addressp[i].ptrs);
	}
	for(int i = 0; i < col; i++){
		free(addressp[i].ptr);
	}
}
int main(int opt, char **type) {
	int lines = 10;
	char *filename;
	filename = NULL;

	if (opt == 2) {
		filename = type[1];
	}
	else if (opt == 3) {
		if (strcmp("-n", type[1]) == 0){
			lines =  conv(type[2]);
		}
		else{
			return -1;
		}
	}
	else if (opt == 4) {
		if (strcmp("-n", type[1]) == 0) {
			lines =  conv(type[2]);
			filename = type[3];
		}
		else if (strcmp("-n", type[2]) == 0) {
			lines =  conv(type[3]);
			filename = type[1];
		}
		else {
			return -1;
		}
	}
	else if (opt > 4){
		return -1;
	}

	if(lines < 1){
		return 0;
	}
	if (filename == NULL){
		filer(STDIN_FILENO, lines);
	}
	else{
		int pipe = open(filename, O_RDONLY);

		if (pipe ==-1)
		{
			return -1;
		}
		filer(pipe, lines);
		close(pipe);
		//	pointer=&array[lines];
		//		count=count-lines;
		//		write(1,ptr,count);
		//		free(pipe);
		//		close(pipe);
	}
	return 0;
	
}

//int error(){
//
//if (pf == NULL) {
//	
//		errnum = errno;
//		fprintf(stderr, "Value of errno: %d\n", errno);
//		perror("Error printed by perror");
//		fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
//	} else {
//	
//		//fclose (pf);
//	}
//	
//	return 0;
//}
