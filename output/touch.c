#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char* argv[])
{
    char c[]="touch ";
    char filename[20];
    printf("Enter the name of the file: ");
    scanf("%s", filename);
    char command[26];
    strcpy(command,c);
    strcat(command,filename);
    system(command);
    printf("File '%s' has successfully been created!\n",filename);
}
