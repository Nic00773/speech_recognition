#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char* argv[])
{
    char c[]="mkdir ";
    char directoryname[20];
    printf("Enter the name of the directory: ");
    scanf("%s", directoryname);
    char command[25];
    strcpy(command,c);
    strcat(command,directoryname);
    system(command);
    printf("Directory '%s' has successfully been created!\n",directoryname);
}
