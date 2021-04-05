#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "records.h"

int main(int argc, char* argv[])
{
	
	FILE* fileIn;
	char key1[4];
	char key2[4];
	RouteRecord* arr = NULL;
	int length;
	char c;
	char select[10];
	SearchType st;
	if(argc < 2)   //checks if there is correct # of arguments
	{
		printf("ERROR: Missing file name\n");
		return 1;
	}
	
	printf("Opening %s...\n", argv[1]);
	fileIn = fopen(argv[1], "r");
	if(fileIn == NULL)   //checks if the file opened
	{
		printf("ERROR: Could not open file\n");
		return 1;
	}
	arr = createRecords(fileIn);
	length = fillRecords(arr, fileIn);
	fclose(fileIn);
	printf("Unique routes operated by airlines: %d\n", length);
	while(strcmp(select, "5") != 0) //prints menu until user chooses to quit and selects chosen search key
	{
		printMenu();
		printf("Enter your selection: ");
		scanf("%s", select);	
		if(strcmp(select, "1") == 0)
		{
			st = ROUTE;
			printf("Enter origin: ");
			scanf("%s", key1);
			printf("Enter destination ");
			scanf("%s", key2);
			searchRecords(arr, length, key1, key2, st);
		}
		else if(strcmp(select, "2") == 0)
		{
			st = ORIGIN;
			printf("Enter origin: ");
			scanf("%s", key1);
			searchRecords(arr, length, key1, "", st);
		}
		else if(strcmp(select, "3") == 0)
		{
			st = DESTINATION;
			printf("Enter destination: ");
			scanf("%s", key1);
			searchRecords(arr, length, key1, "", st);
		}
		else if(strcmp(select, "4") == 0)
		{
			st = AIRLINE;
			printf("Enter airline: ");
			scanf("%s", key1);
			searchRecords(arr, length, key1, "", st);
		}
		else if(strcmp(select, "5") == 0)
		{
			printf("Good-bye!\n");
			free(arr);
		}
		else if(isalpha(select[0]))
		{
			printf("Invalid input.\n");
		}
		else
		{
			printf("Invalid choice.\n");
		}
		c = getchar();
		while(c != '\n' && c != EOF) {
   		c = getchar();
		}
		

	} 
	
	return 0;
}	
