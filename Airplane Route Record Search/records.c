#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "records.h"

RouteRecord* createRecords(FILE* fileIn) //creates an array for records
{
	RouteRecord* arr;
	int n, i, j;
	char buffer[100];
	fgets(buffer, 500, fileIn);
	while(fgets(buffer, 500, fileIn) != NULL)
	{
		++n;
	}	
	arr = (RouteRecord*)malloc(n * sizeof(RouteRecord));
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < 6; j++)
		{
			arr[i].passCnt[j] = 0;
		}
	}
	rewind(fileIn);
	
	return arr;
}
int fillRecords(RouteRecord* arr, FILE* fileIn) //initializes the array
{
	int month, numPass, idx, count = 0, i = 0;
	char o[4], d[4], al[3], ty[11];
	char buffer[500];
	fgets(buffer, 500,fileIn);
	while(fgets(buffer, 500, fileIn) != NULL)
	{
		sscanf(buffer, "%d,%[^,],%[^,],%[^,],%[^,],%d", &month, o, d, al, ty, &numPass);
		idx = findAirlineRoute(arr, i, o, d, al, 1); 
		if(idx != -1)
		{
			arr[idx].passCnt[month - 1] = numPass;	
		}
		else
		{
			strcpy(arr[i].origin, o);
			strcpy(arr[i].dest, d);
			strcpy(arr[i].airline, al);
			strcpy(arr[i].type, ty);
			arr[i].passCnt[month - 1] = numPass;
			++count;
			++i;	
		}
		
	}
	return count;
}
int findAirlineRoute(RouteRecord* arr, int length, const char* o, const char* d, const char* al, int curIdx) //searches array for same route
{
        int track;
	int t;
	if(curIdx > length)
	{
		return -1;
	}
	else
	{
		t = curIdx - 1; 
		track = findAirlineRoute(arr, length, o, d, al, curIdx + 1);
		if(track != -1)
		{
			return track;
		}
		if(strcmp(arr[t].origin, o) == 0 && strcmp(arr[t].dest, d) == 0 && strcmp(arr[t].airline, al) == 0)
		{ 
			return t;
		}
		return -1;
		
	
	}
}
void searchRecords(RouteRecord* arr, int length, const char* key1, const char* key2, SearchType st) //search array for user requested data
{
	int i, j, avgPass, m1 = 0, m2 = 0, m3 = 0, m4 = 0, m5 = 0, m6 = 0, numMatches = 0, totalPass = 0;

	if(st == ROUTE)
	{
		printf("\nSearching by route...\n");
		for(i = 0; i < length; i++)
		{
			if(strcmp(arr[i].origin, key1) == 0 && strcmp(arr[i].dest, key2) == 0)
			{
				printf("%s (%s-%s) ", arr[i].airline, arr[i].origin, arr[i].dest);
				++numMatches;
				for(j = 0; j < 6; j++)
				{
				     totalPass = totalPass + arr[i].passCnt[j];	
				}
				m1 += arr[i].passCnt[0];
				m2 += arr[i].passCnt[1];
				m3 += arr[i].passCnt[2];
				m4 += arr[i].passCnt[3];
				m5 += arr[i].passCnt[4];
				m6 += arr[i].passCnt[5];
			}
		}
		printf("\n%d matches were found.\n\nStatistics\nTotal Passengers:           	%7d\n", numMatches, totalPass);
		printf("Total Passengers in Month 1: 	%7d\nTotal Passengers in Month 2:    %7d\n", m1, m2);
		printf("Total Passengers in Month 3:	%7d\nTotal Passengers in Month 4:    %7d\n", m3, m4);
		printf("Total Passengers in Month 5:	%7d\nTotal Passengers in Month 6:    %7d\n", m5, m6);
		printf("\nAverage passengers per Month:   %7d\n", totalPass/6);	
	}
	else if(st == ORIGIN)
	{
                  printf("Search by origin...\n");
	          for(i = 0; i < length; i++)
                  {
                         if(strcmp(arr[i].origin, key1) == 0)
                         {
                                 printf("%s (%s-%s) ", arr[i].airline, arr[i].origin, arr[i].dest);
                                 ++numMatches;
                                 for(j = 0; j < 6; j++)
                                 {
                                      totalPass = totalPass + arr[i].passCnt[j];
                                 }
                                 m1 += arr[i].passCnt[0];
                                 m2 += arr[i].passCnt[1];
                                 m3 += arr[i].passCnt[2];
                                 m4 += arr[i].passCnt[3];
                                 m5 += arr[i].passCnt[4];
                                 m6 += arr[i].passCnt[5];
                         
			}                 
		   }
                 printf("\n%d matches were found.\n\nStatistics\nTotal Passengers:               %7d\n", numMatches, totalPass);
                 printf("Total Passengers in Month 1:    %7d\nTotal Passengers in Month 2:    %7d\n", m1, m2);
		 printf("Total Passengers in Month 3:    %7d\nTotal Passengers in Month 4:    %7d\n", m3, m4);
                 printf("Total Passengers in Month 5:    %7d\nTotal Passengers in Month 6:    %7d\n", m5, m6);  
                 printf("\nAverage passengers per Month:   %7d\n", totalPass/6);
	}
	else if(st == DESTINATION)
	{
		printf("Searching by destination...\n");
		for(i = 0; i < length; i++)
		{
			if(strcmp(arr[i].dest, key1) == 0)
			{
				printf("%s (%s-%s) ", arr[i].airline, arr[i].origin, arr[i].dest);
				++numMatches;
				for(j=0; j < 6; j++)
				{
					totalPass = totalPass + arr[i].passCnt[j];
				}
				 m1 += arr[i].passCnt[0];
				 m2 += arr[i].passCnt[1];
				 m3 += arr[i].passCnt[2];
				 m4 += arr[i].passCnt[3];
				 m5 += arr[i].passCnt[4];
				 m6 += arr[i].passCnt[5];
			}
		}
		printf("\n%d matches were found.\n\nStatistics\nTotal Passengers:               %7d\n", numMatches, totalPass);
		printf("Total Passengers in Month 1:    %7d\nTotal Passengers in Month 2:    %7d\n", m1, m2);
		printf("Total Passengers in Month 3:    %7d\nTotal Passengers in Month 4:    %7d\n", m3, m4);
		printf("Total Passengers in Month 5:    %7d\nTotal Passengers in Month 6:    %7d\n", m5, m6);
		printf("\nAverage passengers per Month:   %7d\n", totalPass/6);
	}
	else if(st == AIRLINE)
	{
		printf("Search by airline...\n");
		for(i = 0; i < length; i++)
		{
			if(strcmp(arr[i].airline, key1) == 0)
			{
				printf("%s (%s-%s) ", arr[i].airline, arr[i].origin,arr[i].dest);
				++numMatches;
				for(j=0; j < 6; j++)
				{
					totalPass = totalPass + arr[i].passCnt[j];
				}
				m1 += arr[i].passCnt[0];
				m2 += arr[i].passCnt[1];
				m3 += arr[i].passCnt[2];
				m4 += arr[i].passCnt[3];
				m5 += arr[i].passCnt[4];
				m6 += arr[i].passCnt[5];


			}
		}
	        printf("\n%d matches were found.\n\nStatistics\nTotal Passengers:               %7d\n", numMatches, totalPass);
		printf("Total Passengers in Month 1:    %7d\nTotal Passengers in Month 2:    %7d\n", m1, m2);
		printf("Total Passengers in Month 3:    %7d\nTotal Passengers in Month 4:    %7d\n", m3, m4);
		printf("Total Passengers in Month 5:    %7d\nTotal Passengers in Month 6:    %7d\n", m5, m6);
		printf("\nAverage passengers per Month:   %7d\n", totalPass/6);
	}
	
}
void printMenu(void) //Prints menu
{
	printf("\n\n######### Airline Route Records Database MENU #########\n");
	printf("1. Search by Route\n");
	printf("2. Search by Origin Airport\n");
	printf("3. Search by Destination Airport\n");
	printf("4. Search by Airline\n");
	printf("5. Quit\n");
}
void printRecords(RouteRecord* arr, int length) //Prints records
{
	int i;
	int j;
	for(i = 0; i < length; i++)
	{
		printf("%s, %s, %s, ", arr[i].origin, arr[i].dest, arr[i].airline);
		for(j = 0; j < 6; j++)
		{
			printf("Month %d: %d, ", j+1, arr[i].passCnt[j]);
		}
		printf("\n");
	}
}
