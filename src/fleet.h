#ifndef FLEET_H
#define FLEET_H

#include <stdbool.h>

typedef enum { ORIENT_H, ORIENT_V } Orientation;

typedef struct {
    char name[20];
    int length;
    int hits;
    int placed;
    int start_r;
    int start_c;
    Orientation orient;
} Ship;

typedef struct {
    Ship *ships;
    int count;
} Fleet;

bool fleet_init(Fleet *f);
void fleet_free(Fleet *f);
bool fleet_add_default_ships(Fleet *f);
Ship* fleet_get_ship(Fleet *f, int id);
bool fleet_all_sunk(Fleet *f);

#endif
