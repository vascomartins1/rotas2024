#ifndef FLIGHT_H
#define FLIGHT_H

#include "coord.h"

typedef struct {
    int hour, minute;
} Time;

typedef struct {
    Coordinate latitude;
    Coordinate longitude;
    char icao[5];
    char iata[4];
    char city[50];
    int timezone;
} Airport;

typedef struct {
    char airline[50];
    char code[5];
    char origin[5], destiny[5];
    Time departure, arrival;
} Route;

#endif