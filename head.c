////////////////////////////////////////////
////  Team:Monica Heim
////	Machine: Linux-18
////	Programming Assignment 2
////	CSCE 321 - Operating Systems
////	10/7/19
////	Fall 2019
////	C. Lauter
////////////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/*
  Program: head
  Description: This program has the options of (1) running without a filename
		argument, (2) with a filename argument, (3) with the -n [num] option,
		(4) or a combination of the filename and -n options.
  Execution:
	- (1): this program copies the first 10 lines of the input it
		receives on standard input (stdin) to standard output (stdout)
		and disregards any other lines seen on input.
	- (2): this program reads from the file designated by the
		filename argument.
	- (3): this program replaces the number of 10 lines by the
		appropriate amount specified by [num]
	- (4): this program combines the two options and uses it in any
		reasonable order
*/
void read_file(int fd, int line) {
	int readchar;
	int option;
	int number = 0;
	int x = 0;
	do {
		char t = 0;
        readchar = read(fd, &t, 1);
		write(STDOUT_FILENO, &t, sizeof(t));
		if(t == '\n') {
			number++;
			if(number==line)
				break;
        	}
		if(t == '\0')
			break;
	}
	while (readchar != 0);
}
int str_to_num(char *base){
	int number = 0;
	int cv = 0;
	for(int i = 0; base[i] != '\0'; i++)
		number = number * 10 + base[i] - '0';

	return number;
}
int comparisons(const char *first_string, const char *second_string){
	while(*first_string){
		if (*first_string != *second_string)
			break;

		first_string++;
		second_string++;
	}
	return *(const unsigned char*)first_string - *(const unsigned char*)second_string;
}
int main(int argc, char **argv) {
	char *file;
	file = NULL;
	int options = 10;
	int i = 0;

	if (argc == 2) {
		file = argv[1];
	}
	else if (argc == 3) {
		if (strcmp("-n", argv[1]) == 0){
			options =  str_to_num(argv[2]);
		}
		else{
			return -1;
		}
	}
	else if (argc == 4) {
		if (strcmp("-n", argv[1]) == 0) {
			options =  str_to_num(argv[2]);
			file = argv[3];
		}
		else if (strcmp("-n", argv[2]) == 0) {
			options =  str_to_num(argv[3]);
			file = argv[1];
		}
		else {
			return -1;
		}
	}
	else if (argc > 4){
		return -1;
	}
	if(options < 1){
		return 0;
	}
	if (file == NULL){
		read_file(STDIN_FILENO, options);
	}
	else{
		int fd = open(file, O_RDONLY);

		if (fd ==-1)
		{
			return -1;
		}
		read_file(fd, options);
		close(fd);
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
