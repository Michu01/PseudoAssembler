//#ifdef _MSC_VER
//#pragma warning(disable:4996)
//#endif

#include "directives.h"
#include "commands.h"
#include "program.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Program przyjmuje nazwę pliku do kompilacji

void main(int argc, char** argv)
{
	FILE* input = NULL;
	char path[MAX_PATH_SIZE];

	//Brak podanej ścieżki do pliku

	if (argc == 1) 
	{
		printf("Brak sciezki!\nPodaj sciezke:\n");
		if (scanf_s("%s", &path, MAX_PATH_SIZE) == 0)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
	}
	else //Skopiuj nazwę ścieżki do zmiennej path
	{
		if (strcpy_s(path, MAX_PATH_SIZE * sizeof(char), argv[1]) != 0)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
	}

	//Powtarzaj dopóki nazwa pliku nie będzie prawidłowa

	while (fopen_s(&input, path, "r") != 0)
	{
		printf("Plik %s nie istnieje!\nPodaj sciezke ponownie:\n", path);
		if (scanf_s("%s", &path, MAX_PATH_SIZE) == 0)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
	}

	//Skompiluj program i zapisz go w pliku

	compile_program(input);

	printf("Kompilacja zakonczona sukcesem!");

	if (input != NULL)
		fclose(input);
}