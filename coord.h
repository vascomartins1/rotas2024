#ifndef COORD_H
#define COORD_H

typedef struct {
    int deg, sec, min;
    char direction; // 'N' or 'W'
} Coordinate;

#endif