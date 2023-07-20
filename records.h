#ifndef RECORDS_H
#define RECORDS_H
#define LENGTH 500 // length for the buffer
#include <stdio.h> // for the File
typedef struct RouteRecord_Struct
{
    int Month;
    char origin[4];
    char destination[4];
    char airline[3];
    char type[100];
    int passengercount;
    int totalPass[6];

} RouteRecord;
typedef enum enumSearchType
{
    ROUTE,
    ORIGIN,
    DESTINATION,
    AIRLINE
} SearchType;

// function prototypes

RouteRecord *createRecords(FILE *inFile);

int fillRecords(RouteRecord *r, FILE *fileIn);

int findAirlineRoute(RouteRecord *r, int length, const char *origin, const char *destination, const char *airline, int);

void searchRecords(RouteRecord *r, int length, const char *key1, const char *key2, SearchType st);
void printMenu();

#endif
