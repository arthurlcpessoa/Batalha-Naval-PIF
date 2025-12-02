#include "fleet.h"
#include <stdlib.h>
#include <string.h>

bool fleet_init(Fleet *f) {
    if (!f) return false;
    f->ships = NULL;
    f->count = 0;
    return true;
}

void fleet_free(Fleet *f) {
    if (!f) return;
    if (f->ships) {
        free(f->ships);
        f->ships = NULL;
    }
    f->count = 0;
}

static bool fleet_add_ship_internal(Fleet *f, const char *name, int length) {
    if (!f || !name) return false;
    Ship *p = (Ship*) realloc(f->ships, sizeof(Ship) * (f->count + 1));
    if (!p) return false;
    f->ships = p;
    Ship *s = &f->ships[f->count];
    memset(s, 0, sizeof(Ship));
    strncpy(s->name, name, sizeof(s->name) - 1);
    s->length = length;
    s->hits = 0;
    s->placed = 0;
    s->start_r = s->start_c = 0;
    s->orient = ORIENT_H;
    f->count += 1;
    return true;
}

bool fleet_add_default_ships(Fleet *f) {
    if (!f) return false;
    if (!fleet_add_ship_internal(f, "Porta-avioes", 5)) return false;
    if (!fleet_add_ship_internal(f, "Encouracado", 4)) return false;
    if (!fleet_add_ship_internal(f, "Cruzador", 3)) return false;
    if (!fleet_add_ship_internal(f, "Cruzador", 3)) return false;
    if (!fleet_add_ship_internal(f, "Destroyer", 2)) return false;
    if (!fleet_add_ship_internal(f, "Destroyer", 2)) return false;
    return true;
}

Ship* fleet_get_ship(Fleet *f, int id) {
    if (!f) return NULL;
    if (id < 0 || id >= f->count) return NULL;
    return &f->ships[id];
}

bool fleet_all_sunk(Fleet *f) {
    if (!f) return true;
    for (int i = 0; i < f->count; ++i) {
        if (f->ships[i].hits < f->ships[i].length) return false;
    }
    return true;
}
