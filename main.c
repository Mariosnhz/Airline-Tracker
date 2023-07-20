#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "records.h"
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int input;
    char origin[4];
    char dest[4];
    char airline[3];
    SearchType st;
    char buff[3];

    FILE *file;
    // if there argument count >= 2, will open file, else end program
    if (argc >= 2)
    {
        printf("Opening %s\n", argv[1]);
        file = fopen(argv[1], "r");
    }
    else
    {
        printf("ERROR: Missing file name\n");
        return 1;
    }
    // checkinf if the file will open
    if (file == NULL)
    {
        printf("ERROR: Could not open file\n");
        return -1;
    }
    // creating a dynamic instance of RouteRecord
    RouteRecord *record;
    // sending file to createRecords to dynamically allocate memory to record
    record = createRecords(file);

    // making interger length in order to keep all unique routes
    int fillR = fillRecords(record, file);
    printf("Unique routes operated by airline: %d\n", fillR);
    fclose(file);

    for (;;)
    {
        printMenu();
        // used fgets instead of scanning a charecter. Possibility of inserting number 10
        fgets(buff, 3, stdin);

        // checking if input is not an integer
        if (*buff < '0' || '9' < *buff)
        {
            fgets(buff, 3, stdin);
        }

        // if input is 10, get input again
        if (strcmp(buff, "10") == 0)
        {
            fgets(buff, 3, stdin);
        }
        // convert char to integer
        input = *buff - '0';
        // switch case to go through the options, setting enum to be be certain value in each case
        switch (input)
        {

        case 1:
            printf("Enter origin: ");
            scanf("%s", origin);
            printf("Enter destination: ");
            scanf("%s", dest);
            printf("\n");
            printf("Searching by route...\n");
            st = ROUTE;
            // key1 and key2
            searchRecords(record, fillR, origin, dest, st);
            break;
        case 2:
            printf("Enter origin: ");
            scanf("%s", origin);
            printf("Search by origin...\n");
            st = ORIGIN;
            searchRecords(record, fillR, origin, origin, st);
            break;
        case 3:
            printf("Enter destination: ");
            scanf("%s", dest);
            st = DESTINATION;
            printf("Searching by destination...\n");
            searchRecords(record, fillR, dest, dest, st);

            break;
        case 4:
            printf("Enter airline: ");
            scanf("%s", airline);
            printf("Search by airline...\n");
            st = AIRLINE;
            searchRecords(record, fillR, airline, airline, st);
            break;
        case 5:
            // free memory allocated for records
            printf("Good-bye!\n");
            free(record);
            exit(0);
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    }

    return 0;
}
