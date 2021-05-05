#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char* argv[])
{
    char c[]="cd ";
    char path[100];
    printf("Enter the path: ");
    scanf("%s", path);
    char command[106];
    strcpy(command,c);
    strcat(command,path);
    system(command);
    printf("Current working directory is now %s\n",path);
}
