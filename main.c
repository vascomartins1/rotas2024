#include <stdio.h>
#include <string.h>

#include "coord.h"
#include "flight.h"

#define MAX_LINE_LEN 128
#define AIRPORT_PARAMS 12
#define ROUTE_PARAMS 7

typedef enum {
    true, false
} bool;

void printRoute(const Route* route) {
    printf("\tRoute ID: %s\n", route->code);
    printf("\tFrom: %s\n", route->origin);
    printf("\tTo: %s\n", route->destiny);
    printf("\tDeparture Time: %02d:%02d\n", route->departure.hour, route->departure.minute);
    printf("\tAirline: %s\n\n", route->airline);
}

void printAirport(const Airport* airport) {
    printf("\tICAO:%s\n", airport->icao);
    printf("\tIATA: %s\n", airport->iata);
    printf("\tLatitude: %d° %d' %d\" %c\n", airport->latitude.deg, airport->latitude.min,
           airport->latitude.sec, airport->latitude.direction);
    printf("\tLongitude: %d° %d' %d\" %c\n", airport->longitude.deg, airport->longitude.min,
           airport->longitude.sec, airport->longitude.direction);
    printf("\tCity: %s\n", airport->city);
    printf("\tTimezone: GMT%s%d\n\n", airport->timezone > 0 ? "+" : "", airport->timezone); //TODO: change this
}

bool readAeroportos (const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: cannot read '%s'\n", filename);
        return false;
    }
    printf("'%s' file opened succesfully.\n\n", filename);

    char buffer[MAX_LINE_LEN];
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        Airport airport;

        if(sscanf(buffer, "%4s %3s %d %d %d %c %d %d %d %c %49s %d",
        airport.icao, airport.iata,
        &airport.latitude.deg, &airport.latitude.sec, &airport.latitude.min, &airport.latitude.direction,
        &airport.longitude.deg, &airport.longitude.sec, &airport.longitude.min, &airport.longitude.direction,
        airport.city, &airport.timezone) == AIRPORT_PARAMS) {
            //TODO: populate airports matrix
            printAirport(&airport);
        }
    }

    fclose(file);
    return true;
}

bool readRoutes (const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: cannot read '%s'\n", filename);
        return false;
    }
    printf("'%s' file opened succesfully.\n\n", filename);

    char buffer[MAX_LINE_LEN];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        Route route;

        if (strncmp(buffer, "AIRLINE:", 8) == true) {
            printf("%s\n", buffer);
            if (sscanf(buffer, "AIRLINE: %s", route.airline) == 1) {
                printf("%s:\n", route.airline);
            }
        }
        else if (sscanf(buffer, "%s %s %d:%d %s %d:%d", route.code,
        route.origin, &route.departure.hour, &route.departure.minute,
        route.destiny, &route.arrival.hour, &route.arrival.minute) == ROUTE_PARAMS) {
            //TODO: populate routes matrix
            printRoute(&route);
        }
    }

    fclose(file);
    return true;
}

int main(int argc, char** argvs) {

    if (argc < 2) {
        printf("Invalid call. Expected format: rotas2024 <flags> <...>\n");
        return false;
    }

    if (strcmp(argvs[1], "-aeroportos") == true) {
        readAeroportos("aeroportos.txt");
    }

    if (strcmp(argvs[1], "-voos") == true) {
        readRoutes("rotas.txt");
    }


    return true;
}