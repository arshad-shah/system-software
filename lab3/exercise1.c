// Write a C program to emulate the ls –l command that prints all
// files in a current directory. Use the system() command.
// Eg. ./myprog ls –l example.txt
// What is the security problem with this program
// and how can you fix it?

//this program is the ls -l command emulator
// it prints all the files in the current directory

//imports for the program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//main function
int main()
{
    //argv is an array of strings
    char *argv = {"./myprog","ls", "-l", "example.txt"};
    int argc = 3;
    //check if the user has entered the correct number of arguments
    if (argc != 3)
    {
        printf("Error: Incorrect number of arguments entered \n");
        printf("Usage: ./myprog ls -l example.txt \n");
        return 1;
    }

    //check if the user has entered the correct command
    if (strcmp(argv[1], "ls") != 0)
    {
        printf("Error: Incorrect command entered \n");
        printf("Usage: ./myprog ls -l example.txt \n");
        return 1;
    }

    //check if the user has entered the correct flag
    if (strcmp(argv[2], "-l") != 0)
    {
        printf("Error: Incorrect flag entered \n");
        printf("Usage: ./myprog ls -l example.txt \n");
        return 1;
    }

    //check if the user has entered the correct file name
    if (strcmp(argv[3], "example.txt") != 0)
    {
        printf("Error: Incorrect file name entered \n");
        printf("Usage: ./myprog ls -l example.txt \n");
        return 1;
    }

    //call the system command to execute the ls -l command
    system("ls -l");

    return 0;
}

//end of program