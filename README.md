# Head-Tail
Level 2 System Calls

In the file [head.c] we implement a program that by default reads the first 10 lines of a file that the program needs to open.
If the user does not input how many lines she/he wants to read, the first 10 lines of the document are going to show.
If the user inputs an exact amount of lines to read then the program will output the exact lines the user wants. Ex. 
If the user wants to read the first 3 lines of the program the then the user has to precisely input [ nanpa.txt -n 3 ]. 
To compile this program, use the following command: gcc -Wall -O3 -o head head.c. 
To run the program, use the following command (in Linux): ./head <arg1> <arg2>.
In the file [ tail.c ] the program will display the 10 last lines of the program by default.
This works similar as the [ head.c ] program but in this case the LAST 10 lines will be the output.
When the user does not give any input, 10 lines will be read by default. When the user gives a specific number 
then that specific number of lines will be read. [ nanpa.txt -n 8 ] this will allow the user to output the last 10 lines 
of the file. To compile this program, use the following command: gcc -Wall -O3 -o tail tail.c. 
To run the program, use the following command (in Linux): ./tail <arg1> <arg2>.
