#ifndef RECORDS_H
#define RECORDS_H


typedef struct RouteRecord
{
	char origin[4];
	char dest[4];
	char airline[3];
	char type[11];
	int passCnt[6];
}RouteRecord;
typedef enum SearchType
{
	ROUTE, ORIGIN, DESTINATION, AIRLINE
}SearchType;
RouteRecord* createRecords(FILE*);
int fillRecords(RouteRecord*, FILE*);
int fineAirlineRoute(RouteRecord*, int, const char*, const char*, int);
void searchRecords(RouteRecord*, int, const char*, const char*, SearchType);void printRecords(RouteRecord*, int);
void printRecord(RouteRecord*, int);
void printMenu(void);

#endif
