#include "records.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// createRecord function to read file and allocate memory to record array
RouteRecord *createRecords(FILE *inFile)
{

    int size = 0;
    // creating instance in order to dynamic allocate array once it knows the size
    RouteRecord *records;
    char buffer[LENGTH];
    while (fgets(buffer, LENGTH, inFile) != NULL)
    {
        // skipping the first line, first charecter in header is M
        if (buffer[0] == 'M')
        {
            continue;
        }
        // incrementing size after each line
        size++;
    }
    // rewinding file
    rewind(inFile);

    records = (RouteRecord *)malloc(size * sizeof(RouteRecord));

    // returning an empty array with set size
    return records;
}

// function to fill the dynamic struct array
int fillRecords(RouteRecord *r, FILE *inFile)
{
    int size = 0;
    int i = 0;
    int flightIndex;
    char buffer[LENGTH];
    int temp;
    int passengerIndex = 0;
    // creating instance of RouteRecord for temporary values
    RouteRecord tmp;
    int j = 0;

    while (fgets(buffer, LENGTH, inFile) != NULL)
    {
        // skipping the buffer
        if (buffer[0] == 'M')
        {
            continue;
        }
        // scanning variables onto tmp variables
        sscanf(buffer, "%d, %[^,], %[^,], %[^,], %[^,], %d", &tmp.Month, tmp.origin, tmp.destination, tmp.airline, tmp.type, &tmp.passengercount);
        // sending variables in order to find unique route, will return either -1 or an index
        flightIndex = findAirlineRoute(r, i, tmp.origin, tmp.destination, tmp.airline, 0);
        // if the route is unique, copy the tmp variables and place them onto the dynamic array
        if (flightIndex == -1)
        {
            r[j].Month = tmp.Month;
            strcpy(r[j].origin, tmp.origin);
            strcpy(r[j].destination, tmp.destination);
            strcpy(r[j].airline, tmp.airline);
            strcpy(r[j].type, tmp.type);
            // initializing every totalPass index to 0
            for (passengerIndex = 0; passengerIndex < 6; passengerIndex++)
            {
                r[j].totalPass[passengerIndex] = 0;
            }
            // storing certain tmpMonth to dynamic array
            r[j].totalPass[tmp.Month - 1] = tmp.passengercount;

            j++;

            // used to j to sort from 0, if I use i it wont sort correctly
            // if unique route is not unique, store the variable to calculate statistics later on
        }
        else
        {
            r[flightIndex].totalPass[tmp.Month - 1] = tmp.passengercount;
        }

        i++;
    }

    return j;
}

int findAirlineRoute(RouteRecord *r, int length, const char *origin, const char *destination, const char *airline, int i)
{
    // checking if values are the same
    if ((strcmp(origin, r[i].origin) == 0) && (strcmp(destination, r[i].destination) == 0) && (strcmp(airline, r[i].airline) == 0))
    {
        // if values are the same, return index
        return i;
    }
    // checking when array is out of bounds
    if (i > length)
    {
        return -1;
    }
    // keep going to find all unique routs, increment i in order to go to next value
    return findAirlineRoute(r, length, origin, destination, airline, i + 1);
}

void printMenu()
{
    printf("\n\n######### Airline Route Records Database MENU #########\n");
    printf("1. Search by Route\n");
    printf("2. Search by Origin Airport\n");
    printf("3. Search by Destination Airport\n");
    printf("4. Search by Airline\n");
    printf("5. Quit\n");
    printf("Enter your selection: ");
}
// searching records
void searchRecords(RouteRecord *r, int length, const char *key1, const char *key2, SearchType st)
{
    int i = 0;
    int j = 0;
    int matches = 0;
    int total;
    int totalPassengers[6] = {0, 0, 0, 0, 0, 0};
    int avg;
    // switch case for enums
    // iterating through the entire length of unique routs, checking if variables are the same and outputting results.
    // nested for loop in order to keep track of totalPassengers
    // printing out statistics in each case
    switch (st)
    {
    case ROUTE:
        for (i = 0; i < length; i++)
        {
            if ((strcmp(key1, r[i].origin) == 0) && (strcmp(key2, r[i].destination) == 0))
            {
                printf("%s(%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                matches++;
                for (j = 0; j < 6; j++)
                {
                    totalPassengers[j] += r[i].totalPass[j];
                }
            }
        }
        printf("\n%d matches were found.\n\n", matches);
        printf("Statistics:\n");
        total = totalPassengers[0] + totalPassengers[1] + totalPassengers[2] + totalPassengers[3] + totalPassengers[4] + totalPassengers[5];
        printf("Total passengers:\t%d\n", total);
        for (i = 0; i < 6; i++)
        {
            printf("Total passengers in Month %d:\t %d\n", i + 1, totalPassengers[i]);
        }
        printf("\nAverage Passengers per Month: %d", total / 6);

        break;
    case ORIGIN:
        for (i = 0; i < length; i++)
        {
            if ((strcmp(key1, r[i].origin) == 0) && (strcmp(key2, r[i].origin) == 0))
            {
                printf("%s(%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                matches++;
                for (j = 0; j < 6; j++)
                {
                    totalPassengers[j] += r[i].totalPass[j];
                }
            }
        }
        printf("\n%d matches were found.\n\n", matches);
        printf("Statistics:\n");
        total = totalPassengers[0] + totalPassengers[1] + totalPassengers[2] + totalPassengers[3] + totalPassengers[4] + totalPassengers[5];
        printf("Total passengers:\t%d\n", total);
        for (i = 0; i < 6; i++)
        {
            printf("Total passengers in Month %d:\t %d\n", i + 1, totalPassengers[i]);
        }
        printf("\nAverage Passengers per Month: %d", total / 6);

        break;
    case DESTINATION:
        for (i = 0; i < length; i++)
        {
            if ((strcmp(key1, r[i].destination) == 0) && (strcmp(key2, r[i].destination) == 0))
            {
                printf("%s(%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                matches++;
                for (j = 0; j < 6; j++)
                {
                    totalPassengers[j] += r[i].totalPass[j];
                }
            }
        }
        printf("\n%d matches were found.\n\n", matches);
        printf("Statistics:\n");
        total = totalPassengers[0] + totalPassengers[1] + totalPassengers[2] + totalPassengers[3] + totalPassengers[4] + totalPassengers[5];
        printf("Total passengers:\t%d\n", total);
        for (i = 0; i < 6; i++)
        {
            printf("Total passengers in Month %d:\t %d\n", i + 1, totalPassengers[i]);
        }
        printf("\nAverage Passengers per Month: %d", total / 6);

        break;
    case AIRLINE:
        for (i = 0; i < length; i++)
        {
            if ((strcmp(key1, r[i].airline) == 0) && (strcmp(key2, r[i].airline) == 0))
            {
                printf("%s(%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                matches++;
                for (j = 0; j < 6; j++)
                {
                    totalPassengers[j] += r[i].totalPass[j];
                }
            }
        }
        printf("\n%d matches were found.\n\n", matches);
        printf("Statistics:\n");
        total = totalPassengers[0] + totalPassengers[1] + totalPassengers[2] + totalPassengers[3] + totalPassengers[4] + totalPassengers[5];
        printf("Total passengers:\t%d\n", total);
        for (i = 0; i < 6; i++)
        {
            printf("Total passengers in Month %d:\t %d\n", i + 1, totalPassengers[i]);
        }
        printf("\nAverage Passengers per Month: %d", total / 6);
        break;
    }
}
